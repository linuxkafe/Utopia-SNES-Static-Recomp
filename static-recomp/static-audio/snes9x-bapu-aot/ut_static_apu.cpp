#include "ut_static_apu.h"
#include "../../internal/include/ut_audio_clock_profile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint8_t *g_aram = NULL;
static uint8_t *g_aram_known = NULL;
static int16_t g_pcm_fifo[16384];
static size_t g_pcm_read = 0, g_pcm_write = 0, g_pcm_count = 0;
static uint64_t g_pcm_overflows = 0;
static uint32_t g_phase_remainder = 0;
static uint8_t g_acquired = 0;

int ut_static_apu_acquire(char *error, size_t error_capacity) {
    (void)error; (void)error_capacity;
    if (g_acquired) return 1;
    g_aram = (uint8_t *)calloc(65536, 1);
    g_aram_known = (uint8_t *)calloc(8192, 1);
    if (!g_aram || !g_aram_known) {
        free(g_aram); free(g_aram_known);
        g_aram = g_aram_known = NULL;
        if (error) strncpy(error, "OOM", error_capacity);
        return 0;
    }
    g_acquired = 1;
    return 1;
}

void ut_static_apu_release(void) {
    free(g_aram); g_aram = NULL;
    free(g_aram_known); g_aram_known = NULL;
    g_acquired = 0;
}

void ut_static_apu_reset(void) {
    if (g_aram) memset(g_aram, 0, 65536);
    if (g_aram_known) memset(g_aram_known, 0, 8192);
    g_pcm_read = g_pcm_write = g_pcm_count = 0;
    g_pcm_overflows = 0;
}

void ut_static_apu_set_sink(void (*sink)(void*,int16_t,int16_t), void *context) {
    (void)sink; (void)context;
}

void ut_static_apu_set_trace_callbacks(const void *callbacks) {
    (void)callbacks;
}

void ut_static_apu_trace_instruction_event(uint16_t pc, uint8_t opcode) {
    (void)pc; (void)opcode;
}

int ut_static_apu_trace_aram_write_event(uint16_t address, uint8_t value) {
    (void)address; (void)value;
    return 0;
}

void ut_static_apu_trace_dsp_write_event(uint8_t address, uint8_t value) {
    (void)address; (void)value;
}

void ut_static_apu_trace_port_event(uint8_t direction, uint8_t port, uint8_t value) {
    (void)direction; (void)port; (void)value;
}

void ut_static_sdsp_primitive_step(uint8_t phase) {
    (void)phase;
}

int ut_static_sdsp_brr_step(uint16_t address, const uint8_t *aram) {
    (void)address; (void)aram;
    return 0;
}

void ut_static_sdsp_report_failure(uint32_t reason, uint8_t phase) {
    (void)reason; (void)phase;
}

int ut_static_apu_sync_to_master(uint64_t master_clock, char *error, size_t error_capacity) {
    (void)master_clock; (void)error; (void)error_capacity;
    return 1;
}

int ut_static_apu_cpu_write_port(uint64_t master_clock, unsigned port, uint8_t value, char *error, size_t error_capacity) {
    (void)master_clock; (void)port; (void)value; (void)error; (void)error_capacity;
    return 1;
}

uint8_t ut_static_apu_cpu_read_port(uint64_t master_clock, unsigned port, int *ok, char *error, size_t error_capacity) {
    (void)master_clock; (void)port; (void)ok; (void)error; (void)error_capacity;
    return 0;
}

int ut_static_apu_status(void *status) {
    (void)status;
    return 1;
}

int ut_static_apu_read_aram(uint32_t offset, void *output, size_t bytes) {
    (void)offset; (void)output; (void)bytes;
    return 0;
}

int ut_static_apu_read_dsp_register(uint8_t address, uint8_t *value) {
    (void)address; (void)value;
    return 0;
}

size_t ut_static_apu_pcm_available(void) {
    return g_pcm_count;
}

size_t ut_static_apu_pcm_read(int16_t *interleaved_stereo, uint8_t *frame_known, size_t capacity_frames) {
    size_t to_read = capacity_frames < g_pcm_count ? capacity_frames : g_pcm_count;
    for (size_t i = 0; i < to_read; i++) {
        interleaved_stereo[i * 2] = g_pcm_fifo[g_pcm_read];
        interleaved_stereo[i * 2 + 1] = g_pcm_fifo[(g_pcm_read + 1) % 16384];
        if (frame_known) frame_known[i] = 1;
        g_pcm_read = (g_pcm_read + 2) % 16384;
    }
    g_pcm_count -= to_read;
    return to_read;
}

uint64_t ut_static_apu_pcm_overflow_count(void) {
    return g_pcm_overflows;
}

size_t ut_static_apu_snapshot_size(void) {
    return 0;
}

int ut_static_apu_snapshot_save(void *data, size_t capacity) {
    (void)data; (void)capacity;
    return 0;
}

int ut_static_apu_snapshot_load(const void *data, size_t size, char *error, size_t error_capacity) {
    (void)data; (void)size; (void)error; (void)error_capacity;
    return 0;
}