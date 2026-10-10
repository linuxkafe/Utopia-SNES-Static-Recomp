#include "utopia_static_recomp.h"

#include "ut_v11_runtime.h"
#include "ut_v28_video.h"
#include "ut_audio_epoch_manifest.h"
#include "ut_audio_scpu_access_manifest.h"
#include "ut_static_apu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/* Forward declarations */
static void core_logf(const UtopiaRecomp *inst, const char *event,
                      const char *fmt, ...);
void utopia_recomp_log_close(void);

#define UTOPIA_FRAME_INSTRUCTION_GUARD UINT64_C(50000)
#define UTOPIA_HOST_PCM_CAPACITY_FRAMES 65536u

struct UtopiaRecomp {
    uint8_t *rom;
    SCV11Runtime *runtime;
    uint32_t bgra[UTOPIA_RECOMP_MAX_FRAME_PIXELS];
    int16_t audio_pcm[UTOPIA_HOST_PCM_CAPACITY_FRAMES *
                      UTOPIA_RECOMP_AUDIO_CHANNELS];
    uint32_t audio_read_frame;
    uint32_t audio_write_frame;
    uint32_t audio_available_frames;
    uint8_t audio_overflow;
    uint64_t audio_dropped_frames;
    uint8_t static_acquired;
    char last_error[256];
    uint16_t *input_history;
    uint32_t input_history_count;
    uint32_t input_history_capacity;
    uint8_t replaying_snapshot;
    uint8_t initialized;
};

static void copy_text(char *dst, size_t cap, const char *src) {
    if (!dst || cap == 0u) return;
    snprintf(dst, cap, "%s", src ? src : "");
}

static void set_error(UtopiaRecomp *inst, const char *message) {
    if (inst) copy_text(inst->last_error, sizeof(inst->last_error), message);
}

static FILE *g_core_log = NULL;
static unsigned long long g_core_log_seq = 0u;

static void core_logf(const UtopiaRecomp *inst, const char *event,
                      const char *fmt, ...) {
    va_list ap;
    if (!g_core_log) return;
    (void)fprintf(g_core_log, "%llu [CORE] event=%s",
                  ++g_core_log_seq, event ? event : "message");
    if (inst && inst->runtime) {
        (void)fprintf(g_core_log, " frame=%u instructions=%llu master=%llu",
                      inst->runtime->scheduler.frame,
                      (unsigned long long)inst->runtime->scheduler.cpu_instructions,
                      (unsigned long long)inst->runtime->scheduler.master_clock);
    }
    if (fmt && *fmt) {
        (void)fputc(' ', g_core_log);
        va_start(ap, fmt);
        (void)vfprintf(g_core_log, fmt, ap);
        va_end(ap);
    }
    (void)fputc('\n', g_core_log);
    (void)fflush(g_core_log);
}

int utopia_recomp_log_open(const char *path, char *error, size_t error_capacity) {
    utopia_recomp_log_close();
    if (!path || !*path) {
        copy_text(error, error_capacity, "A static-core log path is required.");
        return 0;
    }
    g_core_log = fopen(path, "ab");
    if (!g_core_log) {
        copy_text(error, error_capacity, "Unable to open the static-core log file.");
        return 0;
    }
    g_core_log_seq = 0u;
    core_logf(NULL, "log-open", "native_fps=%.12f audio_rate=%u",
              utopia_recomp_nominal_fps(), UTOPIA_RECOMP_AUDIO_SAMPLE_RATE);
    copy_text(error, error_capacity, "");
    return 1;
}

void utopia_recomp_log_close(void) {
    if (!g_core_log) return;
    core_logf(NULL, "log-close", "");
    (void)fclose(g_core_log);
    g_core_log = NULL;
}

