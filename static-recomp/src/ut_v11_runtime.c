#include "ut_v11_runtime.h"
#include "ut_v11_cpu.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define P_N 0x80  /* Negative */
#define P_V 0x40  /* Overflow */
#define P_B 0x10  /* Break */
#define P_D 0x08  /* Decimal */
#define P_I 0x04  /* Interrupt disable */
#define P_Z 0x02  /* Zero */
#define P_C 0x01  /* Carry */

void sc_v11_runtime_init(SCV11Runtime *runtime, const uint8_t *rom, size_t rom_size) {
    if (!runtime || !rom) return;
    memset(runtime, 0, sizeof(*runtime));
    runtime->machine.rom = (uint8_t *)rom;
    runtime->machine.rom_size = rom_size;
    runtime->scheduler.frame = 0u;
    runtime->scheduler.cpu_instructions = 0u;
    runtime->scheduler.master_clock = 0u;

    /* Set PC to the reset vector for Utopia (LoROM, reset vector at 0x81A7) */
    /* In LoROM, reset vector is at file offset 0x7FFE-0x7FFF = 0x81A7 */
    runtime->machine.cpu.pc = 0x01A7u;
    /* Set stack pointer to standard 65xx value */
    runtime->machine.cpu.sp = 0xFFu;
    /* Set initial processor status: IRQ disabled, 8-bit A/X/Y, emulation mode */
    runtime->machine.cpu.status = P_I | 0x10 | 0x20 | 0x30; /* I=1, B=1, M=1, X=1 */
    runtime->machine.cpu.bank = 0x81u; /* LoROM bank 0x81 */
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