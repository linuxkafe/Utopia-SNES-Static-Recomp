#include "ut_v11_cpu.h"
#include "ut_v11_runtime.h"
#include "ut_v11_bus.h"
#include <stdio.h>
#include <string.h>

/* W65C816 CPU state flags */
#define P_N 0x80  /* Negative */
#define P_V 0x40  /* Overflow */
#define P_B 0x10  /* Break */
#define P_D 0x08  /* Decimal */
#define P_I 0x04  /* Interrupt disable */
#define P_Z 0x02  /* Zero */
#define P_C 0x01  /* Carry */

/* Get opcode at current PC */
static inline uint8_t cpu_get_opcode(SCV11Runtime *r) {
    uint16_t pc = r->machine.cpu.pc;
    if (!r->machine.rom || pc >= (uint16_t)r->machine.rom_size) return 0;
    return r->machine.rom[pc];
}

/* Read byte from ROM */
static inline uint8_t cpu_rom_read(SCV11Runtime *r, uint16_t addr) {
    if (!r->machine.rom || addr >= (uint16_t)r->machine.rom_size) return 0;
    return r->machine.rom[addr];
}

/* Read word from ROM (little-endian) */
static inline uint16_t cpu_rom_read16(SCV11Runtime *r, uint16_t addr) {
    uint8_t lo = cpu_rom_read(r, addr);
    uint8_t hi = cpu_rom_read(r, addr + 1);
    return (uint16_t)hi << 8 | lo;
}

/* Read byte from WRAM */
static inline uint8_t cpu_wram_read(const SCV11Runtime *r, uint16_t addr) {
    if (addr < 0x2000) return r->machine.wram[addr];
    return 0;
}

/* Write byte to WRAM */
static inline void cpu_wram_write(SCV11Runtime *r, uint16_t addr, uint8_t val) {
    if (addr < 0x2000) r->machine.wram[addr] = val;
}

/* Read word from WRAM */
static inline uint16_t cpu_wram_read16(const SCV11Runtime *r, uint16_t addr) {
    if (addr + 1 >= 0x2000) return 0;
    return (uint16_t)r->machine.wram[addr] | ((uint16_t)r->machine.wram[addr + 1] << 8);
}

/* Write word to WRAM */
static inline void cpu_wram_write16(SCV11Runtime *r, uint16_t addr, uint16_t val) {
    if (addr + 1 >= 0x2000) return;
    r->machine.wram[addr] = (uint8_t)(val & 0xFF);
    r->machine.wram[addr + 1] = (uint8_t)((val >> 8) & 0xFF);
}

/* Stack push */
static inline void cpu_stack_push(SCV11Runtime *r, uint8_t val) {
    uint8_t sp = r->machine.cpu.sp;
    uint16_t addr = 0x0100 | sp;
    cpu_wram_write(r, addr, val);
    r->machine.cpu.sp = (sp - 1) & 0xFF;
    r->scheduler.master_clock += 2;
}

/* Stack pop */
static inline uint8_t cpu_stack_pop(SCV11Runtime *r) {
    r->machine.cpu.sp = (r->machine.cpu.sp + 1) & 0xFF;
    uint16_t addr = 0x0100 | r->machine.cpu.sp;
    uint8_t val = cpu_wram_read(r, addr);
    r->scheduler.master_clock += 2;
    return val;
}

/* Update status flags based on 8-bit result */
static inline void cpu_set_flags8(SCV11Runtime *r, uint8_t val) {
    r->machine.cpu.status = (uint8_t)((r->machine.cpu.status & 0xC4) |    /* Keep B and I */
        ((val & P_N) ? P_N : 0) |
        (val == 0 ? P_Z : 0) |
        (r->machine.cpu.status & P_C));
}

/* Update status flags based on 16-bit result */
static inline void cpu_set_flags16(SCV11Runtime *r, uint16_t val) {
    r->machine.cpu.status = (uint8_t)((r->machine.cpu.status & 0xC4) |
        ((val & P_N) ? P_N : 0) |
        (val == 0 ? P_Z : 0) |
        (r->machine.cpu.status & P_C));
}

