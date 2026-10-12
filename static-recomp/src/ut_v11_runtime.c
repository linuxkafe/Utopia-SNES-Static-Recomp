#include "ut_v11_runtime.h"
#include "ut_v11_cpu.h"
#include "ut_v23_static_dispatch.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define P_N 0x80
#define P_V 0x40
#define P_B 0x10
#define P_D 0x08
#define P_I 0x04
#define P_Z 0x02
#define P_C 0x01

void sc_v11_runtime_init(SCV11Runtime *runtime, const uint8_t *rom, size_t rom_size) {
    if (!runtime || !rom) return;
    memset(runtime, 0, sizeof(*runtime));
    runtime->machine.rom = (uint8_t *)rom;
    runtime->machine.rom_size = rom_size;
    runtime->scheduler.frame = 0u;
    runtime->scheduler.cpu_instructions = 0u;
    runtime->scheduler.master_clock = 0u;

    /* Set stack pointer */
    runtime->machine.cpu.sp = 0xFFu;
    /* Set initial processor status: IRQ disabled, 8-bit A/X/Y, emulation mode */
    runtime->machine.cpu.status = P_I | 0x10 | 0x20 | 0x30;

    /* Initialize static dispatch if available */
    ut_cpu_dispatch_init();

    /* Read reset vector from bank 0, $FFFC-$FFFD (LoROM file 0x7FFC-0x7FFD).
     * Per W65C816 spec the reset vector is a 16-bit PC only; the bank register
     * is set to $00 on reset. (Bank 0 and bank 0x80 both map $8000-$FFFF to
     * file 0x0000-0x7FFF, so $82B7 resolves to file 0x002B7 either way.)
     * Verified against Utopia (USA).sfc: $7FFA=800C (NMI), $7FFC=82B7
     * (RESET), $7FFE=81A7 (IRQ/BRK); reset handler at file 0x002B7 =
     * D8 78 E2 20 18 FB 9C 00 42 ... (CLD; SEI; SEP #$20; CLC; XCE; STZ). */
    if (rom_size > 0x7FFD) {
        uint16_t reset_pc = (uint16_t)(rom[0x7FFC] | (rom[0x7FFD] << 8));
        runtime->machine.cpu.pc = reset_pc;
        runtime->machine.cpu.bank = 0x00u;
    } else {
        /* Fallback */
        runtime->machine.cpu.pc = 0x0000u;
        runtime->machine.cpu.bank = 0x00u;
    }
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
    /* Use static dispatch if available */
    return sc_v11_static_step(runtime);
}

int sc_v11_fail(SCV11Runtime *runtime, uint32_t address, const char *reason) {
    if (!runtime || !reason) return 0;
    runtime->route_failed = 1u;
    snprintf(runtime->route_error, sizeof(runtime->route_error),
             "route failed at 0x%06X: %s", address, reason);
    return 0;
}