static void audio_sink(void *context, int16_t left, int16_t right) {
    UtopiaRecomp *inst = (UtopiaRecomp *)context;
    if (!inst) return;
    if (inst->audio_available_frames >= UTOPIA_HOST_PCM_CAPACITY_FRAMES) {
        inst->audio_overflow = 1u;
        inst->audio_dropped_frames++;
        return;
    }
    uint32_t frame = inst->audio_write_frame;
    inst->audio_pcm[frame * UTOPIA_RECOMP_AUDIO_CHANNELS] = left;
    inst->audio_pcm[frame * UTOPIA_RECOMP_AUDIO_CHANNELS + 1u] = right;
    inst->audio_write_frame = (frame + 1u) % UTOPIA_HOST_PCM_CAPACITY_FRAMES;
    inst->audio_available_frames++;
}

static int history_reserve(UtopiaRecomp *inst, uint32_t needed) {
    uint32_t capacity;
    uint16_t *grown;
    if (!inst || needed <= inst->input_history_capacity) return 1;
    capacity = inst->input_history_capacity ? inst->input_history_capacity : 4096u;
    while (capacity < needed) {
        if (capacity > UINT32_MAX / 2u) return 0;
        capacity *= 2u;
    }
    grown = (uint16_t *)realloc(inst->input_history, (size_t)capacity * sizeof(uint16_t));
    if (!grown) return 0;
    inst->input_history = grown;
    inst->input_history_capacity = capacity;
    return 1;
}

static int cold_reset(UtopiaRecomp *inst, char *error, size_t error_capacity) {
    uint8_t preserved_sram[SC_V11_SRAM_SIZE];
    uint8_t preserved_dirty = 0u;
    int preserve = 0;

    if (!inst || !inst->runtime || !inst->rom) {
        copy_text(error, error_capacity, "The static recompilation instance is incomplete.");
        return 0;
    }

    preserve = inst->initialized != 0u;
    if (preserve) {
        memcpy(preserved_sram, inst->runtime->sram, sizeof(preserved_sram));
        preserved_dirty = inst->runtime->sram_dirty;
    }

    memset(inst->runtime, 0, sizeof(*inst->runtime));
    memset(inst->bgra, 0, sizeof(inst->bgra));
    inst->audio_read_frame = 0u;
    inst->audio_write_frame = 0u;
    inst->audio_available_frames = 0u;
    inst->audio_overflow = 0u;
    inst->audio_dropped_frames = 0u;
    if (!inst->replaying_snapshot) inst->input_history_count = 0u;
    inst->last_error[0] = '\0';

    sc_v11_runtime_init(inst->runtime, inst->rom, UTOPIA_RECOMP_ROM_SIZE);
    if (preserve) {
        memcpy(inst->runtime->sram, preserved_sram, sizeof(preserved_sram));
        inst->runtime->sram_dirty = preserved_dirty;
    }
    inst->initialized = 1u;
    sc_v11_set_audio_sink(inst->runtime, audio_sink, inst);

    if (inst->runtime->route_failed) {
        copy_text(error, error_capacity,
                  inst->runtime->route_error[0] ? inst->runtime->route_error
                                                : "The exact Utopia (USA) ROM is required.");
        return 0;
    }
    core_logf(inst, "cold-reset-ready", "");
    return 1;
}

const char *utopia_recomp_video_standard(void) { return "NTSC"; }

double utopia_recomp_nominal_fps(void) {
    return (1890000000.0 / 88.0) /
           (double)UTOPIA_RECOMP_NTSC_AVERAGE_MASTER_CLOCKS_PER_FRAME;
}

double utopia_recomp_presentation_fps(void) {
    return (double)UTOPIA_RECOMP_PRESENTATION_FPS_NUMERATOR /
           (double)UTOPIA_RECOMP_PRESENTATION_FPS_DENOMINATOR;
}

uint32_t utopia_recomp_host_audio_sample_rate(void) {
    return UTOPIA_RECOMP_HOST_AUDIO_SAMPLE_RATE;
}

uint32_t utopia_recomp_average_master_clocks_per_frame(void) {
    return UTOPIA_RECOMP_NTSC_AVERAGE_MASTER_CLOCKS_PER_FRAME;
}

