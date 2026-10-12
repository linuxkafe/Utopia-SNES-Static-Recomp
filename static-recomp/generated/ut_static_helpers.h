#ifndef UT_STATIC_HELPERS_H
#define UT_STATIC_HELPERS_H

#include "ut_v11_runtime.h"
#include <stdint.h>

/* Stack operations */
static inline void stack_push(SCV11Runtime *r, uint8_t val) {
    uint8_t sp = r->machine.cpu.sp;
    r->machine.wram[0x0100 + sp] = val;
    r->machine.cpu.sp = (sp - 1) & 0xFF;
    (void)val;
}

static inline uint8_t stack_pop(SCV11Runtime *r) {
    r->machine.cpu.sp = (r->machine.cpu.sp + 1) & 0xFF;
    return r->machine.wram[0x0100 + r->machine.cpu.sp];
}

/* ROM read */
static inline uint8_t rom_read(const SCV11Runtime *r, uint16_t addr) {
    if (!r->machine.rom || addr >= (uint16_t)r->machine.rom_size) return 0;
    return r->machine.rom[addr];
}

/* WRAM access */
static inline uint8_t wram_read(const SCV11Runtime *r, uint16_t addr) {
    if (addr < 0x2000) return r->machine.wram[addr];
    return 0;
}

static inline void wram_write(SCV11Runtime *r, uint16_t addr, uint8_t val) {
    if (addr < 0x2000) r->machine.wram[addr] = val;
    (void)val;
}

/* MMIO access */
static inline uint8_t io_read(const SCV11Runtime *r, uint16_t addr) {
    size_t idx = addr - SC_MMIO_BASE;
    if (idx < sizeof(r->machine.mmio)) return r->machine.mmio[idx];
    return 0xFF;
}

static inline void io_write(SCV11Runtime *r, uint16_t addr, uint8_t val) {
    size_t idx = addr - SC_MMIO_BASE;
    if (idx < sizeof(r->machine.mmio)) r->machine.mmio[idx] = val;
    (void)val;
}

#endif
