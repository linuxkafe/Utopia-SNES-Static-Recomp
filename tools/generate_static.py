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
        self.output.append("#include \"ut_static_helpers.h\"")
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
        """Generate C code implementing a single W65C816 instruction."""
        mnemonic = instr.mnemonic.upper()
        operands = instr.operands
        bytes_hex = bytes(instr.bytes).hex().upper()
        addr_mode = instr.addr_mode
        next_pc = (instr.address + instr.size) & 0xFFFF

        # Comment with instruction details
        self.output.append(f"    /* {instr.mnemonic} {bytes(instr.bytes).hex()} */")

        # Dispatch by mnemonic
        handlers = {
            'BRK': self._emit_brk,
            'BRA': self._emit_bra,
            'BPL': self._emit_bpl,
            'BMI': self._emit_bmi,
            'BVC': self._emit_bvc,
            'BEQ': self._emit_beq,
            'ASL': self._emit_asl,
            'LSR': self._emit_lsr,
            'ROL': self._emit_rol,
            'ROR': self._emit_ror,
            'STZ': self._emit_stz,
            'AND': self._emit_and,
            'ORA': self._emit_ora,
            'EOR': self._emit_eor,
            'ADC': self._emit_adc,
            'SBC': self._emit_sbc,
            'CMP': self._emit_cmp,
            'CPX': self._emit_cpx,
            'CPY': self._emit_cpy,
            'LDA': self._emit_lda,
            'LDX': self._emit_ldx,
            'LDY': self._emit_ldy,
            'STA': self._emit_sta,
            'STX': self._emit_stx,
            'STY': self._emit_sty,
            'INC': self._emit_inc,
            'DEC': self._emit_dec,
            'INX': self._emit_inx,
            'INY': self._emit_iny,
            'DEX': self._emit_dex,
            'DEY': self._emit_dey,
            'PHA': self._emit_pha,
            'PHP': self._emit_php,
            'PHX': self._emit_phx,
            'PHY': self._emit_phy,
            'PLA': self._emit_pla,
            'PLP': self._emit_plp,
            'PLX': self._emit_plx,
            'PLY': self._emit_ply,
            'PHK': self._emit_phk,
            'TAX': self._emit_tax,
            'TAY': self._emit_tay,
            'TXA': self._emit_txa,
            'TYA': self._emit_tya,
            'TXS': self._emit_txs,
            'TSX': self._emit_tsx,
            'TCD': self._emit_tcd,
            'TDC': self._emit_tdc,
            'TSD': self._emit_tsd,
            'SED': self._emit_sed,
            'CLD': self._emit_cld,
            'CLC': self._emit_clc,
            'SEC': self._emit_sec,
            'CLI': self._emit_cli,
            'SEI': self._emit_sei,
            'CLV': self._emit_clv,
            'REP': self._emit_rep,
            'SEP': self._emit_sep,
            'RTS': self._emit_rts,
            'RTI': self._emit_rti,
            'JMP': self._emit_jmp,
            'JSR': self._emit_jsr,
            'WDM': self._emit_wdm,
            'MVA': self._emit_mva,
            'MVD': self._emit_mvd,
            'NEG': self._emit_neg,
            'PHD': self._emit_phd,
            'PLD': self._emit_pld,
        }
        
        handler = handlers.get(mnemonic)
        if handler:
            handler(instr)
        else:
            self.output.append(f"    /* TODO: {instr.mnemonic} */")
            self.output.append(f"    runtime->route_failed = 1; return;")

        # Note: PC is updated within each emitter for control-flow instructions
        # For non-control-flow, we don't update PC here since next instruction
        # in block will handle it or fall-through logic handles it

    # ========== ADDRESSING MODE HELPERS ==========

    def _emit_addr_dp(self):
        """Direct page (1-byte operand)"""
        self.output.append("        uint16_t addr = (uint16_t)runtime->machine.cpu.d;")  # will be operand
        self.output.append("        (void)addr;")
        self.output.append("        /* direct page operand consumed */")
        # Actually need to consume operand - this is handled by instruction bytes
        # Let me re-think: use a simpler approach
        pass

    def _emit_effective_addr_abs(self):
        """Absolute addressing"""
        self.output.append("        uint16_t abs_addr = runtime->machine.bytes[1] | ((uint16_t)runtime->machine.bytes[2] << 8);")

    def _emit_effective_addr_absx(self):
        """Absolute,X addressing"""
        self.output.append("        uint16_t absx_addr = runtime->machine.bytes[1] | ((uint16_t)runtime->machine.bytes[2] << 8);")
        self.output.append("        if ((absx_addr & 0xFF00) != ((absx_addr + runtime->machine.cpu.x) & 0xFF00)) absx_addr += 0x100;")
        self.output.append("        absx_addr = (absx_addr + runtime->machine.cpu.x) & 0xFFFF;")

    def _emit_effective_addr_absy(self):
        """Absolute,Y addressing"""
        self.output.append("        uint16_t absy_addr = runtime->machine.bytes[1] | ((uint16_t)runtime->machine.bytes[2] << 8);")
        self.output.append("        absy_addr = (absy_addr + runtime->machine.cpu.y) & 0xFFFF;")

    def _emit_effective_addr_indx(self):
        """(Indirect,X) addressing"""
        self.output.append("        uint16_t zp_x = (runtime->machine.bytes[1] + runtime->machine.cpu.x) & 0xFF;")
        self.output.append("        uint16_t ind_addr = rom_read(runtime, zp_x) | ((uint16_t)rom_read(runtime, (zp_x + 1) & 0xFF) << 8);")

    def _emit_effective_addr_indy(self):
        """(Indirect),Y addressing"""
        self.output.append("        uint16_t zp = runtime->machine.bytes[1];")
        self.output.append("        uint16_t ind_addr = rom_read(runtime, zp) | ((uint16_t)rom_read(runtime, (zp + 1) & 0xFF) << 8);")
        self.output.append("        ind_addr = (ind_addr + runtime->machine.cpu.y) & 0xFFFF;")

    def _emit_read_operand(self, var="op"):
        """Read operand from memory"""
        self.output.append(f"        uint8_t {var} = rom_read(runtime, addr);")

    def _emit_write_operand(self, val):
        """Write operand to memory"""
        self.output.append(f"        rom_write(runtime, addr, {val});")

    # ========== OPCODE EMITTERS ==========

    def _emit_brk(self, instr):
        """BRK - Force Break / Software Interrupt"""
        self.output.append("    /* BRK - software interrupt */")
        self.output.append("    {")
        self.output.append("        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */")
        self.output.append("        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));")
        self.output.append("        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));")
        self.output.append("        stack_push(runtime, status);")
        self.output.append("        runtime->machine.cpu.status |= 0x14; /* I and B flags */")
        self.output.append("        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);")
        self.output.append("        runtime->machine.cpu.pc = brk_pc;")
        self.output.append("        runtime->machine.cpu.bank = 0x00;")
        self.output.append("        runtime->scheduler.cpu_instructions += 7;")
        self.output.append("        runtime->scheduler.master_clock += 8;")
        self.output.append("        return;")
        self.output.append("    }")

    def _emit_bra(self, instr):
        """BRA - Branch Always (relative 8-bit)"""
        offset = instr.operands[0] if instr.operands else 0
        # Sign-extend 8-bit offset
        if offset & 0x80:
            offset |= 0xFF00
        target = (instr.address + instr.size + offset) & 0xFFFF
        self.output.append(f"    /* BRA ${offset:02X} -> ${target:04X} */")
        self.output.append(f"    runtime->machine.cpu.pc = 0x{target:04X}u;")
        self.output.append("    runtime->scheduler.cpu_instructions += 3;")
        self.output.append("    runtime->scheduler.master_clock += 3;")
        self.output.append("    return;")

    def _emit_bpl(self, instr):
        """BPL - Branch if Positive (N=0)"""
        offset = instr.operands[0] if instr.operands else 0
        if offset & 0x80:
            offset |= 0xFF00
        target = (instr.address + instr.size + offset) & 0xFFFF
        next_pc = (instr.address + instr.size) & 0xFFFF
        self.output.append(f"    /* BPL -> ${target:04X} if N=0 */")
        self.output.append("    if ((runtime->machine.cpu.status & 0x80) == 0) {")
        self.output.append(f"        runtime->machine.cpu.pc = 0x{target:04X}u;")
        self.output.append("        runtime->scheduler.cpu_instructions += 4;")
        self.output.append("        runtime->scheduler.master_clock += 4;")
        self.output.append("    } else {")
        self.output.append("        runtime->scheduler.cpu_instructions += 2;")
        self.output.append("        runtime->scheduler.master_clock += 2;")
        self.output.append("    }")
        self.output.append("    return;")

    def _emit_asl(self, instr):
        """ASL - Arithmetic Shift Left (accumulator or memory)"""
        if len(instr.operands) == 0:
            # ASL A (accumulator)
            self.output.append("    /* ASL A */")
            self.output.append("    {")
            self.output.append("        uint8_t val = runtime->machine.cpu.a;")
            self.output.append("        uint8_t carry = (val & 0x80) != 0;")
            self.output.append("        runtime->machine.cpu.a = (val << 1) & 0xFF;")
            self.output.append("        if (carry) runtime->machine.cpu.status |= 0x01; else runtime->machine.cpu.status &= ~0x01;")
            self.output.append("        if ((runtime->machine.cpu.a & 0x80) != 0) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("        if (runtime->machine.cpu.a == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            self.output.append("        runtime->scheduler.cpu_instructions += 2;")
            self.output.append("        runtime->scheduler.master_clock += 2;")
            self.output.append("    }")
        else:
            # ASL dp / ASL abs / ASL abs,X - memory operations
            self._emit_asl_memory(instr)

    def _emit_stz(self, instr):
        """STZ - Store Zero"""
        if instr.addr_mode == 9:  # dp
            self.output.append("    /* STZ dp */")
            self.output.append("    {")
            self.output.append("        uint16_t addr = runtime->machine.bytes[1];")
            self.output.append("        wram_write(runtime, addr, 0);")
            self.output.append("        runtime->scheduler.cpu_instructions += 3;")
            self.output.append("        runtime->scheduler.master_clock += 3;")
            self.output.append("    }")
        elif instr.addr_mode == 3:  # abs
            self.output.append("    /* STZ abs */")
            self.output.append("    {")
            self.output.append("        uint16_t addr = runtime->machine.bytes[1] | ((uint16_t)runtime->machine.bytes[2] << 8);")
            self.output.append("        wram_write(runtime, addr, 0);")
            self.output.append("        runtime->scheduler.cpu_instructions += 4;")
            self.output.append("        runtime->scheduler.master_clock += 4;")
            self.output.append("    }")
        else:
            self.output.append("    /* STZ stub */")
            self.output.append("    runtime->route_failed = 1; return;")
        return

    def _emit_and(self, instr):
        """AND - Logical AND (all addressing modes)"""
        if instr.addr_mode == 2:  # immediate
            val = instr.operands[0] if instr.operands else 0
            self.output.append(f"    /* AND #${val:02X} */")
            self.output.append(f"    runtime->machine.cpu.a &= 0x{val:02X};")
            self.output.append("    if (runtime->machine.cpu.a & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("    if (runtime->machine.cpu.a == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            self.output.append("    runtime->scheduler.cpu_instructions += 2;")
            self.output.append("    runtime->scheduler.master_clock += 2;")
        elif instr.addr_mode in [3, 7, 8, 9]:
            self.output.append("    /* AND memory */")
            self.output.append("    {")
            if instr.addr_mode == 9:  # dp
                self.output.append("        uint16_t addr = runtime->machine.bytes[1];")
            elif instr.addr_mode == 3:  # abs
                self.output.append("        uint16_t addr = runtime->machine.bytes[1] | ((uint16_t)runtime->machine.bytes[2] << 8);")
            elif instr.addr_mode == 7:  # (ind,X)
                self.output.append("        uint16_t zp = (runtime->machine.bytes[1] + runtime->machine.cpu.x) & 0xFF;")
                self.output.append("        uint16_t addr = rom_read(runtime, zp) | ((uint16_t)rom_read(runtime, (zp + 1) & 0xFF) << 8);")
            else:  # (ind),Y
                self.output.append("        uint16_t zp = runtime->machine.bytes[1];")
                self.output.append("        uint16_t addr = rom_read(runtime, zp) | ((uint16_t)rom_read(runtime, (zp + 1) & 0xFF) << 8);")
                self.output.append("        addr = (addr + runtime->machine.cpu.y) & 0xFFFF;")
            self.output.append("        uint8_t op = rom_read(runtime, addr);")
            self.output.append("        runtime->machine.cpu.a &= op;")
            self.output.append("        if (runtime->machine.cpu.a & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("        if (runtime->machine.cpu.a == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            cyc = {9: 3, 3: 4, 7: 6, 8: 5}.get(instr.addr_mode, 4)
            self.output.append(f"        runtime->scheduler.cpu_instructions += {cyc};")
            self.output.append(f"        runtime->scheduler.master_clock += {cyc};")
            self.output.append("    }")
        else:
            self.output.append("    /* AND stub */")
            self.output.append("    runtime->route_failed = 1; return;")

    def _emit_phk(self, instr):
        """PHK - Push Program Bank Register"""
        self.output.append("    /* PHK */")
        self.output.append("    stack_push(runtime, runtime->machine.cpu.bank);")
        self.output.append("    runtime->scheduler.cpu_instructions += 3;")
        self.output.append("    runtime->scheduler.master_clock += 3;")

    def _emit_tsd(self, instr):
        """TSD - Transfer Stack to Direct"""
        self.output.append("    /* TSD - Transfer Stack Pointer to Direct Page */")
        self.output.append("    runtime->machine.cpu.d = runtime->machine.cpu.sp;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_lda(self, instr):
        """LDA - Load Accumulator (all addressing modes)"""
        operands = instr.operands
        if len(operands) == 0:
            self.output.append("    /* LDA (no operand) */")
            self.output.append("    runtime->route_failed = 1; return;")
        elif instr.addr_mode == 2:  # immediate
            val = operands[0] if len(operands) > 0 else 0
            self.output.append(f"    /* LDA #${val:02X} */")
            self.output.append(f"    runtime->machine.cpu.a = 0x{val:02X};")
            self.output.append("    if (runtime->machine.cpu.a & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("    if (runtime->machine.cpu.a == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            self.output.append("    runtime->scheduler.cpu_instructions += 2;")
            self.output.append("    runtime->scheduler.master_clock += 2;")
        elif instr.addr_mode == 9:  # direct page
            self.output.append("    /* LDA dp */")
            self.output.append("    {")
            self.output.append("        uint16_t addr = runtime->machine.bytes[1];")
            self.output.append("        runtime->machine.cpu.a = rom_read(runtime, addr);")
            self.output.append("        if (runtime->machine.cpu.a & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("        if (runtime->machine.cpu.a == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            self.output.append("        runtime->scheduler.cpu_instructions += 3;")
            self.output.append("        runtime->scheduler.master_clock += 3;")
            self.output.append("    }")
        elif instr.addr_mode == 3:  # absolute
            self.output.append("    /* LDA abs */")
            self.output.append("    {")
            self.output.append("        uint16_t addr = runtime->machine.bytes[1] | ((uint16_t)runtime->machine.bytes[2] << 8);")
            self.output.append("        runtime->machine.cpu.a = rom_read(runtime, addr);")
            self.output.append("        if (runtime->machine.cpu.a & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("        if (runtime->machine.cpu.a == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            self.output.append("        runtime->scheduler.cpu_instructions += 4;")
            self.output.append("        runtime->scheduler.master_clock += 4;")
            self.output.append("    }")
        elif instr.addr_mode == 7:  # (ind,X)
            self.output.append("    /* LDA (ind,X) */")
            self.output.append("    {")
            self.output.append("        uint16_t zp = (runtime->machine.bytes[1] + runtime->machine.cpu.x) & 0xFF;")
            self.output.append("        uint16_t addr = rom_read(runtime, zp) | ((uint16_t)rom_read(runtime, (zp + 1) & 0xFF) << 8);")
            self.output.append("        runtime->machine.cpu.a = rom_read(runtime, addr);")
            self.output.append("        if (runtime->machine.cpu.a & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("        if (runtime->machine.cpu.a == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            self.output.append("        runtime->scheduler.cpu_instructions += 6;")
            self.output.append("        runtime->scheduler.master_clock += 6;")
            self.output.append("    }")
        elif instr.addr_mode == 8:  # (ind),Y
            self.output.append("    /* LDA (ind),Y */")
            self.output.append("    {")
            self.output.append("        uint16_t zp = runtime->machine.bytes[1];")
            self.output.append("        uint16_t addr = rom_read(runtime, zp) | ((uint16_t)rom_read(runtime, (zp + 1) & 0xFF) << 8);")
            self.output.append("        addr = (addr + runtime->machine.cpu.y) & 0xFFFF;")
            self.output.append("        runtime->machine.cpu.a = rom_read(runtime, addr);")
            self.output.append("        if (runtime->machine.cpu.a & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("        if (runtime->machine.cpu.a == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            self.output.append("        runtime->scheduler.cpu_instructions += 5;")
            self.output.append("        runtime->scheduler.master_clock += 5;")
            self.output.append("    }")
        else:
            self.output.append(f"    /* LDA mode={instr.addr_mode} - stub */")
            self.output.append("    runtime->route_failed = 1; return;")

    def _emit_sed(self, instr):
        """SED - Set Decimal Flag"""
        self.output.append("    /* SED - Set Decimal Mode */")
        self.output.append("    runtime->machine.cpu.status |= 0x08;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_tcd(self, instr):
        """TCD - Transfer Accumulator to Direct Page Register"""
        self.output.append("    /* TCD - Transfer A to Direct Page */")
        self.output.append("    runtime->machine.cpu.d = runtime->machine.cpu.a;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_sei(self, instr):
        """SEI - Set Interrupt Disable"""
        self.output.append("    /* SEI - Disable Interrupts */")
        self.output.append("    runtime->machine.cpu.status |= 0x04;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_inc(self, instr):
        """INC - Increment Memory/Register"""
        if instr.addr_mode == 9:  # dp
            self.output.append("    /* INC dp */")
            self.output.append("    {")
            self.output.append("        uint16_t addr = runtime->machine.bytes[1];")
            self.output.append("        uint8_t val = wram_read(runtime, addr);")
            self.output.append("        val++;")
            self.output.append("        wram_write(runtime, addr, val);")
            self.output.append("        if (val & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("        if (val == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            self.output.append("        runtime->scheduler.cpu_instructions += 5;")
            self.output.append("        runtime->scheduler.master_clock += 5;")
            self.output.append("    }")
        elif instr.addr_mode == 3:  # abs
            self.output.append("    /* INC abs */")
            self.output.append("    {")
            self.output.append("        uint16_t addr = runtime->machine.bytes[1] | ((uint16_t)runtime->machine.bytes[2] << 8);")
            self.output.append("        uint8_t val = wram_read(runtime, addr);")
            self.output.append("        val++;")
            self.output.append("        wram_write(runtime, addr, val);")
            self.output.append("        if (val & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("        if (val == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            self.output.append("        runtime->scheduler.cpu_instructions += 6;")
            self.output.append("        runtime->scheduler.master_clock += 6;")
            self.output.append("    }")
        elif instr.addr_mode == 4:  # abs,X
            self.output.append("    /* INC abs,X */")
            self.output.append("    {")
            self.output.append("        uint16_t base = runtime->machine.bytes[1] | ((uint16_t)runtime->machine.bytes[2] << 8);")
            self.output.append("        uint16_t addr = (base + runtime->machine.cpu.x) & 0xFFFF;")
            self.output.append("        uint8_t val = wram_read(runtime, addr);")
            self.output.append("        val++;")
            self.output.append("        wram_write(runtime, addr, val);")
            self.output.append("        if (val & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("        if (val == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            self.output.append("        runtime->scheduler.cpu_instructions += 7;")
            self.output.append("        runtime->scheduler.master_clock += 7;")
            self.output.append("    }")
        else:
            self.output.append("    /* INC stub */")
            self.output.append("    runtime->route_failed = 1; return;")

    def _emit_wdm(self, instr):
        """WDM - Reserved (No Operation)"""
        self.output.append("    /* WDM - Reserved */")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_ror(self, instr):
        """ROR - Rotate Right"""
        if len(instr.operands) == 0:
            self.output.append("    /* ROR A */")
            self.output.append("    {")
            self.output.append("        uint8_t val = runtime->machine.cpu.a;")
            self.output.append("        uint8_t carry = val & 0x01;")
            self.output.append("        uint8_t new_carry = (runtime->machine.cpu.status & 0x01) != 0;")
            self.output.append("        runtime->machine.cpu.a = (val >> 1) | (new_carry << 7);")
            self.output.append("        if (carry) runtime->machine.cpu.status |= 0x01; else runtime->machine.cpu.status &= ~0x01;")
            self.output.append("        if ((runtime->machine.cpu.a & 0x80) != 0) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("        if (runtime->machine.cpu.a == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            self.output.append("        runtime->scheduler.cpu_instructions += 2;")
            self.output.append("        runtime->scheduler.master_clock += 2;")
            self.output.append("    }")
        else:
            self.output.append("    /* ROR memory */")
            self.output.append("    runtime->route_failed = 1;  /* TODO: ROR memory */")
            self.output.append("    return;")

    def _emit_bvc(self, instr):
        """BVC - Branch if Overflow Clear"""
        offset = instr.operands[0] if instr.operands else 0
        if offset & 0x80:
            offset |= 0xFF00
        target = (instr.address + instr.size + offset) & 0xFFFF
        self.output.append(f"    /* BVC -> ${target:04X} if V=0 */")
        self.output.append("    if ((runtime->machine.cpu.status & 0x40) == 0) {")
        self.output.append(f"        runtime->machine.cpu.pc = 0x{target:04X}u;")
        self.output.append("        runtime->scheduler.cpu_instructions += 4;")
        self.output.append("        runtime->scheduler.master_clock += 4;")
        self.output.append("    } else {")
        self.output.append("        runtime->scheduler.cpu_instructions += 2;")
        self.output.append("        runtime->scheduler.master_clock += 2;")
        self.output.append("    }")
        self.output.append("    return;")

    def _emit_ldx(self, instr):
        """LDX - Load X Register"""
        if instr.addr_mode == 2:  # immediate
            val = instr.operands[0] if instr.operands else 0
            self.output.append(f"    /* LDX #${val:02X} */")
            self.output.append(f"    runtime->machine.cpu.x = 0x{val:02X};")
            self.output.append("    if (runtime->machine.cpu.x & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("    if (runtime->machine.cpu.x == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            self.output.append("    runtime->scheduler.cpu_instructions += 2;")
            self.output.append("    runtime->scheduler.master_clock += 2;")
        elif instr.addr_mode in [3, 7, 8, 9]:
            self.output.append("    /* LDX memory */")
            self.output.append("    {")
            if instr.addr_mode == 9:
                self.output.append("        uint16_t addr = runtime->machine.bytes[1];")
            elif instr.addr_mode == 3:
                self.output.append("        uint16_t addr = runtime->machine.bytes[1] | ((uint16_t)runtime->machine.bytes[2] << 8);")
            elif instr.addr_mode == 7:
                self.output.append("        uint16_t zp = (runtime->machine.bytes[1] + runtime->machine.cpu.x) & 0xFF;")
                self.output.append("        uint16_t addr = rom_read(runtime, zp) | ((uint16_t)rom_read(runtime, (zp + 1) & 0xFF) << 8);")
            else:
                self.output.append("        uint16_t zp = runtime->machine.bytes[1];")
                self.output.append("        uint16_t addr = rom_read(runtime, zp) | ((uint16_t)rom_read(runtime, (zp + 1) & 0xFF) << 8);")
                self.output.append("        addr = (addr + runtime->machine.cpu.y) & 0xFFFF;")
            self.output.append("        runtime->machine.cpu.x = rom_read(runtime, addr);")
            self.output.append("        if (runtime->machine.cpu.x & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("        if (runtime->machine.cpu.x == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            cyc = {9: 3, 3: 4, 7: 6, 8: 5}.get(instr.addr_mode, 4)
            self.output.append(f"        runtime->scheduler.cpu_instructions += {cyc};")
            self.output.append(f"        runtime->scheduler.master_clock += {cyc};")
            self.output.append("    }")
        else:
            self.output.append("    /* LDX stub */")
            self.output.append("    runtime->route_failed = 1; return;")

    def _emit_cpy(self, instr):
        """CPY - Compare Y Register"""
        if instr.addr_mode == 2:  # immediate
            val = instr.operands[0] if instr.operands else 0
            self.output.append(f"    /* CPY #${val:02X} */")
            self.output.append("    {")
            self.output.append("        int diff = (int)runtime->machine.cpu.y - (int)0x{:02X};".format(val))
            self.output.append("        if (diff >= 0) runtime->machine.cpu.status |= 0x01; else runtime->machine.cpu.status &= ~0x01;")
            self.output.append("        if (diff & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("        if (diff == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            self.output.append("        runtime->scheduler.cpu_instructions += 2;")
            self.output.append("        runtime->scheduler.master_clock += 2;")
            self.output.append("    }")
        elif instr.addr_mode in [3, 7, 8, 9]:
            self.output.append("    /* CPY memory */")
            self.output.append("    {")
            if instr.addr_mode == 9:
                self.output.append("        uint16_t addr = runtime->machine.bytes[1];")
            elif instr.addr_mode == 3:
                self.output.append("        uint16_t addr = runtime->machine.bytes[1] | ((uint16_t)runtime->machine.bytes[2] << 8);")
            elif instr.addr_mode == 7:
                self.output.append("        uint16_t zp = (runtime->machine.bytes[1] + runtime->machine.cpu.x) & 0xFF;")
                self.output.append("        uint16_t addr = rom_read(runtime, zp) | ((uint16_t)rom_read(runtime, (zp + 1) & 0xFF) << 8);")
            else:
                self.output.append("        uint16_t zp = runtime->machine.bytes[1];")
                self.output.append("        uint16_t addr = rom_read(runtime, zp) | ((uint16_t)rom_read(runtime, (zp + 1) & 0xFF) << 8);")
                self.output.append("        addr = (addr + runtime->machine.cpu.y) & 0xFFFF;")
            self.output.append("        uint8_t op = rom_read(runtime, addr);")
            self.output.append("        int diff = (int)runtime->machine.cpu.y - (int)op;")
            self.output.append("        if (diff >= 0) runtime->machine.cpu.status |= 0x01; else runtime->machine.cpu.status &= ~0x01;")
            self.output.append("        if (diff & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("        if (diff == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            cyc = {9: 3, 3: 4, 7: 6, 8: 5}.get(instr.addr_mode, 4)
            self.output.append(f"        runtime->scheduler.cpu_instructions += {cyc};")
            self.output.append(f"        runtime->scheduler.master_clock += {cyc};")
            self.output.append("    }")
        else:
            self.output.append("    /* CPY stub */")
            self.output.append("    runtime->route_failed = 1; return;")

    def _emit_ora(self, instr):
        """ORA - Logical OR (all addressing modes)"""
        if instr.addr_mode == 2:  # immediate
            val = instr.operands[0] if instr.operands else 0
            self.output.append(f"    /* ORA #${val:02X} */")
            self.output.append(f"    runtime->machine.cpu.a |= 0x{val:02X};")
            self.output.append("    if (runtime->machine.cpu.a & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("    if (runtime->machine.cpu.a == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            self.output.append("    runtime->scheduler.cpu_instructions += 2;")
            self.output.append("    runtime->scheduler.master_clock += 2;")
        elif instr.addr_mode in [3, 7, 8, 9]:
            self.output.append("    /* ORA memory */")
            self.output.append("    {")
            if instr.addr_mode == 9:  # dp
                self.output.append("        uint16_t addr = runtime->machine.bytes[1];")
            elif instr.addr_mode == 3:  # abs
                self.output.append("        uint16_t addr = runtime->machine.bytes[1] | ((uint16_t)runtime->machine.bytes[2] << 8);")
            elif instr.addr_mode == 7:  # (ind,X)
                self.output.append("        uint16_t zp = (runtime->machine.bytes[1] + runtime->machine.cpu.x) & 0xFF;")
                self.output.append("        uint16_t addr = rom_read(runtime, zp) | ((uint16_t)rom_read(runtime, (zp + 1) & 0xFF) << 8);")
            else:  # (ind),Y
                self.output.append("        uint16_t zp = runtime->machine.bytes[1];")
                self.output.append("        uint16_t addr = rom_read(runtime, zp) | ((uint16_t)rom_read(runtime, (zp + 1) & 0xFF) << 8);")
                self.output.append("        addr = (addr + runtime->machine.cpu.y) & 0xFFFF;")
            self.output.append("        uint8_t op = rom_read(runtime, addr);")
            self.output.append("        runtime->machine.cpu.a |= op;")
            self.output.append("        if (runtime->machine.cpu.a & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("        if (runtime->machine.cpu.a == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            cyc = {9: 3, 3: 4, 7: 6, 8: 5}.get(instr.addr_mode, 4)
            self.output.append(f"        runtime->scheduler.cpu_instructions += {cyc};")
            self.output.append(f"        runtime->scheduler.master_clock += {cyc};")
            self.output.append("    }")
        else:
            self.output.append("    /* ORA stub */")
            self.output.append("    runtime->route_failed = 1; return;")

    def _emit_phx(self, instr):
        """PHX - Push X Register"""
        self.output.append("    /* PHX */")
        self.output.append("    stack_push(runtime, runtime->machine.cpu.x);")
        self.output.append("    runtime->scheduler.cpu_instructions += 3;")
        self.output.append("    runtime->scheduler.master_clock += 3;")

    def _emit_cpx(self, instr):
        """CPX - Compare X Register"""
        if instr.addr_mode == 2:  # immediate
            val = instr.operands[0] if instr.operands else 0
            self.output.append(f"    /* CPX #${val:02X} */")
            self.output.append("    {")
            self.output.append("        int diff = (int)runtime->machine.cpu.x - (int)0x{:02X};".format(val))
            self.output.append("        if (diff >= 0) runtime->machine.cpu.status |= 0x01; else runtime->machine.cpu.status &= ~0x01;")
            self.output.append("        if (diff & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("        if (diff == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            self.output.append("        runtime->scheduler.cpu_instructions += 2;")
            self.output.append("        runtime->scheduler.master_clock += 2;")
            self.output.append("    }")
        elif instr.addr_mode in [3, 7, 8, 9]:
            self.output.append("    /* CPX memory */")
            self.output.append("    {")
            if instr.addr_mode == 9:
                self.output.append("        uint16_t addr = runtime->machine.bytes[1];")
            elif instr.addr_mode == 3:
                self.output.append("        uint16_t addr = runtime->machine.bytes[1] | ((uint16_t)runtime->machine.bytes[2] << 8);")
            elif instr.addr_mode == 7:
                self.output.append("        uint16_t zp = (runtime->machine.bytes[1] + runtime->machine.cpu.x) & 0xFF;")
                self.output.append("        uint16_t addr = rom_read(runtime, zp) | ((uint16_t)rom_read(runtime, (zp + 1) & 0xFF) << 8);")
            else:
                self.output.append("        uint16_t zp = runtime->machine.bytes[1];")
                self.output.append("        uint16_t addr = rom_read(runtime, zp) | ((uint16_t)rom_read(runtime, (zp + 1) & 0xFF) << 8);")
                self.output.append("        addr = (addr + runtime->machine.cpu.y) & 0xFFFF;")
            self.output.append("        uint8_t op = rom_read(runtime, addr);")
            self.output.append("        int diff = (int)runtime->machine.cpu.x - (int)op;")
            self.output.append("        if (diff >= 0) runtime->machine.cpu.status |= 0x01; else runtime->machine.cpu.status &= ~0x01;")
            self.output.append("        if (diff & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("        if (diff == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            cyc = {9: 3, 3: 4, 7: 6, 8: 5}.get(instr.addr_mode, 4)
            self.output.append(f"        runtime->scheduler.cpu_instructions += {cyc};")
            self.output.append(f"        runtime->scheduler.master_clock += {cyc};")
            self.output.append("    }")
        else:
            self.output.append("    /* CPX stub */")
            self.output.append("    runtime->route_failed = 1; return;")

    def _emit_rep(self, instr):
        """REP - Reset Status Bits"""
        mask = instr.operands[0] if instr.operands else 0
        self.output.append(f"    /* REP #${mask:02X} */")
        self.output.append(f"    runtime->machine.cpu.status &= ~0x{mask:02X};")
        self.output.append("    runtime->scheduler.cpu_instructions += 3;")
        self.output.append("    runtime->scheduler.master_clock += 3;")

    def _emit_phd(self, instr):
        """PHD - Push Direct Page Register"""
        self.output.append("    /* PHD */")
        self.output.append("    stack_push(runtime, (uint8_t)(runtime->machine.cpu.d >> 8));")
        self.output.append("    stack_push(runtime, (uint8_t)runtime->machine.cpu.d);")
        self.output.append("    runtime->scheduler.cpu_instructions += 4;")
        self.output.append("    runtime->scheduler.master_clock += 4;")

    def _emit_sta(self, instr):
        """STA - Store Accumulator (all addressing modes)"""
        if instr.addr_mode == 9:  # direct page
            self.output.append("    /* STA dp */")
            self.output.append("    {")
            self.output.append("        uint16_t addr = runtime->machine.bytes[1];")
            self.output.append("        wram_write(runtime, addr, runtime->machine.cpu.a);")
            self.output.append("        io_write(runtime, addr, runtime->machine.cpu.a);")
            self.output.append("        runtime->scheduler.cpu_instructions += 3;")
            self.output.append("        runtime->scheduler.master_clock += 3;")
            self.output.append("    }")
        elif instr.addr_mode == 3:  # absolute
            self.output.append("    /* STA abs */")
            self.output.append("    {")
            self.output.append("        uint16_t addr = runtime->machine.bytes[1] | ((uint16_t)runtime->machine.bytes[2] << 8);")
            self.output.append("        wram_write(runtime, addr, runtime->machine.cpu.a);")
            self.output.append("        io_write(runtime, addr, runtime->machine.cpu.a);")
            self.output.append("        runtime->scheduler.cpu_instructions += 4;")
            self.output.append("        runtime->scheduler.master_clock += 4;")
            self.output.append("    }")
        elif instr.addr_mode == 7:  # (ind,X)
            self.output.append("    /* STA (ind,X) */")
            self.output.append("    {")
            self.output.append("        uint16_t zp = (runtime->machine.bytes[1] + runtime->machine.cpu.x) & 0xFF;")
            self.output.append("        uint16_t addr = rom_read(runtime, zp) | ((uint16_t)rom_read(runtime, (zp + 1) & 0xFF) << 8);")
            self.output.append("        wram_write(runtime, addr, runtime->machine.cpu.a);")
            self.output.append("        io_write(runtime, addr, runtime->machine.cpu.a);")
            self.output.append("        runtime->scheduler.cpu_instructions += 6;")
            self.output.append("        runtime->scheduler.master_clock += 6;")
            self.output.append("    }")
        elif instr.addr_mode == 8:  # (ind),Y
            self.output.append("    /* STA (ind),Y */")
            self.output.append("    {")
            self.output.append("        uint16_t zp = runtime->machine.bytes[1];")
            self.output.append("        uint16_t addr = rom_read(runtime, zp) | ((uint16_t)rom_read(runtime, (zp + 1) & 0xFF) << 8);")
            self.output.append("        addr = (addr + runtime->machine.cpu.y) & 0xFFFF;")
            self.output.append("        wram_write(runtime, addr, runtime->machine.cpu.a);")
            self.output.append("        io_write(runtime, addr, runtime->machine.cpu.a);")
            self.output.append("        runtime->scheduler.cpu_instructions += 6;")
            self.output.append("        runtime->scheduler.master_clock += 6;")
            self.output.append("    }")
        else:
            self.output.append(f"    /* STA mode={instr.addr_mode} - stub */")
            self.output.append("    runtime->route_failed = 1; return;")

    def _emit_rts(self, instr):
        """RTS - Return from Subroutine"""
        self.output.append("    /* RTS */")
        self.output.append("    {")
        self.output.append("        uint16_t pc_lo = stack_pop(runtime);")
        self.output.append("        uint16_t pc_hi = stack_pop(runtime);")
        self.output.append("        runtime->machine.cpu.pc = (uint16_t)((pc_hi << 8) | pc_lo) + 1;")
        self.output.append("        runtime->scheduler.cpu_instructions += 6;")
        self.output.append("        runtime->scheduler.master_clock += 6;")
        self.output.append("        return;")
        self.output.append("    }")

    def _emit_neg(self, instr):
        """NEG - Negate Memory"""
        self.output.append("    /* NEG */")
        self.output.append("    runtime->route_failed = 1;  /* TODO: implement NEG */")
        self.output.append("    return;")

    def _emit_asl_memory(self, instr):
        """ASL memory (dp, abs, abs,X, dp,X)"""
        if instr.addr_mode == 9:  # dp
            self.output.append("    /* ASL dp */")
            self.output.append("    {")
            self.output.append("        uint16_t addr = runtime->machine.bytes[1];")
            self.output.append("        uint8_t val = wram_read(runtime, addr);")
            self.output.append("        uint8_t carry = (val & 0x80) != 0;")
            self.output.append("        val = (val << 1) & 0xFF;")
            self.output.append("        wram_write(runtime, addr, val);")
            self.output.append("        if (carry) runtime->machine.cpu.status |= 0x01; else runtime->machine.cpu.status &= ~0x01;")
            self.output.append("        if (val & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("        if (val == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            self.output.append("        runtime->scheduler.cpu_instructions += 5;")
            self.output.append("        runtime->scheduler.master_clock += 5;")
            self.output.append("    }")
        elif instr.addr_mode == 3:  # abs
            self.output.append("    /* ASL abs */")
            self.output.append("    {")
            self.output.append("        uint16_t addr = runtime->machine.bytes[1] | ((uint16_t)runtime->machine.bytes[2] << 8);")
            self.output.append("        uint8_t val = wram_read(runtime, addr);")
            self.output.append("        uint8_t carry = (val & 0x80) != 0;")
            self.output.append("        val = (val << 1) & 0xFF;")
            self.output.append("        wram_write(runtime, addr, val);")
            self.output.append("        if (carry) runtime->machine.cpu.status |= 0x01; else runtime->machine.cpu.status &= ~0x01;")
            self.output.append("        if (val & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("        if (val == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            self.output.append("        runtime->scheduler.cpu_instructions += 6;")
            self.output.append("        runtime->scheduler.master_clock += 6;")
            self.output.append("    }")
        elif instr.addr_mode == 4:  # abs,X
            self.output.append("    /* ASL abs,X */")
            self.output.append("    {")
            self.output.append("        uint16_t base = runtime->machine.bytes[1] | ((uint16_t)runtime->machine.bytes[2] << 8);")
            self.output.append("        uint16_t addr = (base + runtime->machine.cpu.x) & 0xFFFF;")
            self.output.append("        uint8_t val = wram_read(runtime, addr);")
            self.output.append("        uint8_t carry = (val & 0x80) != 0;")
            self.output.append("        val = (val << 1) & 0xFF;")
            self.output.append("        wram_write(runtime, addr, val);")
            self.output.append("        if (carry) runtime->machine.cpu.status |= 0x01; else runtime->machine.cpu.status &= ~0x01;")
            self.output.append("        if (val & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("        if (val == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            self.output.append("        runtime->scheduler.cpu_instructions += 7;")
            self.output.append("        runtime->scheduler.master_clock += 7;")
            self.output.append("    }")
        else:
            self.output.append("    /* ASL memory stub */")
            self.output.append("    runtime->route_failed = 1; return;")

    def _emit_store_zero(self, instr):
        """STZ - Store Zero to memory"""
        self.output.append("    /* STZ memory */")
        self.output.append("    runtime->route_failed = 1;  /* TODO: STZ memory */")
        self.output.append("    return;")

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


    def _emit_eor(self, instr):
        """EOR - Exclusive OR"""
        self.output.append("    /* EOR */")
        self.output.append("    runtime->route_failed = 1; return;")

    def _emit_bmi(self, instr):
        """BMI - Branch if Minus (N=1)"""
        offset = instr.operands[0] if instr.operands else 0
        if offset & 0x80: offset |= 0xFF00
        target = (instr.address + instr.size + offset) & 0xFFFF
        self.output.append(f"    /* BMI -> ${target:04X} if N=1 */")
        self.output.append("    if ((runtime->machine.cpu.status & 0x80) != 0) {")
        self.output.append(f"        runtime->machine.cpu.pc = 0x{target:04X}u;")
        self.output.append("        runtime->scheduler.cpu_instructions += 4;")
        self.output.append("        runtime->scheduler.master_clock += 4;")
        self.output.append("    } else {")
        self.output.append("        runtime->scheduler.cpu_instructions += 2;")
        self.output.append("        runtime->scheduler.master_clock += 2;")
        self.output.append("    }")
        self.output.append("    return;")

    def _emit_beq(self, instr):
        """BEQ - Branch if Equal (Z=1)"""
        offset = instr.operands[0] if instr.operands else 0
        if offset & 0x80: offset |= 0xFF00
        target = (instr.address + instr.size + offset) & 0xFFFF
        self.output.append(f"    /* BEQ -> ${target:04X} if Z=1 */")
        self.output.append("    if ((runtime->machine.cpu.status & 0x02) != 0) {")
        self.output.append(f"        runtime->machine.cpu.pc = 0x{target:04X}u;")
        self.output.append("        runtime->scheduler.cpu_instructions += 4;")
        self.output.append("        runtime->scheduler.master_clock += 4;")
        self.output.append("    } else {")
        self.output.append("        runtime->scheduler.cpu_instructions += 2;")
        self.output.append("        runtime->scheduler.master_clock += 2;")
        self.output.append("    }")
        self.output.append("    return;")

    def _emit_dey(self, instr):
        """DEY - Decrement Y"""
        self.output.append("    /* DEY */")
        self.output.append("    runtime->machine.cpu.y = (runtime->machine.cpu.y - 1) & 0xFFFF;")
        self.output.append("    if (runtime->machine.cpu.y & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("    if (runtime->machine.cpu.y == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_dex(self, instr):
        """DEX - Decrement X"""
        self.output.append("    /* DEX */")
        self.output.append("    runtime->machine.cpu.x = (runtime->machine.cpu.x - 1) & 0xFFFF;")
        self.output.append("    if (runtime->machine.cpu.x & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("    if (runtime->machine.cpu.x == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_sbc(self, instr):
        """SBC - Subtract with Carry"""
        self.output.append("    /* SBC */")
        self.output.append("    runtime->route_failed = 1; return;")

    def _emit_sep(self, instr):
        """SEP - Set Status Bits"""
        mask = instr.operands[0] if instr.operands else 0
        self.output.append(f"    /* SEP #${mask:02X} */")
        self.output.append(f"    runtime->machine.cpu.status |= 0x{mask:02X};")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_rti(self, instr):
        """RTI - Return from Interrupt"""
        self.output.append("    /* RTI */")
        self.output.append("    {")
        self.output.append("        uint8_t status = stack_pop(runtime);")
        self.output.append("        uint16_t pc_lo = stack_pop(runtime);")
        self.output.append("        uint16_t pc_hi = stack_pop(runtime);")
        self.output.append("        runtime->machine.cpu.pc = (uint16_t)((pc_hi << 8) | pc_lo);")
        self.output.append("        runtime->machine.cpu.status = (status & ~0x30) | 0x20; /* clear B, set U */")
        self.output.append("        runtime->scheduler.cpu_instructions += 6;")
        self.output.append("        runtime->scheduler.master_clock += 6;")
        self.output.append("        return;")
        self.output.append("    }")

    def _emit_phy(self, instr):
        """PHY - Push Y"""
        self.output.append("    /* PHY */")
        self.output.append("    stack_push(runtime, (uint8_t)runtime->machine.cpu.y);")
        self.output.append("    runtime->scheduler.cpu_instructions += 3;")
        self.output.append("    runtime->scheduler.master_clock += 3;")

    def _emit_php(self, instr):
        """PHP - Push Processor Status"""
        self.output.append("    /* PHP */")
        self.output.append("    stack_push(runtime, runtime->machine.cpu.status | 0x30); /* B and U always 1 */")
        self.output.append("    runtime->scheduler.cpu_instructions += 3;")
        self.output.append("    runtime->scheduler.master_clock += 3;")

    def _emit_mva(self, instr):
        """MVA - Move Accumulator (placeholder)"""
        self.output.append("    /* MVA - nop */")
        self.output.append("    runtime->scheduler.cpu_instructions += 4;")
        self.output.append("    runtime->scheduler.master_clock += 4;")

    def _emit_mvd(self, instr):
        """MVD - Move Direct (placeholder)"""
        self.output.append("    /* MVD - nop */")
        self.output.append("    runtime->scheduler.cpu_instructions += 4;")
        self.output.append("    runtime->scheduler.master_clock += 4;")

    def _emit_neg(self, instr):
        """NEG - Negate (2's complement)"""
        self.output.append("    /* NEG */")
        self.output.append("    runtime->route_failed = 1; return;")

    # Additional opcode handlers
    def _emit_lsr(self, instr):
        """LSR - Logical Shift Right"""
        if len(instr.operands) == 0:
            self.output.append("    /* LSR A */")
            self.output.append("    {")
            self.output.append("        uint8_t val = runtime->machine.cpu.a;")
            self.output.append("        uint8_t carry = val & 0x01;")
            self.output.append("        runtime->machine.cpu.a = val >> 1;")
            self.output.append("        if (carry) runtime->machine.cpu.status |= 0x01; else runtime->machine.cpu.status &= ~0x01;")
            self.output.append("        if (runtime->machine.cpu.a & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("        if (runtime->machine.cpu.a == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            self.output.append("        runtime->scheduler.cpu_instructions += 2;")
            self.output.append("        runtime->scheduler.master_clock += 2;")
            self.output.append("    }")
        else:
            self.output.append("    /* LSR memory - stub */")
            self.output.append("    runtime->route_failed = 1; return;")

    def _emit_rol(self, instr):
        """ROL - Rotate Left"""
        if len(instr.operands) == 0:
            self.output.append("    /* ROL A */")
            self.output.append("    {")
            self.output.append("        uint8_t val = runtime->machine.cpu.a;")
            self.output.append("        uint8_t carry = val & 0x80;")
            self.output.append("        uint8_t new_carry = (runtime->machine.cpu.status & 0x01) != 0;")
            self.output.append("        runtime->machine.cpu.a = (val << 1) | new_carry;")
            self.output.append("        if (carry) runtime->machine.cpu.status |= 0x01; else runtime->machine.cpu.status &= ~0x01;")
            self.output.append("        if (runtime->machine.cpu.a & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("        if (runtime->machine.cpu.a == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            self.output.append("        runtime->scheduler.cpu_instructions += 2;")
            self.output.append("        runtime->scheduler.master_clock += 2;")
            self.output.append("    }")
        else:
            self.output.append("    /* ROL memory - stub */")
            self.output.append("    runtime->route_failed = 1; return;")

    def _emit_adc(self, instr):
        """ADC - Add with Carry"""
        self.output.append("    /* ADC - stub */")
        self.output.append("    runtime->route_failed = 1; return;")

    def _emit_sbc(self, instr):
        """SBC - Subtract with Carry"""
        self.output.append("    /* SBC - stub */")
        self.output.append("    runtime->route_failed = 1; return;")

    def _emit_cmp(self, instr):
        """CMP - Compare Accumulator"""
        self.output.append("    /* CMP - stub */")
        self.output.append("    runtime->route_failed = 1; return;")

    def _emit_ldy(self, instr):
        """LDY - Load Y Register"""
        if instr.addr_mode == 2:
            val = instr.operands[0] if instr.operands else 0
            self.output.append(f"    /* LDY #${val:02X} */")
            self.output.append(f"    runtime->machine.cpu.y = 0x{val:02X};")
            self.output.append("    if (runtime->machine.cpu.y & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("    if (runtime->machine.cpu.y == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            self.output.append("    runtime->scheduler.cpu_instructions += 2;")
            self.output.append("    runtime->scheduler.master_clock += 2;")
        else:
            self.output.append("    /* LDY memory - stub */")
            self.output.append("    runtime->route_failed = 1; return;")

    def _emit_stx(self, instr):
        """STX - Store X Register"""
        self.output.append("    /* STX - stub */")
        self.output.append("    runtime->route_failed = 1; return;")

    def _emit_sty(self, instr):
        """STY - Store Y Register"""
        self.output.append("    /* STY - stub */")
        self.output.append("    runtime->route_failed = 1; return;")

    def _emit_dec(self, instr):
        """DEC - Decrement Memory"""
        self.output.append("    /* DEC - stub */")
        self.output.append("    runtime->route_failed = 1; return;")

    def _emit_inx(self, instr):
        """INX - Increment X"""
        self.output.append("    /* INX */")
        self.output.append("    runtime->machine.cpu.x = (runtime->machine.cpu.x + 1) & 0xFFFF;")
        self.output.append("    if (runtime->machine.cpu.x & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("    if (runtime->machine.cpu.x == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_iny(self, instr):
        """INY - Increment Y"""
        self.output.append("    /* INY */")
        self.output.append("    runtime->machine.cpu.y = (runtime->machine.cpu.y + 1) & 0xFFFF;")
        self.output.append("    if (runtime->machine.cpu.y & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("    if (runtime->machine.cpu.y == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_pha(self, instr):
        """PHA - Push Accumulator"""
        self.output.append("    /* PHA */")
        self.output.append("    stack_push(runtime, (uint8_t)runtime->machine.cpu.a);")
        self.output.append("    runtime->scheduler.cpu_instructions += 3;")
        self.output.append("    runtime->scheduler.master_clock += 3;")

    def _emit_php(self, instr):
        """PHP - Push Processor Status"""
        self.output.append("    /* PHP */")
        self.output.append("    stack_push(runtime, runtime->machine.cpu.status | 0x30);")
        self.output.append("    runtime->scheduler.cpu_instructions += 3;")
        self.output.append("    runtime->scheduler.master_clock += 3;")

    def _emit_pla(self, instr):
        """PLA - Pull Accumulator"""
        self.output.append("    /* PLA */")
        self.output.append("    {")
        self.output.append("        uint8_t val = stack_pop(runtime);")
        self.output.append("        runtime->machine.cpu.a = val;")
        self.output.append("        if (val & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("        if (val == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("        runtime->scheduler.cpu_instructions += 4;")
        self.output.append("        runtime->scheduler.master_clock += 4;")
        self.output.append("    }")

    def _emit_plp(self, instr):
        """PLP - Pull Processor Status"""
        self.output.append("    /* PLP */")
        self.output.append("    {")
        self.output.append("        uint8_t status = stack_pop(runtime);")
        self.output.append("        runtime->machine.cpu.status = (status & ~0x30) | 0x20;")
        self.output.append("        runtime->scheduler.cpu_instructions += 4;")
        self.output.append("        runtime->scheduler.master_clock += 4;")
        self.output.append("    }")

    def _emit_plx(self, instr):
        """PLX - Pull X"""
        self.output.append("    /* PLX */")
        self.output.append("    {")
        self.output.append("        uint8_t val = stack_pop(runtime);")
        self.output.append("        runtime->machine.cpu.x = val;")
        self.output.append("        if (val & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("        if (val == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("        runtime->scheduler.cpu_instructions += 4;")
        self.output.append("        runtime->scheduler.master_clock += 4;")
        self.output.append("    }")

    def _emit_ply(self, instr):
        """PLY - Pull Y"""
        self.output.append("    /* PLY */")
        self.output.append("    {")
        self.output.append("        uint8_t val = stack_pop(runtime);")
        self.output.append("        runtime->machine.cpu.y = val;")
        self.output.append("        if (val & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("        if (val == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("        runtime->scheduler.cpu_instructions += 4;")
        self.output.append("        runtime->scheduler.master_clock += 4;")
        self.output.append("    }")

    def _emit_tax(self, instr):
        """TAX - Transfer A to X"""
        self.output.append("    /* TAX */")
        self.output.append("    runtime->machine.cpu.x = runtime->machine.cpu.a;")
        self.output.append("    if (runtime->machine.cpu.x & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("    if (runtime->machine.cpu.x == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_tay(self, instr):
        """TAY - Transfer A to Y"""
        self.output.append("    /* TAY */")
        self.output.append("    runtime->machine.cpu.y = runtime->machine.cpu.a;")
        self.output.append("    if (runtime->machine.cpu.y & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("    if (runtime->machine.cpu.y == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_txa(self, instr):
        """TXA - Transfer X to A"""
        self.output.append("    /* TXA */")
        self.output.append("    runtime->machine.cpu.a = runtime->machine.cpu.x;")
        self.output.append("    if (runtime->machine.cpu.a & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("    if (runtime->machine.cpu.a == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_tya(self, instr):
        """TYA - Transfer Y to A"""
        self.output.append("    /* TYA */")
        self.output.append("    runtime->machine.cpu.a = runtime->machine.cpu.y;")
        self.output.append("    if (runtime->machine.cpu.a & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("    if (runtime->machine.cpu.a == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_txs(self, instr):
        """TXS - Transfer X to Stack"""
        self.output.append("    /* TXS */")
        self.output.append("    runtime->machine.cpu.sp = (uint8_t)runtime->machine.cpu.x;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_tsx(self, instr):
        """TSX - Transfer Stack to X"""
        self.output.append("    /* TSX */")
        self.output.append("    runtime->machine.cpu.x = runtime->machine.cpu.sp;")
        self.output.append("    if (runtime->machine.cpu.x & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("    if (runtime->machine.cpu.x == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_tdc(self, instr):
        """TDC - Transfer Direct to A"""
        self.output.append("    /* TDC */")
        self.output.append("    runtime->machine.cpu.a = (uint8_t)runtime->machine.cpu.d;")
        self.output.append("    if (runtime->machine.cpu.a & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("    if (runtime->machine.cpu.a == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_cld(self, instr):
        """CLD - Clear Decimal"""
        self.output.append("    /* CLD */")
        self.output.append("    runtime->machine.cpu.status &= ~0x08;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_clc(self, instr):
        """CLC - Clear Carry"""
        self.output.append("    /* CLC */")
        self.output.append("    runtime->machine.cpu.status &= ~0x01;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_sec(self, instr):
        """SEC - Set Carry"""
        self.output.append("    /* SEC */")
        self.output.append("    runtime->machine.cpu.status |= 0x01;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_cli(self, instr):
        """CLI - Clear Interrupt Disable"""
        self.output.append("    /* CLI */")
        self.output.append("    runtime->machine.cpu.status &= ~0x04;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_clv(self, instr):
        """CLV - Clear Overflow"""
        self.output.append("    /* CLV */")
        self.output.append("    runtime->machine.cpu.status &= ~0x40;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_pld(self, instr):
        """PLD - Pull Direct Page"""
        self.output.append("    /* PLD */")
        self.output.append("    runtime->machine.cpu.d = (uint16_t)(stack_pop(runtime) | (stack_pop(runtime) << 8));")
        self.output.append("    runtime->scheduler.cpu_instructions += 6;")
        self.output.append("    runtime->scheduler.master_clock += 6;")

    def _emit_jmp(self, instr):
        """JMP - Jump"""
        self.output.append("    /* JMP */")
        if len(instr.operands) >= 2:
            target = instr.operands[0] | (instr.operands[1] << 8)
            self.output.append(f"    /* JMP ${target:04X} */")
            self.output.append(f"    runtime->machine.cpu.pc = 0x{target:04X}u;")
            self.output.append("    runtime->scheduler.cpu_instructions += 3;")
            self.output.append("    runtime->scheduler.master_clock += 3;")
            self.output.append("    return;")
        self.output.append("    runtime->route_failed = 1; return;")

    def _emit_jsr(self, instr):
        """JSR - Jump to Subroutine"""
        self.output.append("    /* JSR */")
        if len(instr.operands) >= 2:
            target = instr.operands[0] | (instr.operands[1] << 8)
            self.output.append(f"    /* JSR ${target:04X} */")
            self.output.append("    stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));")
            self.output.append("    stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));")
            self.output.append(f"    runtime->machine.cpu.pc = 0x{target:04X}u;")
            self.output.append("    runtime->scheduler.cpu_instructions += 6;")
            self.output.append("    runtime->scheduler.master_clock += 6;")
            self.output.append("    return;")
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

    # Additional opcode emitters for coverage
    def _emit_eor(self, instr):
        """EOR - Exclusive OR"""
        self.output.append("    /* EOR */")
        self.output.append("    runtime->route_failed = 1; return;")

    def _emit_bmi(self, instr):
        """BMI - Branch if Minus (N=1)"""
        offset = instr.operands[0] if instr.operands else 0
        if offset & 0x80: offset |= 0xFF00
        target = (instr.address + instr.size + offset) & 0xFFFF
        self.output.append(f"    /* BMI -> ${target:04X} if N=1 */")
        self.output.append("    if ((runtime->machine.cpu.status & 0x80) != 0) {")
        self.output.append(f"        runtime->machine.cpu.pc = 0x{target:04X}u;")
        self.output.append("        runtime->scheduler.cpu_instructions += 4;")
        self.output.append("        runtime->scheduler.master_clock += 4;")
        self.output.append("    } else {")
        self.output.append("        runtime->scheduler.cpu_instructions += 2;")
        self.output.append("        runtime->scheduler.master_clock += 2;")
        self.output.append("    }")
        self.output.append("    return;")

    def _emit_beq(self, instr):
        """BEQ - Branch if Equal (Z=1)"""
        offset = instr.operands[0] if instr.operands else 0
        if offset & 0x80: offset |= 0xFF00
        target = (instr.address + instr.size + offset) & 0xFFFF
        self.output.append(f"    /* BEQ -> ${target:04X} if Z=1 */")
        self.output.append("    if ((runtime->machine.cpu.status & 0x02) != 0) {")
        self.output.append(f"        runtime->machine.cpu.pc = 0x{target:04X}u;")
        self.output.append("        runtime->scheduler.cpu_instructions += 4;")
        self.output.append("        runtime->scheduler.master_clock += 4;")
        self.output.append("    } else {")
        self.output.append("        runtime->scheduler.cpu_instructions += 2;")
        self.output.append("        runtime->scheduler.master_clock += 2;")
        self.output.append("    }")
        self.output.append("    return;")

    def _emit_dey(self, instr):
        """DEY - Decrement Y"""
        self.output.append("    /* DEY */")
        self.output.append("    runtime->machine.cpu.y = (runtime->machine.cpu.y - 1) & 0xFFFF;")
        self.output.append("    if (runtime->machine.cpu.y & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("    if (runtime->machine.cpu.y == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_dex(self, instr):
        """DEX - Decrement X"""
        self.output.append("    /* DEX */")
        self.output.append("    runtime->machine.cpu.x = (runtime->machine.cpu.x - 1) & 0xFFFF;")
        self.output.append("    if (runtime->machine.cpu.x & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("    if (runtime->machine.cpu.x == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_sbc(self, instr):
        """SBC - Subtract with Carry"""
        self.output.append("    /* SBC */")
        self.output.append("    runtime->route_failed = 1; return;")

    def _emit_sep(self, instr):
        """SEP - Set Status Bits"""
        mask = instr.operands[0] if instr.operands else 0
        self.output.append(f"    /* SEP #${mask:02X} */")
        self.output.append(f"    runtime->machine.cpu.status |= 0x{mask:02X};")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_rti(self, instr):
        """RTI - Return from Interrupt"""
        self.output.append("    /* RTI */")
        self.output.append("    {")
        self.output.append("        uint8_t status = stack_pop(runtime);")
        self.output.append("        uint16_t pc_lo = stack_pop(runtime);")
        self.output.append("        uint16_t pc_hi = stack_pop(runtime);")
        self.output.append("        runtime->machine.cpu.pc = (uint16_t)((pc_hi << 8) | pc_lo);")
        self.output.append("        runtime->machine.cpu.status = (status & ~0x30) | 0x20; /* clear B, set U */")
        self.output.append("        runtime->scheduler.cpu_instructions += 6;")
        self.output.append("        runtime->scheduler.master_clock += 6;")
        self.output.append("        return;")
        self.output.append("    }")

    def _emit_phy(self, instr):
        """PHY - Push Y"""
        self.output.append("    /* PHY */")
        self.output.append("    stack_push(runtime, (uint8_t)runtime->machine.cpu.y);")
        self.output.append("    runtime->scheduler.cpu_instructions += 3;")
        self.output.append("    runtime->scheduler.master_clock += 3;")

    def _emit_php(self, instr):
        """PHP - Push Processor Status"""
        self.output.append("    /* PHP */")
        self.output.append("    stack_push(runtime, runtime->machine.cpu.status | 0x30); /* B and U always 1 */")
        self.output.append("    runtime->scheduler.cpu_instructions += 3;")
        self.output.append("    runtime->scheduler.master_clock += 3;")

    def _emit_mva(self, instr):
        """MVA - Move Accumulator (placeholder)"""
        self.output.append("    /* MVA - nop */")
        self.output.append("    runtime->scheduler.cpu_instructions += 4;")
        self.output.append("    runtime->scheduler.master_clock += 4;")

    def _emit_mvd(self, instr):
        """MVD - Move Direct (placeholder)"""
        self.output.append("    /* MVD - nop */")
        self.output.append("    runtime->scheduler.cpu_instructions += 4;")
        self.output.append("    runtime->scheduler.master_clock += 4;")

    def _emit_neg(self, instr):
        """NEG - Negate (2's complement)"""
        self.output.append("    /* NEG */")
        self.output.append("    runtime->route_failed = 1; return;")

    # Additional opcode handlers
    def _emit_lsr(self, instr):
        """LSR - Logical Shift Right"""
        if len(instr.operands) == 0:
            self.output.append("    /* LSR A */")
            self.output.append("    {")
            self.output.append("        uint8_t val = runtime->machine.cpu.a;")
            self.output.append("        uint8_t carry = val & 0x01;")
            self.output.append("        runtime->machine.cpu.a = val >> 1;")
            self.output.append("        if (carry) runtime->machine.cpu.status |= 0x01; else runtime->machine.cpu.status &= ~0x01;")
            self.output.append("        if (runtime->machine.cpu.a & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("        if (runtime->machine.cpu.a == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            self.output.append("        runtime->scheduler.cpu_instructions += 2;")
            self.output.append("        runtime->scheduler.master_clock += 2;")
            self.output.append("    }")
        else:
            self.output.append("    /* LSR memory - stub */")
            self.output.append("    runtime->route_failed = 1; return;")

    def _emit_rol(self, instr):
        """ROL - Rotate Left"""
        if len(instr.operands) == 0:
            self.output.append("    /* ROL A */")
            self.output.append("    {")
            self.output.append("        uint8_t val = runtime->machine.cpu.a;")
            self.output.append("        uint8_t carry = val & 0x80;")
            self.output.append("        uint8_t new_carry = (runtime->machine.cpu.status & 0x01) != 0;")
            self.output.append("        runtime->machine.cpu.a = (val << 1) | new_carry;")
            self.output.append("        if (carry) runtime->machine.cpu.status |= 0x01; else runtime->machine.cpu.status &= ~0x01;")
            self.output.append("        if (runtime->machine.cpu.a & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("        if (runtime->machine.cpu.a == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            self.output.append("        runtime->scheduler.cpu_instructions += 2;")
            self.output.append("        runtime->scheduler.master_clock += 2;")
            self.output.append("    }")
        else:
            self.output.append("    /* ROL memory - stub */")
            self.output.append("    runtime->route_failed = 1; return;")

    def _emit_adc(self, instr):
        """ADC - Add with Carry"""
        self.output.append("    /* ADC - stub */")
        self.output.append("    runtime->route_failed = 1; return;")

    def _emit_sbc(self, instr):
        """SBC - Subtract with Carry"""
        self.output.append("    /* SBC - stub */")
        self.output.append("    runtime->route_failed = 1; return;")

    def _emit_cmp(self, instr):
        """CMP - Compare Accumulator"""
        self.output.append("    /* CMP - stub */")
        self.output.append("    runtime->route_failed = 1; return;")

    def _emit_ldy(self, instr):
        """LDY - Load Y Register"""
        if instr.addr_mode == 2:
            val = instr.operands[0] if instr.operands else 0
            self.output.append(f"    /* LDY #${val:02X} */")
            self.output.append(f"    runtime->machine.cpu.y = 0x{val:02X};")
            self.output.append("    if (runtime->machine.cpu.y & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
            self.output.append("    if (runtime->machine.cpu.y == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
            self.output.append("    runtime->scheduler.cpu_instructions += 2;")
            self.output.append("    runtime->scheduler.master_clock += 2;")
        else:
            self.output.append("    /* LDY memory - stub */")
            self.output.append("    runtime->route_failed = 1; return;")

    def _emit_stx(self, instr):
        """STX - Store X Register"""
        self.output.append("    /* STX - stub */")
        self.output.append("    runtime->route_failed = 1; return;")

    def _emit_sty(self, instr):
        """STY - Store Y Register"""
        self.output.append("    /* STY - stub */")
        self.output.append("    runtime->route_failed = 1; return;")

    def _emit_dec(self, instr):
        """DEC - Decrement Memory"""
        self.output.append("    /* DEC - stub */")
        self.output.append("    runtime->route_failed = 1; return;")

    def _emit_inx(self, instr):
        """INX - Increment X"""
        self.output.append("    /* INX */")
        self.output.append("    runtime->machine.cpu.x = (runtime->machine.cpu.x + 1) & 0xFFFF;")
        self.output.append("    if (runtime->machine.cpu.x & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("    if (runtime->machine.cpu.x == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_iny(self, instr):
        """INY - Increment Y"""
        self.output.append("    /* INY */")
        self.output.append("    runtime->machine.cpu.y = (runtime->machine.cpu.y + 1) & 0xFFFF;")
        self.output.append("    if (runtime->machine.cpu.y & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("    if (runtime->machine.cpu.y == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_pha(self, instr):
        """PHA - Push Accumulator"""
        self.output.append("    /* PHA */")
        self.output.append("    stack_push(runtime, (uint8_t)runtime->machine.cpu.a);")
        self.output.append("    runtime->scheduler.cpu_instructions += 3;")
        self.output.append("    runtime->scheduler.master_clock += 3;")

    def _emit_php(self, instr):
        """PHP - Push Processor Status"""
        self.output.append("    /* PHP */")
        self.output.append("    stack_push(runtime, runtime->machine.cpu.status | 0x30);")
        self.output.append("    runtime->scheduler.cpu_instructions += 3;")
        self.output.append("    runtime->scheduler.master_clock += 3;")

    def _emit_pla(self, instr):
        """PLA - Pull Accumulator"""
        self.output.append("    /* PLA */")
        self.output.append("    {")
        self.output.append("        uint8_t val = stack_pop(runtime);")
        self.output.append("        runtime->machine.cpu.a = val;")
        self.output.append("        if (val & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("        if (val == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("        runtime->scheduler.cpu_instructions += 4;")
        self.output.append("        runtime->scheduler.master_clock += 4;")
        self.output.append("    }")

    def _emit_plp(self, instr):
        """PLP - Pull Processor Status"""
        self.output.append("    /* PLP */")
        self.output.append("    {")
        self.output.append("        uint8_t status = stack_pop(runtime);")
        self.output.append("        runtime->machine.cpu.status = (status & ~0x30) | 0x20;")
        self.output.append("        runtime->scheduler.cpu_instructions += 4;")
        self.output.append("        runtime->scheduler.master_clock += 4;")
        self.output.append("    }")

    def _emit_plx(self, instr):
        """PLX - Pull X"""
        self.output.append("    /* PLX */")
        self.output.append("    {")
        self.output.append("        uint8_t val = stack_pop(runtime);")
        self.output.append("        runtime->machine.cpu.x = val;")
        self.output.append("        if (val & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("        if (val == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("        runtime->scheduler.cpu_instructions += 4;")
        self.output.append("        runtime->scheduler.master_clock += 4;")
        self.output.append("    }")

    def _emit_ply(self, instr):
        """PLY - Pull Y"""
        self.output.append("    /* PLY */")
        self.output.append("    {")
        self.output.append("        uint8_t val = stack_pop(runtime);")
        self.output.append("        runtime->machine.cpu.y = val;")
        self.output.append("        if (val & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("        if (val == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("        runtime->scheduler.cpu_instructions += 4;")
        self.output.append("        runtime->scheduler.master_clock += 4;")
        self.output.append("    }")

    def _emit_tax(self, instr):
        """TAX - Transfer A to X"""
        self.output.append("    /* TAX */")
        self.output.append("    runtime->machine.cpu.x = runtime->machine.cpu.a;")
        self.output.append("    if (runtime->machine.cpu.x & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("    if (runtime->machine.cpu.x == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_tay(self, instr):
        """TAY - Transfer A to Y"""
        self.output.append("    /* TAY */")
        self.output.append("    runtime->machine.cpu.y = runtime->machine.cpu.a;")
        self.output.append("    if (runtime->machine.cpu.y & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("    if (runtime->machine.cpu.y == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_txa(self, instr):
        """TXA - Transfer X to A"""
        self.output.append("    /* TXA */")
        self.output.append("    runtime->machine.cpu.a = runtime->machine.cpu.x;")
        self.output.append("    if (runtime->machine.cpu.a & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("    if (runtime->machine.cpu.a == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_tya(self, instr):
        """TYA - Transfer Y to A"""
        self.output.append("    /* TYA */")
        self.output.append("    runtime->machine.cpu.a = runtime->machine.cpu.y;")
        self.output.append("    if (runtime->machine.cpu.a & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("    if (runtime->machine.cpu.a == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_txs(self, instr):
        """TXS - Transfer X to Stack"""
        self.output.append("    /* TXS */")
        self.output.append("    runtime->machine.cpu.sp = (uint8_t)runtime->machine.cpu.x;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_tsx(self, instr):
        """TSX - Transfer Stack to X"""
        self.output.append("    /* TSX */")
        self.output.append("    runtime->machine.cpu.x = runtime->machine.cpu.sp;")
        self.output.append("    if (runtime->machine.cpu.x & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("    if (runtime->machine.cpu.x == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_tdc(self, instr):
        """TDC - Transfer Direct to A"""
        self.output.append("    /* TDC */")
        self.output.append("    runtime->machine.cpu.a = (uint8_t)runtime->machine.cpu.d;")
        self.output.append("    if (runtime->machine.cpu.a & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;")
        self.output.append("    if (runtime->machine.cpu.a == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_cld(self, instr):
        """CLD - Clear Decimal"""
        self.output.append("    /* CLD */")
        self.output.append("    runtime->machine.cpu.status &= ~0x08;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_clc(self, instr):
        """CLC - Clear Carry"""
        self.output.append("    /* CLC */")
        self.output.append("    runtime->machine.cpu.status &= ~0x01;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_sec(self, instr):
        """SEC - Set Carry"""
        self.output.append("    /* SEC */")
        self.output.append("    runtime->machine.cpu.status |= 0x01;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_cli(self, instr):
        """CLI - Clear Interrupt Disable"""
        self.output.append("    /* CLI */")
        self.output.append("    runtime->machine.cpu.status &= ~0x04;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_clv(self, instr):
        """CLV - Clear Overflow"""
        self.output.append("    /* CLV */")
        self.output.append("    runtime->machine.cpu.status &= ~0x40;")
        self.output.append("    runtime->scheduler.cpu_instructions += 2;")
        self.output.append("    runtime->scheduler.master_clock += 2;")

    def _emit_pld(self, instr):
        """PLD - Pull Direct Page"""
        self.output.append("    /* PLD */")
        self.output.append("    runtime->machine.cpu.d = (uint16_t)(stack_pop(runtime) | (stack_pop(runtime) << 8));")
        self.output.append("    runtime->scheduler.cpu_instructions += 6;")
        self.output.append("    runtime->scheduler.master_clock += 6;")

    def _emit_jmp(self, instr):
        """JMP - Jump"""
        self.output.append("    /* JMP */")
        if len(instr.operands) >= 2:
            target = instr.operands[0] | (instr.operands[1] << 8)
            self.output.append(f"    /* JMP ${target:04X} */")
            self.output.append(f"    runtime->machine.cpu.pc = 0x{target:04X}u;")
            self.output.append("    runtime->scheduler.cpu_instructions += 3;")
            self.output.append("    runtime->scheduler.master_clock += 3;")
            self.output.append("    return;")
        self.output.append("    runtime->route_failed = 1; return;")

    def _emit_jsr(self, instr):
        """JSR - Jump to Subroutine"""
        self.output.append("    /* JSR */")
        if len(instr.operands) >= 2:
            target = instr.operands[0] | (instr.operands[1] << 8)
            self.output.append(f"    /* JSR ${target:04X} */")
            self.output.append("    stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));")
            self.output.append("    stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));")
            self.output.append(f"    runtime->machine.cpu.pc = 0x{target:04X}u;")
            self.output.append("    runtime->scheduler.cpu_instructions += 6;")
            self.output.append("    runtime->scheduler.master_clock += 6;")
            self.output.append("    return;")
        self.output.append("    runtime->route_failed = 1; return;")
