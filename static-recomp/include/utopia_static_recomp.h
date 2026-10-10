#ifndef UTOPIA_STATIC_RECOMP_H
#define UTOPIA_STATIC_RECOMP_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define UTOPIA_RECOMP_API_VERSION 1u
#define UTOPIA_RECOMP_ROM_SIZE 524288u
#define UTOPIA_RECOMP_FRAME_WIDTH 256u
#define UTOPIA_RECOMP_FRAME_HEIGHT 239u
#define UTOPIA_RECOMP_FRAME_PIXELS \
    (UTOPIA_RECOMP_FRAME_WIDTH * UTOPIA_RECOMP_FRAME_HEIGHT)
#define UTOPIA_RECOMP_MAX_FRAME_PIXELS UTOPIA_RECOMP_FRAME_PIXELS
#define UTOPIA_RECOMP_TITLE_FRAME 840u
#define UTOPIA_RECOMP_AUDIO_SAMPLE_RATE 32040u
#define UTOPIA_RECOMP_PRESENTATION_FPS_NUMERATOR 39375000u
#define UTOPIA_RECOMP_PRESENTATION_FPS_DENOMINATOR 655171u
#define UTOPIA_RECOMP_HOST_AUDIO_SAMPLE_RATE 32040u
#define UTOPIA_RECOMP_AUDIO_CHANNELS 2u
#define UTOPIA_RECOMP_AUDIO_BITS_PER_SAMPLE 16u
#define UTOPIA_RECOMP_VIDEO_STANDARD_NTSC 1u
#define UTOPIA_RECOMP_NTSC_SCANLINES 262u
#define UTOPIA_RECOMP_NTSC_AVERAGE_MASTER_CLOCKS_PER_FRAME 357366u

/* Native SNES controller bit layout used by the static runtime. */
enum UtopiaRecompInput {
    UTOPIA_INPUT_B      = 0x8000u,
    UTOPIA_INPUT_Y      = 0x4000u,
    UTOPIA_INPUT_SELECT = 0x2000u,
    UTOPIA_INPUT_START  = 0x1000u,
    UTOPIA_INPUT_UP     = 0x0800u,
    UTOPIA_INPUT_DOWN   = 0x0400u,
    UTOPIA_INPUT_LEFT   = 0x0200u,
    UTOPIA_INPUT_RIGHT  = 0x0100u,
    UTOPIA_INPUT_A      = 0x0080u,
    UTOPIA_INPUT_X      = 0x0040u,
    UTOPIA_INPUT_L      = 0x0020u,
    UTOPIA_INPUT_R      = 0x0010u
};

typedef struct UtopiaRecomp UtopiaRecomp;
typedef void (*UtopiaRecompAudioProgressCallback)(
    UtopiaRecomp *instance, void *opaque);

typedef struct UtopiaRecompFrameResult {
    uint8_t route_continued;
    uint8_t frame_rendered;
    uint16_t input_mask;
    uint32_t start_frame;
    uint32_t end_frame;
    char renderer_error[192];
} UtopiaRecompFrameResult;

/* Creates an independent static-recompilation instance at the real cold-reset
   state. The ROM is copied by the instance; no hidden title acceleration is
   performed. Advance frames normally to observe the complete boot. */
int utopia_recomp_create(UtopiaRecomp **out_instance,
                         const uint8_t *rom,
                         size_t rom_size,
                         char *error,
                         size_t error_capacity);

/* Cartridge and scheduler timing contract for the exact USA ROM. */
const char *utopia_recomp_video_standard(void);
double utopia_recomp_nominal_fps(void);
double utopia_recomp_presentation_fps(void);
uint32_t utopia_recomp_host_audio_sample_rate(void);
uint32_t utopia_recomp_average_master_clocks_per_frame(void);

/* Opens a process-wide static-core log file. Frontends call this before
   creating the game so cold boot, rendering and audio events are recorded. */
int utopia_recomp_log_open(const char *path, char *error, size_t error_capacity);
void utopia_recomp_log_close(void);

void utopia_recomp_destroy(UtopiaRecomp *instance);

/* Returns the existing instance to the real cold-reset state. */
int utopia_recomp_reset(UtopiaRecomp *instance,
                        char *error,
                        size_t error_capacity);

/* Advances whole SNES frames through generated static dispatch. A successful
   return means the CPU route advanced. frame_rendered can still be false when
   the reached PPU feature set is outside the current renderer. */
int utopia_recomp_advance(UtopiaRecomp *instance,
                          uint16_t input_mask,
                          uint32_t frame_count,
                          UtopiaRecompFrameResult *result);