int utopia_recomp_create(UtopiaRecomp **out_instance,
                         const uint8_t *rom,
                         size_t rom_size,
                         char *error,
                         size_t error_capacity) {
    UtopiaRecomp *inst;
    if (out_instance) *out_instance = NULL;
    if (!out_instance || !rom || rom_size != UTOPIA_RECOMP_ROM_SIZE) {
        copy_text(error, error_capacity,
                  "The exact 524,288-byte Utopia (USA) ROM is required.");
        return 0;
    }
    inst = (UtopiaRecomp *)calloc(1u, sizeof(*inst));
    if (!inst) {
        copy_text(error, error_capacity,
                  "Unable to allocate the static recompilation instance.");
        return 0;
    }
    inst->rom = (uint8_t *)malloc(UTOPIA_RECOMP_ROM_SIZE);
    inst->runtime = (SCV11Runtime *)calloc(1u, sizeof(*inst->runtime));
    if (!inst->rom || !inst->runtime) {
        utopia_recomp_destroy(inst);
        copy_text(error, error_capacity,
                  "Unable to allocate the static recompilation runtime.");
        return 0;
    }
    memcpy(inst->rom, rom, UTOPIA_RECOMP_ROM_SIZE);
    if (!ut_audio_transport_acquire(error, error_capacity)) {
        utopia_recomp_destroy(inst);
        return 0;
    }
    inst->static_acquired = 1u;
    core_logf(inst, "create", "audio=FullStatic");
    if (!cold_reset(inst, error, error_capacity)) {
        core_logf(inst, "reset-failed", "error=%s",
                  error && *error ? error : inst->last_error);
        utopia_recomp_destroy(inst);
        return 0;
    }
    *out_instance = inst;
    return 1;
}

void utopia_recomp_destroy(UtopiaRecomp *inst) {
    if (!inst) return;
    core_logf(inst, "destroy", "");
    if (inst->static_acquired) {
        ut_audio_transport_release();
        inst->static_acquired = 0u;
    }
    free(inst->input_history);
    free(inst->runtime);
    free(inst->rom);
    memset(inst, 0, sizeof(*inst));
    free(inst);
}

int utopia_recomp_reset(UtopiaRecomp *inst, char *error, size_t error_capacity) {
    if (!inst) {
        copy_text(error, error_capacity, "No static recompilation instance is loaded.");
        return 0;
    }
    return cold_reset(inst, error, error_capacity);
}