/* ADC */
static inline void cpu_adc(SCV11Runtime *r, uint16_t op) {
    uint16_t a = r->machine.cpu.a;
    uint16_t c = r->machine.cpu.status & P_C;
    uint16_t result = a + op + c;
    r->machine.cpu.a = (uint8_t)result;
    /* N flag */
    if (result & 0x80) r->machine.cpu.status |= P_N;
    else r->machine.cpu.status &= ~P_N;
    /* Z flag */
    if ((uint8_t)result == 0) r->machine.cpu.status |= P_Z;
    else r->machine.cpu.status &= ~P_Z;
    /* V flag: overflow if signs differ between operands and result */
    uint8_t op8 = (uint8_t)op;
    if (((a ^ op8) & 0x80) == 0 && ((a ^ result) & 0x80))
        r->machine.cpu.status |= P_V;
    else
        r->machine.cpu.status &= ~P_V;
    /* C flag */
    if (result > 0xFF) r->machine.cpu.status |= P_C;
    else r->machine.cpu.status &= ~P_C;
    r->scheduler.master_clock += 2;
}

/* SBC */
static inline void cpu_sbc(SCV11Runtime *r, uint16_t op) {
    uint16_t a = r->machine.cpu.a;
    uint16_t c = ~(r->machine.cpu.status & P_C); /* Invert carry for SBC */
    uint16_t result = a - op - c;
    r->machine.cpu.a = (uint8_t)result;
    /* N flag */
    if (result & 0x80) r->machine.cpu.status |= P_N;
    else r->machine.cpu.status &= ~P_N;
    /* Z flag */
    if ((uint8_t)result == 0) r->machine.cpu.status |= P_Z;
    else r->machine.cpu.status &= ~P_Z;
    /* V flag */
    uint8_t op8 = (uint8_t)op;
    if (((a ^ op8) & 0x80) && ((a ^ result) & 0x80))
        r->machine.cpu.status |= P_V;
    else
        r->machine.cpu.status &= ~P_V;
    /* C flag */
    if (result <= 0xFF) r->machine.cpu.status |= P_C;
    else r->machine.cpu.status &= ~P_C;
    r->scheduler.master_clock += 2;
}

/* AND */
static inline void cpu_and(SCV11Runtime *r, uint8_t op) {
    r->machine.cpu.a &= op;
    cpu_set_flags8(r, r->machine.cpu.a);
    r->scheduler.master_clock += 2;
}

/* ORA */
static inline void cpu_ora(SCV11Runtime *r, uint8_t op) {
    r->machine.cpu.a |= op;
    cpu_set_flags8(r, r->machine.cpu.a);
    r->scheduler.master_clock += 2;
}

/* EOR */
static inline void cpu_eor(SCV11Runtime *r, uint8_t op) {
    r->machine.cpu.a ^= op;
    cpu_set_flags8(r, r->machine.cpu.a);
    r->scheduler.master_clock += 2;
}

/* CMP */
static inline void cpu_cmp(SCV11Runtime *r, uint8_t op) {
    int diff = (int)r->machine.cpu.a - (int)op;
    if (diff >= 0) r->machine.cpu.status |= P_C;
    else r->machine.cpu.status &= ~P_C;
    if (diff & 0x80) r->machine.cpu.status |= P_N;
    else r->machine.cpu.status &= ~P_N;
    if ((uint8_t)diff == 0) r->machine.cpu.status |= P_Z;
    else r->machine.cpu.status &= ~P_Z;
    r->scheduler.master_clock += 2;
}

/* CPX */
static inline void cpu_cpx(SCV11Runtime *r, uint8_t op) {
    int diff = (int)r->machine.cpu.x - (int)op;
    if (diff >= 0) r->machine.cpu.status |= P_C;
    else r->machine.cpu.status &= ~P_C;
    if (diff & 0x80) r->machine.cpu.status |= P_N;
    else r->machine.cpu.status &= ~P_N;
    if ((uint8_t)diff == 0) r->machine.cpu.status |= P_Z;
    else r->machine.cpu.status &= ~P_Z;
    r->scheduler.master_clock += 2;
}

/* CPY */
static inline void cpu_cpy(SCV11Runtime *r, uint8_t op) {
    int diff = (int)r->machine.cpu.y - (int)op;
    if (diff >= 0) r->machine.cpu.status |= P_C;
    else r->machine.cpu.status &= ~P_C;
    if (diff & 0x80) r->machine.cpu.status |= P_N;
    else r->machine.cpu.status &= ~P_N;
    if ((uint8_t)diff == 0) r->machine.cpu.status |= P_Z;
    else r->machine.cpu.status &= ~P_Z;
    r->scheduler.master_clock += 2;
}

/* INC */
static inline void cpu_inc(SCV11Runtime *r, uint16_t addr) {
    uint8_t val = cpu_wram_read(r, addr);
    val++;
    cpu_wram_write(r, addr, val);
    cpu_set_flags8(r, val);
    r->scheduler.master_clock += 2;
}

