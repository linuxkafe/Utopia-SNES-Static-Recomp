/* Utopia W65C816 Static Dispatch (Phase 1)

This is a placeholder dispatch file for the main game code.
The full generated dispatch will be produced by the generation script
after ROM analysis is complete.

For now, all code outside the bootstrap routes through the generic
CPU step emulator.
*/

#include "ut_v11_runtime.h"
#include "ut_v11_cpu.h"
#include <stdint.h>

int sc_v11_static_step(SCV11Runtime *runtime) {
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