static int advance_internal(UtopiaRecomp *inst, uint16_t input_mask,
                            uint32_t frame_count,
                            UtopiaRecompFrameResult *result,
                            int render_frame) {
    UtopiaRecompFrameResult local;
    uint32_t target_frame;
    uint64_t guard;

    memset(&local, 0, sizeof(local));
    if (!inst || !inst->runtime || frame_count == 0u) {
        if (inst)
            copy_text(inst->last_error, sizeof(inst->last_error),
                      "A loaded instance and a nonzero frame count are required.");
        if (result) *result = local;
        return 0;
    }

    local.input_mask = input_mask;
    local.start_frame = inst->runtime->scheduler.frame;
    if (UINT32_MAX - local.start_frame < frame_count) {
        copy_text(inst->last_error, sizeof(inst->last_error),
                  "The requested frame range overflowed.");
        if (result) *result = local;
        return 0;
    }
    target_frame = local.start_frame + frame_count;
    if (!history_reserve(inst, inst->input_history_count + frame_count)) {
        copy_text(inst->last_error, sizeof(inst->last_error),
                  "Unable to grow deterministic snapshot history.");
        if (result) *result = local;
        return 0;
    }

    guard = UTOPIA_FRAME_INSTRUCTION_GUARD;
    inst->runtime->machine.joypad[0] = input_mask;

    {
        uint32_t guarded_frame = inst->runtime->scheduler.frame;
        while (!inst->runtime->route_failed &&
               inst->runtime->scheduler.frame < target_frame) {
            if (guard == 0u) {
                /* Address placeholder — real dispatch will track PC. */
                (void)sc_v11_fail(inst->runtime, 0u,
                    "per-frame generated callback guard exceeded");
                break;
            }
            --guard;
            if (!sc_v11_step(inst->runtime)) break;
            if (inst->runtime->scheduler.frame != guarded_frame) {
                guarded_frame = inst->runtime->scheduler.frame;
                guard = UTOPIA_FRAME_INSTRUCTION_GUARD;
            }
        }
    }

    if (!inst->runtime->route_failed &&
        !sc_v11_smp_sync_to_master(inst->runtime,
                                   inst->runtime->scheduler.master_clock)) {
        inst->runtime->route_failed = 1u;
    }

    local.end_frame = inst->runtime->scheduler.frame;
    local.route_continued = (uint8_t)(
        !inst->runtime->route_failed && local.end_frame >= target_frame);

    if (!local.route_continued) {
        copy_text(inst->last_error, sizeof(inst->last_error),
                  inst->runtime->route_error[0] ? inst->runtime->route_error :
                  guard == 0u ? "The static route exceeded the per-frame instruction guard."
                              : "The static route ended before the requested frame.");
        core_logf(inst, "route-failed", "input=%04X error=%s",
                  input_mask, inst->last_error);
        if (result) *result = local;
        return 0;
    }

    if (render_frame) {
        SCV28VideoReport report;
        memset(&report, 0, sizeof(report));
        if (sc_v28_render_first_visible_frame(inst->runtime,
                                              UTOPIA_RECOMP_FRAME_WIDTH, 0u,
                                              NULL, 0u,
                                              inst->bgra,
                                              UTOPIA_RECOMP_MAX_FRAME_PIXELS,
                                              &report)) {
            local.frame_rendered = 1u;
            inst->last_error[0] = '\0';
        } else {
            copy_text(local.renderer_error, sizeof(local.renderer_error),
                      report.error[0] ? report.error
                                      : "The current PPU feature set cannot be rendered.");
            copy_text(inst->last_error, sizeof(inst->last_error),
                      local.renderer_error);
            core_logf(inst, "renderer-warning", "input=%04X error=%s",
                      input_mask, local.renderer_error);
        }
    } else {
        inst->last_error[0] = '\0';
    }

    {
        uint32_t i;
        for (i = 0u; i < frame_count; ++i)
            inst->input_history[inst->input_history_count++] = input_mask;
    }
    if (inst->runtime->scheduler.frame % 60u == 0u) {
        core_logf(inst, "frame", "input=%04X rendered=%u pcm=%u",
                  input_mask, (unsigned)local.frame_rendered,
                  inst->audio_available_frames);
    }
    if (result) *result = local;
    return 1;
}

int utopia_recomp_advance(UtopiaRecomp *inst, uint16_t input_mask,
                          uint32_t frame_count,
                          UtopiaRecompFrameResult *result) {
    return advance_internal(inst, input_mask, frame_count, result, 1);
}

int utopia_recomp_advance_headless(UtopiaRecomp *inst,
                                   uint16_t input_mask,
                                   uint32_t frame_count,
                                   UtopiaRecompFrameResult *result) {
    return advance_internal(inst, input_mask, frame_count, result, 0);
}

int utopia_recomp_advance_streamed(
    UtopiaRecomp *inst, uint16_t input_mask, uint32_t frame_count,
    UtopiaRecompAudioProgressCallback audio_progress, void *opaque,
    UtopiaRecompFrameResult *result)
{
    (void)audio_progress; (void)opaque;
    return advance_internal(inst, input_mask, frame_count, result, 1);
}

int utopia_recomp_render_current_frame(UtopiaRecomp *inst,
                                       char *error,
                                       size_t error_capacity) {
    if (!inst || !inst->runtime) {
        copy_text(error, error_capacity, "No static recompilation instance is loaded.");
        return 0;
    }
    SCV28VideoReport report;
    memset(&report, 0, sizeof(report));
    if (!sc_v28_render_first_visible_frame(inst->runtime,
                                           UTOPIA_RECOMP_FRAME_WIDTH, 0u,
                                           NULL, 0u,
                                           inst->bgra,
                                           UTOPIA_RECOMP_MAX_FRAME_PIXELS,
                                           &report)) {
        copy_text(error, error_capacity,
                  report.error[0] ? report.error
                                  : "The current PPU feature set cannot be rendered.");
        return 0;
    }
    copy_text(error, error_capacity, "");
    return 1;
}

