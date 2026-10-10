#include "ut_v11_runtime.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void sc_v11_runtime_init(SCV11Runtime *runtime, const uint8_t *rom, size_t rom_size) {
    if (!runtime || !rom) return;
    memset(runtime, 0, sizeof(*runtime));
    runtime->machine.rom = (uint8_t *)rom;
    runtime->machine.rom_size = rom_size;
    runtime->scheduler.frame = 0u;
    runtime->scheduler.cpu_instructions = 0u;
    runtime->scheduler.master_clock = 0u;
}

void sc_v11_set_audio_sink(SCV11Runtime *runtime,
                           void (*sink)(void*, int16_t, int16_t),
                           void *context) {
    if (!runtime) return;
    runtime->audio_sink = sink;
    runtime->audio_sink_context = context;
}

int sc_v11_step(SCV11Runtime *runtime) {
    if (!runtime || runtime->route_failed) return 0;
    /* Placeholder: real implementation will dispatch generated code.
       This stub advances the frame counter and returns success
       so the build compiles and links. */
    runtime->scheduler.cpu_instructions++;
    return 1;
}

int sc_v11_fail(SCV11Runtime *runtime, uint32_t address, const char *reason) {
    if (!runtime || !reason) return 0;
    runtime->route_failed = 1u;
    snprintf(runtime->route_error, sizeof(runtime->route_error),
             "route failed at 0x%06X: %s", address, reason);
    return 0;
}