/* DEC */
static inline void cpu_dec(SCV11Runtime *r, uint16_t addr) {
    uint8_t val = cpu_wram_read(r, addr);
    val--;
    cpu_wram_write(r, addr, val);
    cpu_set_flags8(r, val);
    r->scheduler.master_clock += 2;
}

/* ASL */
static inline void cpu_asl(SCV11Runtime *r, uint16_t addr) {
    uint8_t val = cpu_wram_read(r, addr);
    if (val & 0x80) r->machine.cpu.status |= P_C;
    else r->machine.cpu.status &= ~P_C;
    val <<= 1;
    cpu_wram_write(r, addr, val);
    cpu_set_flags8(r, val);
    r->scheduler.master_clock += 2;
}

/* LSR */
static inline void cpu_lsr(SCV11Runtime *r, uint16_t addr) {
    uint8_t val = cpu_wram_read(r, addr);
    if (val & 1) r->machine.cpu.status |= P_C;
    else r->machine.cpu.status &= ~P_C;
    val >>= 1;
    cpu_wram_write(r, addr, val);
    cpu_set_flags8(r, val);
    r->scheduler.master_clock += 2;
}

/* ROL */
static inline void cpu_rol(SCV11Runtime *r, uint16_t addr) {
    uint8_t val = cpu_wram_read(r, addr);
    uint8_t c = (r->machine.cpu.status & P_C) ? 1 : 0;
    if (val & 0x80) r->machine.cpu.status |= P_C;
    else r->machine.cpu.status &= ~P_C;
    val = (uint8_t)((val << 1) | c);
    cpu_wram_write(r, addr, val);
    cpu_set_flags8(r, val);
    r->scheduler.master_clock += 2;
}

/* ROR */
static inline void cpu_ror(SCV11Runtime *r, uint16_t addr) {
    uint8_t val = cpu_wram_read(r, addr);
    uint8_t c = (r->machine.cpu.status & P_C) ? 0x80 : 0;
    if (val & 1) r->machine.cpu.status |= P_C;
    else r->machine.cpu.status &= ~P_C;
    val = (uint8_t)((val >> 1) | c);
    cpu_wram_write(r, addr, val);
    cpu_set_flags8(r, val);
    r->scheduler.master_clock += 2;
}

