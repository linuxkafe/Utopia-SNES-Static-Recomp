#!/usr/bin/env python3
"""
Utopia SNES Static Recompilation Pipeline
Translates ROM code to native C functions for static recompilation.
"""

import sys
import struct
from pathlib import Path
from collections import defaultdict, deque
from dataclasses import dataclass, field
from typing import Dict, List, Set, Optional, Tuple
import subprocess

# 65C816 opcode table with sizes and cycle counts
OPCODES = {
    # Format: opcode: (name, size, cycles, addressing_mode)
    0x00: ('BRK', 1, 7, 'impl'),  # BRK
    0x01: ('ORA (ind,X)', 6, 6, 'indx'),  # ORA (ind,X)
    0x02: ('COP', 2, 4, 'impl'),  # COP
    0x03: ('AND (ind,S)', 4, 6, 'indx'),  # AND (ind,S)
    0x04: ('TSD', 1, 3, 'impl'),  # TSD
    0x05: ('ORA dp', 3, 3, 'dp'),  # ORA dp
    0x06: ('ASL dp', 5, 5, 'dpx'),  # ASL dp
    0x07: ('PHP', 1, 3, 'impl'),  # PHP
    0x08: ('PHP', 1, 3, 'impl'),  # PHP
    0x09: ('ORA #imm', 2, 2, 'imm'),  # ORA #imm
    0x0A: ('ASL A', 1, 2, 'impl'),  # ASL A
    0x0B: ('PHD', 1, 4, 'impl'),  # PHD
    0x0C: ('TSA', 1, 3, 'impl'),  # TSA
    0x0D: ('ASL', 2, 6, 'impl'),  # ASL
    0x0E: ('ASL', 2, 6, 'impl'),  # ASL
    0x0F: ('ASL', 2, 6, 'impl'),  # ASL
    0x10: ('BPL', 2, 2, 'rel'),  # BPL
    0x11: ('ORA (ind,S),Y', 5, 5, 'indy'),  # ORA (ind,S),Y
    0x12: ('ORA dp', 2, 3, 'dp'),  # ORA dp
    0x13: ('AND (ind,S),Y', 5, 5, 'indy'),  # AND (ind,S),Y
    0x14: ('TRB dp', 3, 3, 'dp'),  # TRB dp
    0x15: ('ORA dp', 2, 3, 'dp'),  # ORA dp
    0x16: ('ASL dp', 5, 5, 'dpx'),  # ASL dp
    0x17: ('ASL dp', 5, 5, 'dpx'),  # ASL dp
    0x18: ('CLC', 1, 2, 'impl'),  # CLC
    0x19: ('ORA abs', 4, 4, 'abs'),  # ORA abs
    0x1A: ('INC A', 1, 2, 'impl'),  # INC A
    0x1B: ('TCD', 1, 0, 'impl'),  # TCD
    0x1C: ('CSD', 1, 3, 'impl'),  # CSD
    0x1D: ('ASL', 2, 6, 'impl'),  # ASL
    0x1E: ('ASL', 2, 6, 'impl'),  # ASL
    0x1F: ('ASL', 2, 6, 'impl'),  # ASL
    0x20: ('JSR', 3, 6, 'abs'),  # JSR
    0x21: ('AND (ind,X)', 6, 6, 'indx'),  # AND (ind,X)
    0x22: ('JSL', 4, 8, 'long'),  # JSL
    0x23: ('AND (ind,S)', 4, 6, 'indx'),  # AND (ind,S)
    0x24: ('BIT dp', 3, 3, 'dp'),  # BIT dp
    0x25: ('AND dp', 3, 3, 'dp'),  # AND dp
    0x26: ('ROL dp', 5, 5, 'dpx'),  # ROL dp
    0x27: ('ROL dp', 5, 5, 'dpx'),  # ROL dp
    0x28: ('PLP', 1, 4, 'impl'),  # PLP
    0x29: ('AND #imm', 2, 2, 'imm'),  # AND #imm
    0x2A: ('ROL A', 1, 2, 'impl'),  # ROL A
    0x2B: ('PLD', 1, 4, 'impl'),  # PLD
    0x2C: ('BIT abs', 3, 3, 'abs'),  # BIT abs
    0x2D: ('AND abs', 3, 4, 'abs'),  # AND abs
    0x2E: ('ROL', 2, 6, 'abs'),  # ROL
    0x2F: ('ROL', 2, 6, 'abs'),  # ROL
    0x30: ('BMI', 2, 2, 'rel'),  # BMI
    0x31: ('AND (ind,S),Y', 5, 5, 'indy'),  # AND (ind,S),Y
    0x32: ('AND dp', 2, 3, 'dp'),  # AND dp
    0x33: ('AND (ind,S),Y', 5, 5, 'indy'),  # AND (ind,S),Y
    0x34: ('NEGA', 1, 2, 'impl'),  # NEGA
    0x35: ('AND dp', 2, 3, 'dp'),  # AND dp
    0x36: ('ASL dp', 5, 5, 'dpx'),  # ASL dp
    0x37: ('ASL dp', 5, 5, 'dpx'),  # ASL dp
    0x38: ('SEC', 1, 2, 'impl'),  # SEC
    0x39: ('ORA abs', 4, 4, 'abs'),  # ORA abs
    0x3A: ('DEC A', 1, 2, 'impl'),  # DEC A
    0x3B: ('TCD', 1, 0, 'impl'),  # TCD
    0x3C: ('BIT abs', 3, 3, 'abs'),  # BIT abs
    0x3D: ('AND abs', 3, 4, 'abs'),  # AND abs
    0x3E: ('ROL', 2, 6, 'abs'),  # ROL
    0x3F: ('ROL', 2, 6, 'abs'),  # ROL
    0x40: ('RTI', 1, 6, 'impl'),  # RTI
    0x41: ('EOR (ind,X)', 6, 6, 'indx'),  # EOR (ind,X)
    0x42: ('WDM', 2, 2, 'impl'),  # WDM
    0x43: ('MVA', 1, 4, 'impl'),  # MVA
    0x44: ('MVN', 1, 4, 'impl'),  # MVN
    0x45: ('EOR dp', 3, 3, 'dp'),  # EOR dp
    0x46: ('LSR dp', 5, 5, 'dpx'),  # LSR dp
    0x47: ('LSR dp', 5, 5, 'dpx'),  # LSR dp
    0x48: ('PHA', 1, 3, 'impl'),  # PHA
    0x49: ('EOR #imm', 2, 2, 'imm'),  # EOR #imm
    0x4A: ('LSR A', 1, 2, 'impl'),  # LSR A
    0x4B: ('PHK', 1, 3, 'impl'),  # PHK
    0x4C: ('JMP', 3, 3, 'abs'),  # JMP
    0x4D: ('EOR abs', 3, 4, 'abs'),  # EOR abs
    0x4E: ('LSR', 2, 6, 'abs'),  # LSR
    0x4F: ('LSR', 2, 6, 'abs'),  # LSR
    0x50: ('BVC', 2, 2, 'rel'),  # BVC
    0x51: ('EOR (ind,S),Y', 5, 5, 'indy'),  # EOR (ind,S),Y
    0x52: ('EOR dp', 2, 3, 'dp'),  # EOR dp
    0x53: ('EOR (ind,S),Y', 5, 5, 'indy'),  # EOR (ind,S),Y
    0x54: ('NEG dp', 3, 3, 'dp'),  # NEG dp
    0x55: ('EOR dp', 3, 3, 'dp'),  # EOR dp
    0x56: ('LSR dp', 5, 5, 'dpx'),  # LSR dp
    0x57: ('LSR dp', 5, 5, 'dpx'),  # LSR dp
    0x58: ('CLI', 1, 2, 'impl'),  # CLI
    0x59: ('ORA abs', 4, 4, 'abs'),  # ORA abs
    0x5A: ('PHY', 1, 3, 'impl'),  # PHY
    0x5B: ('TCD', 1, 0, 'impl'),  # TCD
    0x5C: ('JMP', 3, 3, 'abs'),  # JMP
    0x5D: ('TCD', 1, 0, 'impl'),  # TCD
    0x5E: ('EOR', 2, 6, 'abs'),  # EOR
    0x5F: ('EOR', 2, 6, 'abs'),  # EOR
    0x60: ('RTS', 1, 6, 'impl'),  # RTS
    0x61: ('ADC (ind,X)', 6, 6, 'indx'),  # ADC (ind,X)
    0x62: ('PEI dp', 3, 5, 'dpi'),  # PEI dp
    0x44: ('MVN', 1, 4, 'impl'),  # MVN
    0x65: ('ADC dp', 3, 3, 'dp'),  # ADC dp
    0x66: ('INC dp', 5, 5, 'dpx'),  # INC dp
    0x67: ('INC dp', 5, 5, 'dpx'),  # INC dp
    0x68: ('INX', 1, 2, 'impl'),  # INX
    0x69: ('ADC #imm', 2, 2, 'imm'),  # ADC #imm
    0x6A: ('ROR A', 1, 2, 'impl'),  # ROR A
    0x6B: ('RTL', 1, 6, 'impl'),  # RTL
    0x6C: ('JMP', 3, 3, 'abs'),  # JMP
    0x6D: ('ADC abs', 3, 4, 'abs'),  # ADC abs
    0x6E: ('ROR', 2, 6, 'abs'),  # ROR
    0x6F: ('ROR', 2, 6, 'abs'),  # ROR
    0x70: ('BVS', 2, 2, 'rel'),  # BVS
    0x71: ('ADC (ind,S),Y', 5, 5, 'indy'),  # ADC (ind,S),Y
    0x72: ('EOR dp', 2, 3, 'dp'),  # EOR dp
    0x73: ('EOR (ind,S),Y', 5, 5, 'indy'),  # EOR (ind,S),Y
    0x74: ('MVD', 1, 4, 'impl'),  # MVD
    0x75: ('EOR dp', 3, 3, 'dp'),  # EOR dp
    0x76: ('INC dp', 5, 5, 'dpx'),  # INC dp
    0x77: ('INC dp', 5, 5, 'dpx'),  # INC dp
    0x78: ('SEI', 1, 2, 'impl'),  # SEI
    0x79: ('ADC abs', 3, 4, 'abs'),  # ADC abs
    0x7A: ('PLY', 1, 4, 'impl'),  # PLY
    0x7B: ('TDC', 1, 0, 'impl'),  # TDC
    0x7C: ('MVD', 1, 4, 'impl'),  # MVD
    0x7D: ('TCD', 1, 0, 'impl'),  # TCD
    0x7E: ('EOR', 2, 6, 'abs'),  # EOR
    0x7F: ('EOR', 2, 6, 'abs'),  # EOR
    0x80: ('BRA', 2, 3, 'rel'),  # BRA
    0x81: ('STA (ind,X)', 6, 6, 'indx'),  # STA (ind,X)
    0x82: ('STA (ind,S)', 6, 6, 'indx'),  # STA (ind,S)
    0x83: ('MVA', 1, 4, 'impl'),  # MVA
    0x84: ('STY dp', 3, 3, 'dpy'),  # STY dp
    0x85: ('STA dp', 3, 3, 'dp'),  # STA dp
    0x86: ('STX dp', 3, 3, 'dpx'),  # STX dp
    0x87: ('STX dp', 3, 3, 'dpx'),  # STX dp
    0x88: ('DEY', 1, 2, 'impl'),  # DEY
    0x89: ('BIT #imm', 2, 2, 'imm'),  # BIT #imm
    0x8A: ('TXA', 1, 2, 'impl'),  # TXA
    0x8B: ('PHK', 1, 3, 'impl'),  # PHK
    0x8C: ('STY abs', 3, 4, 'abs'),  # STY abs
    0x8D: ('STA abs', 3, 4, 'abs'),  # STA abs
    0x8E: ('STX abs', 3, 4, 'abs'),  # STX abs
    0x8F: ('STX abs', 3, 4, 'abs'),  # STX abs
    0x90: ('BCC', 2, 2, 'rel'),  # BCC
    0x91: ('STA (ind,X)', 6, 6, 'indx'),  # STA (ind,X)
    0x92: ('STA dp', 3, 3, 'dp'),  # STA dp
    0x93: ('STA (ind,S),Y', 5, 5, 'indy'),  # STA (ind,S),Y
    0x94: ('STY dp', 3, 3, 'dpy'),  # STY dp
    0x95: ('STA dp', 3, 3, 'dp'),  # STA dp
    0x96: ('STX dp', 3, 3, 'dpx'),  # STX dp
    0x97: ('STX dp', 3, 3, 'dpx'),  # STX dp
    0x98: ('TYA', 1, 2, 'impl'),  # TYA
    0x99: ('STA abs', 3, 4, 'abs'),  # STA abs
    0x9A: ('TXS', 1, 2, 'impl'),  # TXS
    0x9B: ('TXY', 1, 2, 'impl'),  # TXY
    0x9C: ('STZ dp', 3, 3, 'dpy'),  # STZ dp
    0x9D: ('STA abs', 3, 4, 'abs'),  # STA abs
    0x9E: ('STZ dp', 3, 3, 'dpy'),  # STZ dp
    0x9F: ('STA abs', 3, 4, 'abs'),  # STA abs
    0xA0: ('LDY #imm', 2, 2, 'imm'),  # LDY #imm
    0xA1: ('LDA (ind,X)', 6, 6, 'indx'),  # LDA (ind,X)
    0xA2: ('LDX #imm', 2, 2, 'imm'),  # LDX #imm
    0xA3: ('MVA', 1, 4, 'impl'),  # MVA
    0xA4: ('LDY dp', 3, 3, 'dpy'),  # LDY dp
    0xA5: ('LDA dp', 3, 3, 'dp'),  # LDA dp
    0xA6: ('LDX dp', 3, 3, 'dpx'),  # LDX dp
    0xA7: ('LDX dp', 3, 3, 'dpx'),  # LDX dp
    0xA8: ('TAY', 1, 2, 'impl'),  # TAY
    0xA9: ('LDA #imm', 2, 2, 'imm'),  # LDA #imm
    0xAA: ('TAX', 1, 2, 'impl'),  # TAX
    0xAB: ('PHK', 1, 3, 'impl'),  # PHK
    0xAC: ('LDY dp', 3, 3, 'dpy'),  # LDY dp
    0xAD: ('LDA abs', 3, 4, 'abs'),  # LDA abs
    0xAE: ('LDX abs', 3, 4, 'abs'),  # LDX abs
    0xAF: ('LDA abs', 3, 4, 'abs'),  # LDA abs
    0xB0: ('BCS', 2, 2, 'rel'),  # BCS
    0xB1: ('LDA (ind,X)', 6, 6, 'indx'),  # LDA (ind,X)
    0xB2: ('LDA dp', 3, 3, 'dp'),  # LDA dp
    0xB3: ('MVA', 1, 4, 'impl'),  # MVA
    0xB4: ('LDY dp', 3, 3, 'dpy'),  # LDY dp
    0xB5: ('LDA dp', 3, 3, 'dp'),  # LDA dp
    0xB6: ('LDX dp', 3, 3, 'dpx'),  # LDX dp
    0xB7: ('LDX dp', 3, 3, 'dpx'),  # LDX dp
    0xB8: ('CLV', 1, 2, 'impl'),  # CLV
    0xB9: ('LDA abs', 3, 4, 'abs'),  # LDA abs
    0xBA: ('TSX', 1, 2, 'impl'),  # TSX
    0xBB: ('TXY', 1, 2, 'impl'),  # TXY
    0xBC: ('LDY abs', 3, 4, 'abs'),  # LDY abs
    0xBD: ('LDA abs', 3, 4, 'abs'),  # LDA abs
    0xBE: ('LDX abs', 3, 4, 'abs'),  # LDX abs
    0xBF: ('LDX abs', 3, 4, 'abs'),  # LDX abs
    0xC0: ('CPY #imm', 2, 2, 'imm'),  # CPY #imm
    0xC1: ('CMP (ind,X)', 6, 6, 'indx'),  # CMP (ind,X)
    0xC2: ('REP #imm', 3, 3, 'imm'),  # REP #imm
    0xC3: ('SBC (ind,X)', 6, 6, 'indx'),  # SBC (ind,X)
    0xC4: ('CPY dp', 3, 3, 'dp'),  # CPY dp
    0xC5: ('CMP dp', 3, 3, 'dp'),  # CMP dp
    0xC6: ('DEC dp', 3, 3, 'dp'),  # DEC dp
    0xC7: ('DEC dp', 3, 3, 'dp'),  # DEC dp
    0xC8: ('INX', 1, 2, 'impl'),  # INX
    0xC9: ('CMP #imm', 2, 2, 'imm'),  # CMP #imm
    0xCA: ('DEX', 1, 2, 'impl'),  # DEX
    0xCB: ('WAI', 1, 3, 'impl'),  # WAI
    0xCC: ('CPY abs', 3, 3, 'abs'),  # CPY abs
    0xCD: ('CMP abs', 3, 4, 'abs'),  # CMP abs
    0xCE: ('DEC abs', 3, 5, 'abs'),  # DEC abs
    0xCF: ('EOR abs', 3, 4, 'abs'),  # EOR abs
    0xD0: ('BNE', 2, 2, 'rel'),  # BNE
    0xD1: ('CMP (ind,X)', 6, 6, 'indx'),  # CMP (ind,X)
    0xD2: ('CMP dp', 3, 3, 'dp'),  # CMP dp
    0xD3: ('CMP (ind,S),Y', 5, 5, 'indy'),  # CMP (ind,S),Y
    0xD4: ('TRB dp', 3, 3, 'dp'),  # TRB dp
    0xD5: ('CMP dp', 3, 3, 'dp'),  # CMP dp
    0xD6: ('INC dp', 3, 3, 'dp'),  # INC dp
    0xD7: ('INC dp', 3, 3, 'dp'),  # INC dp
    0xD8: ('CLD', 1, 2, 'impl'),  # CLD
    0xD9: ('CMP #imm', 2, 2, 'imm'),  # CMP #imm
    0xDA: ('PHX', 1, 3, 'impl'),  # PHX
    0xDB: ('SBC abs', 3, 4, 'abs'),  # SBC abs
    0xDC: ('TRB abs', 3, 5, 'abs'),  # TRB abs
    0xDD: ('CMP abs', 3, 4, 'abs'),  # CMP abs
    0xDE: ('DEC abs', 3, 6, 'abs'),  # DEC abs
    0xDF: ('EOR abs', 3, 4, 'abs'),  # EOR abs
    0xE0: ('CPX #imm', 2, 2, 'imm'),  # CPX #imm
    0xE1: ('SBC (ind,X)', 6, 6, 'indx'),  # SBC (ind,X)
    0xE2: ('SEP #imm', 3, 3, 'imm'),  # SEP #imm
    0xE3: ('MVC', 1, 4, 'impl'),  # MVC
    0xE4: ('CPX dp', 3, 3, 'dp'),  # CPX dp
    0xE5: ('SBC dp', 3, 3, 'dp'),  # SBC dp
    0xE6: ('INC dp', 3, 3, 'dp'),  # INC dp
    0xE7: ('INC dp', 3, 3, 'dp'),  # INC dp
    0xE8: ('INX', 1, 2, 'impl'),  # INX
    0xE9: ('SBC #imm', 2, 2, 'imm'),  # SBC #imm
    0xEA: ('NOP', 1, 2, 'impl'),  # NOP
    0xEB: ('SBC #imm', 2, 2, 'imm'),  # SBC #imm
    0xEC: ('CPX abs', 3, 3, 'abs'),  # CPX abs
    0xED: ('SBC abs', 3, 4, 'abs'),  # SBC abs
    0xEE: ('INC abs', 3, 5, 'abs'),  # INC abs
    0xEF: ('EOR abs', 3, 4, 'abs'),  # EOR abs
    0xF0: ('BEQ', 2, 2, 'rel'),  # BEQ
    0xF1: ('SBC (ind,X)', 6, 6, 'indx'),  # SBC (ind,X)
    0xF2: ('SBC dp', 3, 3, 'dp'),  # SBC dp
    0xF3: ('SBC (ind,S),Y', 5, 5, 'indy'),  # SBC (ind,S),Y
    0xF4: ('TRB dp', 3, 3, 'dp'),  # TRB dp
    0xF5: ('SBC dp', 3, 3, 'dp'),  # SBC dp
    0xF6: ('INC dp', 3, 3, 'dp'),  # INC dp
    0xF7: ('INC dp', 3, 3, 'dp'),  # INC dp
    0xF8: ('SED', 1, 2, 'impl'),  # SED
    0xF9: ('SBC #imm', 2, 2, 'imm'),  # SBC #imm
    0xFA: ('PLX', 1, 4, 'impl'),  # PLX
    0xFB: ('XCE', 1, 2, 'impl'),  # XCE
    0xFC: ('INC dp', 3, 3, 'dp'),  # INC dp
    0xFD: ('SBC abs', 3, 4, 'abs'),  # SBC abs
    0xFE: ('INC abs', 3, 5, 'abs'),  # INC abs
    0xFF: ('INC abs', 3, 5, 'abs'),  # INC abs
}