const uint32_t *utopia_recomp_frame_bgra(const UtopiaRecomp *inst) {
    return inst ? inst->bgra : NULL;
}

uint32_t utopia_recomp_frame_width(const UtopiaRecomp *inst) {
    return UTOPIA_RECOMP_FRAME_WIDTH;
}

uint32_t utopia_recomp_current_frame(const UtopiaRecomp *inst) {
    return inst && inst->runtime ? inst->runtime->scheduler.frame : 0u;
}

uint64_t utopia_recomp_instruction_count(const UtopiaRecomp *inst) {
    return inst && inst->runtime ? inst->runtime->scheduler.cpu_instructions : 0u;
}

uint64_t utopia_recomp_master_clock(const UtopiaRecomp *inst) {
    return inst && inst->runtime ? inst->runtime->scheduler.master_clock : 0u;
}

int utopia_recomp_failed(const UtopiaRecomp *inst) {
    return !inst || !inst->runtime || inst->runtime->route_failed != 0u;
}

int utopia_recomp_read_wram(const UtopiaRecomp *inst,
                            uint32_t offset,
                            void *destination,
                            size_t length) {
    if (!inst || !inst->runtime || !destination) return 0;
    size_t start = (size_t)offset;
    if (start > sizeof(inst->runtime->machine.wram) ||
        length > sizeof(inst->runtime->machine.wram) - start) return 0;
    if (length) memcpy(destination, inst->runtime->machine.wram + start, length);
    return 1;
}

int utopia_recomp_write_wram(UtopiaRecomp *inst,
                             uint32_t offset,
                             const void *source,
                             size_t length) {
    if (!inst || !inst->runtime || !source) return 0;
    size_t start = (size_t)offset;
    if (start > sizeof(inst->runtime->machine.wram) ||
        length > sizeof(inst->runtime->machine.wram) - start) return 0;
    if (length) memcpy(inst->runtime->machine.wram + start, source, length);
    return 1;
}

const char *utopia_recomp_last_error(const UtopiaRecomp *inst) {
    return inst ? inst->last_error :
            "No static recompilation instance is loaded.";
}

size_t utopia_recomp_audio_available(const UtopiaRecomp *inst) {
    return inst ? inst->audio_available_frames : 0u;
}

size_t utopia_recomp_audio_read(UtopiaRecomp *inst,
                                int16_t *interleaved_stereo,
                                size_t frame_capacity) {
    size_t count = 0u;
    if (!inst || !interleaved_stereo || frame_capacity == 0u) return 0u;
    while (count < frame_capacity && inst->audio_available_frames > 0u) {
        uint32_t frame = inst->audio_read_frame;
        interleaved_stereo[count * UTOPIA_RECOMP_AUDIO_CHANNELS] =
            inst->audio_pcm[frame * UTOPIA_RECOMP_AUDIO_CHANNELS];
        interleaved_stereo[count * UTOPIA_RECOMP_AUDIO_CHANNELS + 1u] =
            inst->audio_pcm[frame * UTOPIA_RECOMP_AUDIO_CHANNELS + 1u];
        inst->audio_read_frame = (frame + 1u) % UTOPIA_HOST_PCM_CAPACITY_FRAMES;
        inst->audio_available_frames--;
        count++;
    }
    return count;
}

size_t utopia_recomp_audio_discard(UtopiaRecomp *inst) {
    size_t discarded;
    if (!inst) return 0u;
    discarded = inst->audio_available_frames;
    inst->audio_read_frame = 0u;
    inst->audio_write_frame = 0u;
    inst->audio_available_frames = 0u;
    inst->audio_overflow = 0u;
    return discarded;
}

int utopia_recomp_audio_overflowed(const UtopiaRecomp *inst) {
    return inst && inst->audio_overflow != 0u;
}