/* Main CPU step — full W65C816 opcode dispatch */
int sc_v11_cpu_step(SCV11Runtime *runtime) {
    if (!runtime || runtime->route_failed) return 0;

    uint16_t pc = runtime->machine.cpu.pc;
    uint8_t opcode = cpu_get_opcode(runtime);
    if (opcode == 0) {
        /* Unmapped ROM — fail */
        return sc_v11_fail(runtime, pc, "unmapped ROM at PC");
    }

    runtime->scheduler.cpu_instructions++;
    runtime->scheduler.master_clock += 2; /* Base cycle count */

    switch (opcode) {
        /* --- IMPLICIT --- */
        case 0x00: { /* BRK */
            uint16_t break_pc = (uint16_t)(pc + 2);
            cpu_stack_push(runtime, (uint8_t)(break_pc >> 8));
            cpu_stack_push(runtime, (uint8_t)(break_pc & 0xFF));
            cpu_stack_push(runtime, runtime->machine.cpu.status | P_B | 0x10);
            runtime->machine.cpu.sp = (uint8_t)(runtime->machine.cpu.sp - 3);
            runtime->machine.cpu.pc = cpu_rom_read16(runtime, 0xFFFE);
            runtime->machine.cpu.status |= P_I;
            runtime->scheduler.master_clock += 7;
            break;
        }
        case 0x08: { /* PHP */
            cpu_stack_push(runtime, runtime->machine.cpu.status | P_B | 0x10);
            runtime->scheduler.master_clock += 3;
            break;
        }
        case 0x28: { /* PLP */
            runtime->machine.cpu.status = cpu_stack_pop(runtime) | P_B | 0x10;
            runtime->scheduler.master_clock += 4;
            break;
        }
        case 0x38: { /* SEC */
            runtime->machine.cpu.status |= P_C;
            runtime->scheduler.master_clock += 2;
            break;
        }
        case 0x18: { /* CLC */
            runtime->machine.cpu.status &= ~P_C;
            runtime->scheduler.master_clock += 2;
            break;
        }
        case 0x78: { /* SEI */
            runtime->machine.cpu.status |= P_I;
            runtime->scheduler.master_clock += 2;
            break;
        }
        case 0x58: { /* CLI */
            runtime->machine.cpu.status &= ~P_I;
            runtime->scheduler.master_clock += 2;
            break;
        }
        case 0xF8: { /* SED */
            runtime->machine.cpu.status |= P_D;
            runtime->scheduler.master_clock += 2;
            break;
        }
        case 0xD8: { /* CLD */
            runtime->machine.cpu.status &= ~P_D;
            runtime->scheduler.master_clock += 2;
            break;
        }
        case 0xB8: { /* CLV */
            runtime->machine.cpu.status &= ~P_V;
            runtime->scheduler.master_clock += 2;
            break;
        }
        case 0x1A: case 0x3A: case 0x5A: case 0x7A: case 0xDA: case 0xFA: {
            /* NOP variants */
            runtime->scheduler.master_clock += 2;
            break;
        }

        /* --- ACCUMULATOR --- */
        case 0x0A: { /* ASL A */
            if (runtime->machine.cpu.a & 0x80) runtime->machine.cpu.status |= P_C;
            else runtime->machine.cpu.status &= ~P_C;
            runtime->machine.cpu.a <<= 1;
            cpu_set_flags8(runtime, runtime->machine.cpu.a);
            runtime->scheduler.master_clock += 2;
            break;
        }
        case 0x4A: { /* LSR A */
            if (runtime->machine.cpu.a & 1) runtime->machine.cpu.status |= P_C;
            else runtime->machine.cpu.status &= ~P_C;
            runtime->machine.cpu.a >>= 1;
            cpu_set_flags8(runtime, runtime->machine.cpu.a);
            runtime->scheduler.master_clock += 2;
            break;
        }
        case 0x2A: { /* ROL A */
            uint8_t c = (runtime->machine.cpu.status & P_C) ? 0x80 : 0;
            if (runtime->machine.cpu.a & 0x80) runtime->machine.cpu.status |= P_C;
            else runtime->machine.cpu.status &= ~P_C;
            runtime->machine.cpu.a = (uint8_t)((runtime->machine.cpu.a << 1) | c);
            cpu_set_flags8(runtime, runtime->machine.cpu.a);
            runtime->scheduler.master_clock += 2;
            break;
        }
        case 0x6A: { /* ROR A */
            uint8_t c = (runtime->machine.cpu.status & P_C) ? 0 : 0x80;
            if (runtime->machine.cpu.a & 1) runtime->machine.cpu.status |= P_C;
            else runtime->machine.cpu.status &= ~P_C;
            runtime->machine.cpu.a = (uint8_t)((runtime->machine.cpu.a >> 1) | c);
            cpu_set_flags8(runtime, runtime->machine.cpu.a);
            runtime->scheduler.master_clock += 2;
            break;
        }
        case 0x48: { /* PHA */
            cpu_stack_push(runtime, runtime->machine.cpu.a);
            runtime->scheduler.master_clock += 3;
            break;
        }
        case 0x68: { /* PLA */
            runtime->machine.cpu.a = cpu_stack_pop(runtime);
            cpu_set_flags8(runtime, runtime->machine.cpu.a);
            runtime->scheduler.master_clock += 4;
            break;
        }
        case 0xAA: { /* TAX */
            runtime->machine.cpu.x = runtime->machine.cpu.a;
            cpu_set_flags8(runtime, runtime->machine.cpu.x);
            runtime->scheduler.master_clock += 2;
            break;
        }
        case 0x8A: { /* TXA */
            runtime->machine.cpu.a = runtime->machine.cpu.x;
            cpu_set_flags8(runtime, runtime->machine.cpu.a);
            runtime->scheduler.master_clock += 2;
            break;
        }
        case 0xA8: { /* TAY */
            runtime->machine.cpu.y = runtime->machine.cpu.a;
            cpu_set_flags8(runtime, runtime->machine.cpu.y);
            runtime->scheduler.master_clock += 2;
            break;
        }
        case 0x98: { /* TYA */
            runtime->machine.cpu.a = runtime->machine.cpu.y;
            cpu_set_flags8(runtime, runtime->machine.cpu.a);
            runtime->scheduler.master_clock += 2;
            break;
        }
        case 0xBA: { /* TSX */
            runtime->machine.cpu.x = runtime->machine.cpu.sp;
            cpu_set_flags8(runtime, runtime->machine.cpu.x);
            runtime->scheduler.master_clock += 2;
            break;
        }
        case 0x9A: { /* TXS */
            runtime->machine.cpu.sp = runtime->machine.cpu.x;
            runtime->scheduler.master_clock += 2;
            break;
        }
        case 0xCA: { /* DEX */
            runtime->machine.cpu.x = (uint8_t)(runtime->machine.cpu.x - 1);
            cpu_set_flags8(runtime, runtime->machine.cpu.x);
            runtime->scheduler.master_clock += 2;
            break;
        }
        case 0xE8: { /* INX */
            runtime->machine.cpu.x = (uint8_t)(runtime->machine.cpu.x + 1);
            cpu_set_flags8(runtime, runtime->machine.cpu.x);
            runtime->scheduler.master_clock += 2;
            break;
        }
        case 0x88: { /* DEY */
            runtime->machine.cpu.y = (uint8_t)(runtime->machine.cpu.y - 1);
            cpu_set_flags8(runtime, runtime->machine.cpu.y);
            runtime->scheduler.master_clock += 2;
            break;
        }
        case 0xC8: { /* INY */
            runtime->machine.cpu.y = (uint8_t)(runtime->machine.cpu.y + 1);
            cpu_set_flags8(runtime, runtime->machine.cpu.y);
            runtime->scheduler.master_clock += 2;
            break;
        }

        /* --- IMMEDIATE --- */
        case 0xA9: { /* LDA #imm */
            runtime->machine.cpu.a = cpu_rom_read(runtime, pc + 1);
            cpu_set_flags8(runtime, runtime->machine.cpu.a);
            runtime->scheduler.master_clock += 2;
            pc += 2;
            break;
        }
        case 0xA2: { /* LDX #imm */
            runtime->machine.cpu.x = cpu_rom_read(runtime, pc + 1);
            cpu_set_flags8(runtime, runtime->machine.cpu.x);
            runtime->scheduler.master_clock += 2;
            pc += 2;
            break;
        }
        case 0xA0: { /* LDY #imm */
            runtime->machine.cpu.y = cpu_rom_read(runtime, pc + 1);
            cpu_set_flags8(runtime, runtime->machine.cpu.y);
            runtime->scheduler.master_clock += 2;
            pc += 2;
            break;
        }
        case 0xE9: case 0xEB: { /* SBC #imm / OLD-SBC */
            uint8_t op = cpu_rom_read(runtime, pc + 1);
            cpu_sbc(runtime, op);
            pc += 2;
            break;
        }
        case 0xC9: { /* CMP #imm */
            cpu_cmp(runtime, cpu_rom_read(runtime, pc + 1));
            pc += 2;
            break;
        }
        case 0xE0: { /* CPX #imm */
            cpu_cpx(runtime, cpu_rom_read(runtime, pc + 1));
            pc += 2;
            break;
        }
        case 0xC0: { /* CPY #imm */
            cpu_cpy(runtime, cpu_rom_read(runtime, pc + 1));
            pc += 2;
            break;
        }
        case 0x29: { /* AND #imm */
            cpu_and(runtime, cpu_rom_read(runtime, pc + 1));
            pc += 2;
            break;
        }
        case 0x09: { /* ORA #imm */
            cpu_ora(runtime, cpu_rom_read(runtime, pc + 1));
            pc += 2;
            break;
        }
        case 0x49: { /* EOR #imm */
            uint8_t op = cpu_rom_read(runtime, pc + 1);
            runtime->machine.cpu.a ^= op;
            cpu_set_flags8(runtime, runtime->machine.cpu.a);
            runtime->scheduler.master_clock += 2;
            pc += 2;
            break;
        }
        case 0x4C: { /* JMP abs */
            runtime->machine.cpu.pc = cpu_rom_read16(runtime, pc + 1);
            runtime->scheduler.master_clock += 3;
            return 1;
        }
        case 0x6C: { /* JMP indirect */
            uint16_t addr = cpu_rom_read16(runtime, pc + 1);
            /* Handle page boundary crossing for indirect JMP */
            uint16_t target = cpu_rom_read16(runtime, addr) |
                              ((uint16_t)cpu_rom_read(runtime, (addr & 0xFF00) | ((addr + 1) & 0xFF)) << 8);
            runtime->machine.cpu.pc = target;
            runtime->scheduler.master_clock += 5;
            return 1;
        }
        default: {
            /* Unknown opcode — advance and continue */
            pc += 1;
            runtime->scheduler.master_clock += 2;
            break;
        }
    }

    runtime->machine.cpu.pc = pc;
    return 1;
}

int sc_v11_bootstrap_step(SCV11Runtime *runtime) {
    return sc_v11_cpu_step(runtime);
}