# Addressing mode encoding
ADDR_MODE = {
    'impl': 0,  # Implied
    'acc': 1,   # Accumulator
    'imm': 2,   # Immediate
    'abs': 3,   # Absolute
    'absx': 4,  # Absolute,X
    'absy': 5,  # Absolute,Y
    'ind': 6,   # Indirect
    'indx': 7,  # (ind,X)
    'indy': 8,  # (ind),Y
    'dp': 9,    # Direct page
    'dpx': 10,  # Direct page,X
    'dpy': 11,  # Direct page,Y
    'indlong': 12, # [ind]
    'rel': 13,  # Relative
    'rella': 14, # Relative long
    'indlongy': 15, # [ind],Y
    'dpi': 16,  # (dp)
    'dpily': 17, # (dp),Y
    'rel8': 18, # 8-bit relative
    'rella': 19, # 16-bit relative
}


@dataclass
class Instruction:
    address: int
    bank: int
    opcode: int
    bytes: List[int]
    mnemonic: str
    size: int
    cycles: int
    addr_mode: int
    operands: List[int] = field(default_factory=list)
    is_branch: bool = False
    branch_target: Optional[int] = None
    is_call: bool = False
    call_target: Optional[int] = None
    is_return: bool = False
    is_branch_long: bool = False
    is_branch_short: bool = False