uint64_t utopia_recomp_audio_dropped_frames(const UtopiaRecomp *inst) {
    return inst ? inst->audio_dropped_frames : 0u;
}

void utopia_recomp_audio_clear_overflow(UtopiaRecomp *inst) {
    if (inst) inst->audio_overflow = 0u;
}

/* Snapshot hashing helpers. */
static uint32_t snapshot_hash(const uint16_t *h, uint32_t count) {
    uint32_t hash = 2166136261u;
    for (uint32_t i = 0u; i < count; ++i) {
        hash ^= (uint8_t)h[i]; hash *= 16777619u;
        hash ^= (uint8_t)(h[i] >> 8); hash *= 16777619u;
    }
    return hash;
}

static uint32_t snapshot_hash_bytes(uint32_t h, const void *data, size_t size) {
    const uint8_t *bytes = (const uint8_t *)data;
    for (size_t i = 0u; i < size; ++i) { h ^= bytes[i]; h *= 16777619u; }
    return h;
}

typedef struct UtopiaSnapshotHeader {
    char magic[8];
    uint32_t version;
    uint32_t history_frames;
    uint32_t history_hash;
    uint32_t reserved;
} UtopiaSnapshotHeader;

typedef struct UtopiaSnapshotHeaderV11 {
    char magic[8]; uint32_t version, history_frames, history_hash;
    uint32_t runtime_size, apu_size, payload_hash, reserved;
} UtopiaSnapshotHeaderV11;

int utopia_recomp_snapshot_save(const UtopiaRecomp *inst, const char *path,
                                char *error, size_t error_capacity) {
    (void)inst; (void)path; (void)error; (void)error_capacity;
    /* Placeholder: full snapshot save not yet implemented. */
    copy_text(error, error_capacity, "Snapshot save not yet implemented.");
    return 0;
}

int utopia_recomp_snapshot_load(UtopiaRecomp *inst, const char *path,
                                char *error, size_t error_capacity) {
    (void)inst; (void)path; (void)error; (void)error_capacity;
    copy_text(error, error_capacity, "Snapshot load not yet implemented.");
    return 0;
}

uint32_t utopia_recomp_snapshot_history_frames(const UtopiaRecomp *inst) {
    return inst ? inst->input_history_count : 0u;
}

size_t utopia_recomp_sram_size(void) { return SC_V11_SRAM_SIZE; }

int utopia_recomp_sram_copy(const UtopiaRecomp *inst,
                            void *destination, size_t capacity) {
    if (!inst || !inst->runtime || !destination ||
        capacity < SC_V11_SRAM_SIZE) return 0;
    memcpy(destination, inst->runtime->sram, SC_V11_SRAM_SIZE);
    return 1;
}

int utopia_recomp_sram_load(UtopiaRecomp *inst,
                            const void *source, size_t size,
                            char *error, size_t error_capacity) {
    if (!inst || !inst->runtime || !source ||
        size != SC_V11_SRAM_SIZE) {
        set_error(inst, "The battery SRAM image must be exactly 32 KiB.");
        copy_text(error, error_capacity,
                  "The battery SRAM image must be exactly 32 KiB.");
        return 0;
    }
    memcpy(inst->runtime->sram, source, SC_V11_SRAM_SIZE);
    inst->runtime->sram_dirty = 0u;
    copy_text(error, error_capacity, "");
    return 1;
}

int utopia_recomp_sram_dirty(const UtopiaRecomp *inst) {
    return inst && inst->runtime && inst->runtime->sram_dirty != 0u;
}

void utopia_recomp_sram_mark_clean(UtopiaRecomp *inst) {
    if (inst && inst->runtime) inst->runtime->sram_dirty = 0u;
}

int utopia_recomp_load_diagnostic_runtime_state(
    UtopiaRecomp *inst, const char *path, char *error, size_t error_capacity) {
    (void)inst; (void)path; (void)error; (void)error_capacity;
    copy_text(error, error_capacity, "Diagnostic state load not yet implemented.");
    return 0;
}