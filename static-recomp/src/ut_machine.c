#include "ut_v11_runtime.h"
#include "ut_machine.h"
#include <string.h>
#include <stdio.h>

/* Machine-level helpers for WRAM, bus, and ROM access. */

uint16_t ut_machine_read_wram16(const SCV11Runtime *runtime, size_t offset) {
    if (!runtime || offset + 1u >= sizeof(runtime->machine.wram)) return 0u;
    return (uint16_t)(runtime->machine.wram[offset] |
                      ((uint16_t)runtime->machine.wram[offset + 1u] << 8));
}

void ut_machine_write_wram16(SCV11Runtime *runtime, size_t offset, uint16_t value) {
    if (!runtime || offset + 1u >= sizeof(runtime->machine.wram)) return;
    runtime->machine.wram[offset]     = (uint8_t)value;
    runtime->machine.wram[offset + 1u] = (uint8_t)(value >> 8);
}