@dataclass
class BasicBlock:
    start_addr: int
    bank: int
    instructions: List[Instruction] = field(default_factory=list)
    successors: List[Tuple[int, int]] = field(default_factory=list)  # (addr, bank)
    predecessors: List[Tuple[int, int]] = field(default_factory=list)
    label: str = ""


@dataclass
class Function:
    name: str
    blocks: List[BasicBlock] = field(default_factory=list)
    entry_addr: int = 0
    entry_bank: int = 0


class ROMAnalyzer:
    def __init__(self, rom_path: str):
        self.rom_path = Path(rom_path)
        with open(rom_path, 'rb') as f:
            self.rom = f.read()
            self.rom_size = len(self.rom)

    def get_bank_offset(self, bank: int, addr: int) -> int:
        """Convert bank:address to file offset for LoROM"""
        return ((bank & 0x7F) << 15) | (addr & 0x7FFF)

    def read_byte(self, bank: int, addr: int) -> int:
        offset = self.get_bank_offset(bank, addr)
        if offset < len(self.rom):
            return self.rom[offset]
        return 0

    def read_word(self, bank: int, addr: int) -> int:
        lo = self.read_byte(bank, addr)
        hi = self.read_byte(bank, (addr + 1) & 0xFFFF)
        return (hi << 8) | lo

    def read_long(self, bank: int, addr: int) -> int:
        b0 = self.read_byte(bank, addr)
        b1 = self.read_byte(bank, (addr + 1) & 0xFFFF)
        b2 = self.read_byte(bank, (addr + 2) & 0xFFFF)
        return (b2 << 16) | (b1 << 8) | b0

    def decode_instruction(self, bank: int, pc: int) -> Instruction:
        offset = self.get_bank_offset(bank, pc)
        if offset >= len(self.rom):
            return Instruction(pc, bank, 0x00, [0], 'UNK', 1, 2, 0)
        opcode = self.rom[offset]
        if opcode not in OPCODES:
            return Instruction(pc, bank, opcode, [opcode], f'UNK_{opcode:02X}', 1, 2, 0)

        name, size, cycles, addr_mode = OPCODES[opcode]
        bytes_read = [self.read_byte(bank, (pc + i) & 0xFFFF) for i in range(size)]

        instr = Instruction(
            address=pc,
            bank=bank,
            opcode=opcode,
            bytes=bytes_read,
            mnemonic=name,
            size=size,
            cycles=cycles,
            addr_mode=ADDR_MODE.get(addr_mode, 0),
        )

        # Decode operands
        if size > 1:
            instr.operands = bytes_read[1:]

        # Detect branches
        if name in ('BPL', 'BMI', 'BVC', 'BVS', 'BCC', 'BCS', 'BNE', 'BEQ', 'BRA', 'BRL'):
            instr.is_branch = True
            rel = bytes_read[1]
            if rel & 0x80:
                rel -= 256
            instr.branch_target = (pc + size + rel) & 0xFFFF
            instr.is_branch_short = True

        # Long branches
        if name == 'BRL':
            instr.is_branch = True
            instr.is_branch_long = True
            target = (bytes_read[1] | (bytes_read[2] << 8))
            if target & 0x8000:
                target -= 65536
            instr.branch_target = (pc + 3 + target) & 0xFFFF

        # Jumps and calls
        if name in ('JMP', 'JML', 'JSR', 'JSL'):
            if name in ('JMP', 'JSR'):
                target = bytes_read[1] | (bytes_read[2] << 8)
            else:
                target = bytes_read[1] | (bytes_read[2] << 8) | (bytes_read[3] << 16)
            if name in ('JSR', 'JSL'):
                instr.is_call = True
            else:
                instr.is_call = False
            instr.call_target = target

        if name in ('RTS', 'RTL', 'RTI'):
            instr.is_return = True

        return instr

    def disassemble_range(self, bank: int, start: int, end: int) -> List[Instruction]:
        instructions = []
        pc = start
        while pc < end:
            instr = self.decode_instruction(bank, pc)
            instructions.append(instr)
            pc = (pc + instr.size) & 0xFFFF
            if instr.size == 0:
                break
        return instructions

    def find_entry_points(self) -> List[Tuple[int, int, str]]:
        """Find all entry points (vectors)"""
        entry_points = []

        # Reset vector at $7FFC-$7FFD (bank 0, LoROM)
        rst_pc = self.read_word(0, 0x7FFC)
        rst_bank = self.read_byte(0, 0x7FFE)
        entry_points.append((rst_pc, rst_bank & 0x0F, 'RESET'))

        # NMI vector
        nmi_pc = self.read_word(0, 0x7FFA)
        nmi_bank = self.read_byte(0, 0x7FFC)
        entry_points.append((nmi_pc, nmi_bank & 0x0F, 'NMI'))

        # IRQ/BRK vector
        irq_pc = self.read_word(0, 0x7FFE)
        irq_bank = self.read_byte(0, 0x7FFF)
        entry_points.append((irq_pc, irq_bank & 0x0F, 'IRQ'))

        # COP vector
        cop_pc = self.read_word(0, 0x7FF4)
        cop_bank = self.read_byte(0, 0x7FF6)
        entry_points.append((cop_pc, cop_bank & 0x0F, 'COP'))

        # ABORT vector
        abt_pc = self.read_word(0, 0x7FF8)
        abt_bank = self.read_byte(0, 0x7FFA)
        entry_points.append((abt_pc, abt_bank & 0x0F, 'ABORT'))

        # BRK vector
        brk_pc = self.read_word(0, 0x7FF6)
        brk_bank = self.read_byte(0, 0x7FF8)
        entry_points.append((brk_pc, brk_bank & 0x0F, 'BRK'))

        # NMI vector (bank 0)
        nmi_pc = self.read_word(0, 0xFFFA)
        nmi_bank = 0
        entry_points.append((nmi_pc, nmi_bank, 'NMI(0)'))

        # Reset vector (bank 0)
        rst_pc = self.read_word(0, 0xFFFC)
        entry_points.append((rst_pc, 0, 'RESET(0)'))

        # IRQ/BRK vector (bank 0)
        irq_pc = self.read_word(0, 0xFFFE)
        entry_points.append((irq_pc, 0, 'IRQ/BRK(0)'))

        # COP vector (bank 0)
        cop_pc = self.read_word(0, 0xFFF4)
        entry_points.append((cop_pc, 0, 'COP(0)'))

        # ABORT vector (bank 0)
        abt_pc = self.read_word(0, 0xFFF8)
        entry_points.append((abt_pc, 0, 'ABORT(0)'))

        # BRK vector (bank 0)
        brk_pc = self.read_word(0, 0xFFFE)
        entry_points.append((brk_pc, 0, 'BRK(0)'))

        return entry_points

    def trace_code(self, start_bank: int, start_pc: int, max_instructions: int = 100000) -> Dict[Tuple[int, int], Instruction]:
        """Trace code from entry point, returning all reachable instructions"""
        visited = {}
        work_queue = deque([(start_bank, start_pc)])

        while work_queue and len(visited) < max_instructions:
            bank, pc = work_queue.popleft()
            key = (bank, pc)

            if key in visited:
                continue

            # Check if valid ROM address
            offset = self.get_bank_offset(bank, pc)
            if offset >= len(self.rom):
                continue

            instr = self.decode_instruction(bank, pc)
            visited[(bank, pc)] = instr

            # Add successors
            if instr.is_branch and instr.branch_target is not None:
                target_bank = bank  # Branch stays in same bank
                work_queue.append((target_bank, instr.branch_target))

            if instr.is_call and instr.call_target is not None:
                call_bank = bank
                work_queue.append((call_bank, instr.call_target))

            if not instr.is_return and not instr.is_branch and not instr.is_call:
                next_pc = (pc + instr.size) & 0xFFFF
                work_queue.append((bank, next_pc))

            if instr.is_return:
                # Return - we can't statically determine target, but we know it continues
                pass

        return visited

    def trace_all(self, max_instructions: int = 500000) -> Dict[Tuple[int, int], Instruction]:
        """Trace from all entry points"""
        all_instructions = {}
        entry_points = self.find_entry_points()

        print(f"Found {len(entry_points)} entry points:")
        for pc, bank, name in entry_points:
            print(f"  {name}: bank={bank:02X}, pc={pc:04X}")

        for pc, bank, name in entry_points:
            traced = self.trace_code(bank, pc, max_instructions)
            print(f"  {name}: traced {len(traced)} instructions")
            all_instructions.update(traced)

        return all_instructions


