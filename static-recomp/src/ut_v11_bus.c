#include "ut_v11_bus.h"
#include "ut_v11_runtime.h"
#include <stdint.h>

/* SNES bus read/write — placeholder stubs.
   The real implementation will handle WRAM, I/O registers, DMA, HDMA,
   and cartridge ROM mapping. */

uint8_t sc_v11_bus_read(const SCV11Runtime *runtime, uint16_t addr, uint8_t bank) {
    (void)runtime; (void)bank;
    /* WRAM: 0x0000–0x1FFF maps to $7E0000–$7E1FFF in SNES address space */
    if (addr < 0x2000u) {
        return runtime ? runtime->machine.wram[addr] : 0u;
    }
    /* MMIO: 0x4020–0x402F are SNES I/O registers */
    if (addr >= SC_MMIO_BASE && addr < SC_MMIO_BASE + 0x100u) {
        size_t idx = addr - SC_MMIO_BASE;
        return runtime ? runtime->machine.mmio[idx] : 0u;
    }
    /* ROM: all other addresses fall through to the cartridge ROM */
    if (runtime && runtime->machine.rom) {
        size_t rom_off = ((size_t)bank << 16) | addr;
        if (rom_off < runtime->machine.rom_size) {
            return runtime->machine.rom[rom_off];
        }
    }
    return 0xFFu;
}

void sc_v11_bus_write(SCV11Runtime *runtime, uint16_t addr, uint8_t value, uint8_t bank) {
    (void)bank;
    if (!runtime) return;
    /* WRAM write */
    if (addr < 0x2000u) {
        if (addr < sizeof(runtime->machine.wram)) {
            runtime->machine.wram[addr] = value;
        }
        return;
    }
    /* MMIO write */
    if (addr >= SC_MMIO_BASE && addr < SC_MMIO_BASE + 0x100u) {
        size_t idx = addr - SC_MMIO_BASE;
        if (idx < sizeof(runtime->machine.mmio)) {
            runtime->machine.mmio[idx] = value;
        }
        return;
    }
    /* ROM writes are ignored (ROM is read-only) */
    (void)value;
}