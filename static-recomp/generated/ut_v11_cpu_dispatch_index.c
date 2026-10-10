/* Utopia W65C816 CPU Dispatch Index — Generated

This file provides the dispatch index that maps PC pages to generated
dispatch functions. The generated code creates dispatch blocks for
each 256-byte page of the active code region.

For T002, we generate a stub dispatch table that routes all pages
to the bootstrap or generic emulator.
*/

#include "ut_v11_runtime.h"
#include "ut_v11_cpu.h"
#include "ut_bootstrap_dispatch.h"
#include <stdint.h>
#include <string.h>

/* Generic CPU step — handles all unimplemented opcodes with a stub */
static int cpu_step_generic(SCV11Runtime *runtime) {
    if (!runtime || runtime->route_failed) return 0;

    uint16_t pc = runtime->machine.cpu.pc;
    uint8_t opcode = 0;

    if (runtime->machine.rom && pc < (uint16_t)runtime->machine.rom_size) {
        opcode = runtime->machine.rom[pc];
    }
    (void)opcode;

    runtime->scheduler.cpu_instructions++;
    runtime->scheduler.master_clock += 6;
    runtime->machine.cpu.pc = (uint16_t)(pc + 1);
    return 1;
}

/* Dispatch table — one entry per PC page (0x00-0xFF) */
static int (*dispatch_table[256])(SCV11Runtime *) = {0};

int sc_v11_cpu_step(SCV11Runtime *runtime) {
    if (!runtime || runtime->route_failed) return 0;

    uint16_t pc = runtime->machine.cpu.pc;
    uint8_t page = (uint8_t)(pc >> 8);

    if (dispatch_table[page]) {
        return dispatch_table[page](runtime);
    }

    return cpu_step_generic(runtime);
}

void ut_cpu_dispatch_init(void) {
    memset(dispatch_table, 0, sizeof(dispatch_table));
    dispatch_table[0x01] = ut_bootstrap_step;
}

uint8_t rom_read(const SCV11Runtime *r, uint16_t addr) {
    if (!r || !r->machine.rom || addr >= (uint16_t)r->machine.rom_size) return 0;
    return r->machine.rom[addr];
}