class BasicBlockBuilder:
    def __init__(self, instructions: Dict[Tuple[int, int], Instruction]):
        self.instructions = instructions
        self.blocks: Dict[Tuple[int, int], BasicBlock] = {}
        self.block_map: Dict[Tuple[int, int], BasicBlock] = {}

    def build(self) -> Dict[Tuple[int, int], BasicBlock]:
        # Find block leaders
        leaders = set()
        for (bank, pc), instr in self.instructions.items():
            leaders.add((instr.bank, instr.address))
            # Branch targets are leaders
            if instr.is_branch and instr.branch_target is not None:
                leaders.add((instr.bank, instr.branch_target))
            if instr.is_call and instr.call_target is not None:
                leaders.add((instr.bank, instr.call_target))

            # Next instruction after branch/call/return
            if instr.is_branch or instr.is_call or instr.is_return:
                next_pc = (instr.address + instr.size) & 0xFFFF
                leaders.add((instr.bank, next_pc))
        # Sort leaders by bank, then address
        sorted_leaders = sorted(leaders, key=lambda x: (x[0], x[1]))

        # Build blocks
        leader_to_block = {}
        for i, (bank, addr) in enumerate(sorted_leaders):
            # Find end of this block (next leader or end of instructions)
            end_addr = 0xFFFF
            if i + 1 < len(sorted_leaders):
                next_bank, next_addr = sorted_leaders[i + 1]
                if next_bank == bank:
                    end_addr = next_addr
                else:
                    end_addr = 0xFFFF
            else:
                end_addr = 0xFFFF

            # Collect instructions in this block
            block_instructions = []
            pc = addr
            while pc != end_addr and (bank, pc) in self.instructions:
                instr = self.instructions[(bank, pc)]
                block_instructions.append(instr)
                pc = (pc + instr.size) & 0xFFFF
                if instr.is_return or instr.is_branch or instr.is_call:
                    break

            if block_instructions:
                block = BasicBlock(
                    start_addr=addr,
                    bank=bank,
                    instructions=block_instructions,
                    label=f"bb_{bank:02X}_{addr:04X}"
                )
                self.blocks[(bank, addr)] = block
                leader_to_block[(bank, addr)] = block

        # Build successor/predecessor links
        for block in self.blocks.values():
            last_instr = block.instructions[-1]

            if last_instr.is_branch and last_instr.branch_target is not None:
                target = (last_instr.bank, last_instr.branch_target)
                if target in self.blocks:
                    block.successors.append(target)
                    self.blocks[target].predecessors.append((block.bank, block.start_addr))

            if last_instr.is_call and last_instr.call_target is not None:
                target = (last_instr.bank, last_instr.call_target)
                if target in self.blocks:
                    block.successors.append(target)
                    self.blocks[target].predecessors.append((block.bank, block.start_addr))

            if not last_instr.is_return and not last_instr.is_branch and not last_instr.is_call:
                next_pc = (last_instr.address + last_instr.size) & 0xFFFF
                target = (last_instr.bank, next_pc)
                if target in self.blocks:
                    block.successors.append(target)
                    self.blocks[target].predecessors.append((block.bank, block.start_addr))

        return self.blocks