/* Advances natural guest frames while permitting the host to drain already
   produced PCM during a long frame. The callback is observational and must
   never advance or modify guest state. */
int utopia_recomp_advance_streamed(
    UtopiaRecomp *instance, uint16_t input_mask, uint32_t frame_count,
    UtopiaRecompAudioProgressCallback audio_progress, void *opaque,
    UtopiaRecompFrameResult *result);

/* Headless frame advance. CPU, PPU timing, S-SMP, S-DSP, controller
   history, and all SNES state advance identically, but the expensive host
   frame conversion is deferred. Call utopia_recomp_render_current_frame()
   when the current frame must be displayed. */
int utopia_recomp_advance_headless(UtopiaRecomp *instance,
                                   uint16_t input_mask,
                                   uint32_t frame_count,
                                   UtopiaRecompFrameResult *result);
int utopia_recomp_render_current_frame(UtopiaRecomp *instance,
                                       char *error,
                                       size_t error_capacity);

const uint32_t *utopia_recomp_frame_bgra(const UtopiaRecomp *instance);
uint32_t utopia_recomp_frame_width(const UtopiaRecomp *instance);
uint32_t utopia_recomp_current_frame(const UtopiaRecomp *instance);
uint64_t utopia_recomp_instruction_count(const UtopiaRecomp *instance);
uint64_t utopia_recomp_master_clock(const UtopiaRecomp *instance);
int utopia_recomp_failed(const UtopiaRecomp *instance);

/* Bounds-checked read of the native 128 KiB SNES WRAM image. This never
   modifies emulated state. */
int utopia_recomp_read_wram(const UtopiaRecomp *instance,
                            uint32_t offset,
                            void *destination,
                            size_t length);

/* Bounds-checked write to the native 128 KiB SNES WRAM image, for host-side
   cheats and mods applied between frames.

   Unlike utopia_recomp_read_wram() this DOES modify emulated state. Call it
   only from the thread that calls utopia_recomp_advance(), and only between
   frames.
   Returns 1 on success, 0 if the arguments are invalid or the range would
   leave the 128 KiB image. Nothing is written when it returns 0. */
int utopia_recomp_write_wram(UtopiaRecomp *instance,
                             uint32_t offset,
                             const void *source,
                             size_t length);

const char *utopia_recomp_last_error(const UtopiaRecomp *instance);

/* PCM is produced only by the native S-SMP/S-DSP runtime contained in this
   static-recompilation instance. The host frontend owns playback.
   Each returned frame contains interleaved stereo signed 16-bit samples
   at UTOPIA_RECOMP_AUDIO_SAMPLE_RATE. */
size_t utopia_recomp_audio_available(const UtopiaRecomp *instance);
size_t utopia_recomp_audio_read(UtopiaRecomp *instance,
                                int16_t *interleaved_stereo,
                                size_t frame_capacity);
size_t utopia_recomp_audio_discard(UtopiaRecomp *instance);

int utopia_recomp_audio_overflowed(const UtopiaRecomp *instance);
uint64_t utopia_recomp_audio_dropped_frames(
    const UtopiaRecomp *instance);
void utopia_recomp_audio_clear_overflow(UtopiaRecomp *instance);

/* Current snapshots store direct static-core runtime state plus the exact
   controller history needed for continued deterministic saves. */
int utopia_recomp_snapshot_save(const UtopiaRecomp *instance,
                                const char *path,
                                char *error, size_t error_capacity);
int utopia_recomp_snapshot_load(UtopiaRecomp *instance,
                                const char *path,
                                char *error, size_t error_capacity);
uint32_t utopia_recomp_snapshot_history_frames(const UtopiaRecomp *instance);

/* Battery-backed cartridge SRAM. Reset preserves this memory, matching a real
   SNES reset. Frontends persist the exact 32 KiB image between processes. */
size_t utopia_recomp_sram_size(void);
int utopia_recomp_sram_copy(const UtopiaRecomp *instance,
                            void *destination, size_t capacity);
int utopia_recomp_sram_load(UtopiaRecomp *instance,
                            const void *source, size_t size,
                            char *error, size_t error_capacity);
int utopia_recomp_sram_dirty(const UtopiaRecomp *instance);
void utopia_recomp_sram_mark_clean(UtopiaRecomp *instance);

int utopia_recomp_load_diagnostic_runtime_state(
    UtopiaRecomp *instance, const char *path, char *error, size_t error_capacity);

#ifdef __cplusplus
}
#endif

#endif