class CCodeGenerator:
    def __init__(self, blocks: Dict[Tuple[int, int], BasicBlock]):
        self.blocks = blocks
        self.output = []

    def generate(self) -> str:
        self.output = []
        self.output.append("/* Utopia W65C816 Static Dispatch - Generated */")
        self.output.append("#include \"ut_v11_runtime.h\"")
        self.output.append("#include \"ut_v11_cpu.h\"")
        self.output.append("#include <stdint.h>")
        self.output.append("")

        # Forward declarations for all block functions
        self.output.append("/* Forward declarations */")
        for (bank, addr), block in sorted(self.blocks.items()):
            self.output.append(f"static void {block.label}(SCV11Runtime* runtime);")
        self.output.append("")

        # Generate function for each block
        for (bank, addr), block in sorted(self.blocks.items()):
            self.generate_block(block)

        # Generate dispatch table
        self.generate_dispatch_table()

        return "\n".join(self.output)

    def generate_block(self, block: BasicBlock):
        self.output.append(f"")
        self.output.append(f"/* Block {block.label} at bank={block.bank:02X} addr={block.start_addr:04X} */")
        self.output.append(f"static void {block.label}(SCV11Runtime* runtime) {{")

        for instr in block.instructions:
            self.generate_instruction(instr)

        # Handle block termination
        last = block.instructions[-1]
        if last.is_return:
            self.output.append("    return;")
        elif last.is_branch and last.branch_target is not None:
            target_label = f"bb_{last.bank:02X}_{last.branch_target:04X}"
            self.output.append(f"    {target_label}(runtime);")
            self.output.append("    return;")
        elif last.is_call and last.call_target is not None:
            target_label = f"bb_{last.bank:02X}_{last.call_target:04X}"
            self.output.append(f"    {target_label}(runtime);")
            self.output.append("    return;")
        elif not (last.is_branch or last.is_call or last.is_return):
            # Fall through
            next_pc = (last.address + last.size) & 0xFFFF
            target_label = f"bb_{last.bank:02X}_{next_pc:04X}"
            if (last.bank, next_pc) in self.blocks:
                self.output.append(f"    {target_label}(runtime);")
            else:
                self.output.append("    return;")

        self.output.append("}")
        self.output.append("")

    def generate_instruction(self, instr: Instruction):
        # This is a simplified version - real implementation would generate full C code
        self.output.append(f"    /* {instr.mnemonic} {bytes(instr.bytes).hex()} */")
        # Real implementation would generate actual CPU emulation code
        self.output.append(f"    /* TODO: implement {instr.mnemonic} */")
        # Update PC
        self.output.append(f"    runtime->machine.cpu.pc = 0x{(instr.address + instr.size) & 0xFFFF:04X}u;")

    def generate_dispatch_table(self):
        self.output.append("")
        self.output.append("/* Dispatch table */")
        self.output.append("typedef void (*BlockFunc)(SCV11Runtime*);")
        self.output.append("static const struct {")
        self.output.append("    uint16_t pc;")
        self.output.append("    uint16_t bank;")
        self.output.append("    BlockFunc func;")
        self.output.append("} dispatch_table[] = {")

        for (bank, addr), block in sorted(self.blocks.items()):
            self.output.append(f"    {{ 0x{addr:04X}, 0x{bank:02X}, {block.label} }},")

        self.output.append("    { 0xFFFF, 0xFF, NULL }")
        self.output.append("};")
        self.output.append("")

        # Dispatch function
        self.output.append("int sc_v11_static_step(SCV11Runtime* runtime) {")
        self.output.append("    if (!runtime || runtime->route_failed) return 0;")
        self.output.append("")
        self.output.append("    uint16_t pc = runtime->machine.cpu.pc;")
        self.output.append("    uint16_t bank = runtime->machine.cpu.bank;")
        self.output.append("")
        self.output.append("    for (size_t i = 0; dispatch_table[i].func; i++) {")
        self.output.append("        if (dispatch_table[i].pc == pc && dispatch_table[i].bank == bank) {")
        self.output.append("            dispatch_table[i].func(runtime);")
        self.output.append("            return 1;")
        self.output.append("        }")
        self.output.append("    }")
        self.output.append("")
        self.output.append("    runtime->scheduler.cpu_instructions++;")
        self.output.append("    runtime->scheduler.master_clock += 6;")
        self.output.append("    runtime->machine.cpu.pc = (uint16_t)(pc + 1);")
        self.output.append("    return 1;")
        self.output.append("}")


def main():
    if len(sys.argv) < 2:
        print("Usage: python3 generate.py <rom_file>")
        sys.exit(1)

    rom_path = sys.argv[1]
    print(f"Analyzing ROM: {rom_path}")

    analyzer = ROMAnalyzer(rom_path)

    # Trace all reachable code
    print("Tracing code from entry points...")
    instructions = analyzer.trace_all(max_instructions=200000)
    print(f"Total instructions traced: {len(instructions)}")

    # Build basic blocks
    print("Building basic blocks...")
    builder = BasicBlockBuilder(instructions)
    blocks = builder.build()
    print(f"Built {len(blocks)} basic blocks")

    # Generate C code
    print("Generating C code...")
    generator = CCodeGenerator(blocks)
    c_code = generator.generate()

    # Write output
    output_path = Path("static-recomp/generated/ut_v23_static_dispatch.c")
    output_path.parent.mkdir(parents=True, exist_ok=True)
    with open(output_path, 'w') as f:
        f.write(c_code)

    print(f"Generated {output_path}")
    print("Done!")


if __name__ == '__main__':
    main()
