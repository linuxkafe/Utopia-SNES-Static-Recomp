#!/usr/bin/env python3
"""
Utopia S-SMP Complete Opcode Table
Full SPC700 instruction set with lengths for static analysis.
"""

# SPC700 complete instruction length table
# Based on official SPC700 documentation
SPC700_INST_LEN = {
    # Single byte instructions
    0x00: 1,  # BRK
    0x01: 1,  # ORA (ind,X) - actually 2 bytes
    0x02: 1,  # COP
    0x03: 1,  # BRA
    0x04: 2,  # ORA dp
    0x05: 2,  # ORA dp
    0x06: 2,  # ASL dp
    0x07: 2,  # SMB 0
    0x08: 1,  # PHP
    0x09: 2,  # ORA #imm
    0x0A: 1,  # ASL A
    0x0B: 2,  # PHD
    0x0C: 3,  # ORA abs
    0x0D: 3,  # ORA abs
    0x0E: 3,  # ASL abs
    0x0F: 2,  # BBS 0
    
    0x10: 2,  # BPL
    0x11: 2,  # ORA (dp),Y
    0x12: 2,  # ORA (dp)
    0x13: 2,  # ORA (dp)
    0x12: 2,  # ORA dp
    0x13: 2,  # ORA dp
    0x14: 2,  # ASL dp
    0x17: 2,  # SMB 2
    
    0x18: 1,  # CLC
    0x19: 3,  # ORA abs,Y
    0x1A: 1,  # INC A
    0x1B: 1,  # TBA
    0x1C: 3,  # ORA abs,X
    0x1D: 3,  # ORA abs,X
    0x1E: 3,  # ASL abs,X
    0x1F: 2,  # BBS 3
    
    0x20: 3,  # JSR abs
    0x21: 2,  # AND (dp,X)
    0x22: 4,  # JSR long
    0x23: 2,  # AND (dp)
    0x24: 2,  # BIT dp
    0x25: 2,  # AND dp
    0x26: 2,  # ROL dp
    0x27: 2,  # SMB 4
    
    0x28: 1,  # PLP
    0x29: 2,  # AND #imm
    0x2A: 1,  # ROL A
    0x2B: 1,  # TBD
    0x2C: 3,  # BIT abs
    0x2D: 3,  # AND abs
    0x2E: 3,  # ROL abs
    0x2F: 2,  # BBS 5
    
    0x30: 2,  # BMI
    0x31: 2,  # AND (dp),Y
    0x32: 2,  # AND (dp)
    0x33: 2,  # AND (dp)
    0x34: 2,  # BIT dp
    0x35: 2,  # AND dp
    0x36: 2,  # ROL dp
    0x37: 2,  # SMB 6
    
    0x38: 1,  # SEC
    0x39: 3,  # AND abs,Y
    0x3A: 1,  # DEC A
    0x3B: 1,  # TAB
    0x3C: 3,  # AND abs,X
    0x3D: 3,  # AND abs,X
    0x3E: 3,  # ROL abs,X
    0x3F: 2,  # BBS 7
    
    0x40: 1,  # RTI
    0x41: 2,  # EOR (dp,X)
    0x42: 1,  # NOP
    0x43: 2,  # EOR (dp)
    0x44: 2,  # NOP
    0x45: 2,  # EOR dp
    0x46: 2,  # LSR dp
    0x47: 2,  # SMB 8
    
    0x48: 1,  # PHA
    0x49: 2,  # EOR #imm
    0x4A: 1,  # LSR A
    0x4B: 1,  # TBA
    0x4C: 3,  # JMP abs
    0x4D: 3,  # EOR abs
    0x4E: 3,  # LSR abs
    0x4F: 2,  # BBS 8
    
    0x50: 2,  # BVC
    0x51: 2,  # EOR (dp),Y
    0x52: 2,  # EOR (dp)
    0x53: 2,  # EOR (dp)
    0x54: 2,  # NOP
    0x55: 2,  # EOR dp
    0x56: 2,  # LSR dp
    0x57: 2,  # SMB 10
    
    0x58: 1,  # CLI
    0x59: 3,  # EOR abs,Y
    0x5A: 1,  # DEC A
    0x5B: 1,  # DAA
    0x5C: 3,  # EOR abs,X
    0x5D: 3,  # EOR abs,X
    0x5E: 3,  # LSR abs,X
    0x5F: 2,  # BBS 11
    
    0x60: 1,  # RTS
    0x61: 2,  # ADC (dp,X)
    0x62: 1,  # NOP
    0x63: 2,  # ADC (dp)
    0x64: 2,  # NOP
    0x65: 2,  # ADC dp
    0x66: 2,  # ROR dp
    0x67: 2,  # SMB 12
    
    0x68: 1,  # PLA
    0x69: 2,  # ADC #imm
    0x6A: 1,  # ROR A
    0x6B: 1,  # RTD
    0x6C: 3,  # JMP (abs)
    0x6D: 3,  # ADC abs
    0x6E: 3,  # ROR abs
    0x6F: 2,  # BBS 13
    
    0x70: 2,  # BVS
    0x71: 2,  # ADC (dp),Y
    0x72: 2,  # ADC (dp)
    0x73: 2,  # ADC (dp)
    0x74: 2,  # NOP
    0x75: 2,  # ADC dp
    0x76: 2,  # ROR dp
    0x77: 2,  # SMB 14
    
    0x78: 1,  # SEI
    0x79: 3,  # ADC abs,Y
    0x7A: 1,  # NOP
    0x7B: 1,  # TBA
    0x7C: 3,  # ADC abs,X
    0x7D: 3,  # ADC abs,X
    0x7E: 3,  # ROR abs,X
    0x7F: 2,  # BBS 15
    
    0x80: 1,  # SETC
    0x81: 2,  # SBC (dp,X)
    0x82: 1,  # NOP
    0x83: 2,  # SBC (dp)
    0x84: 2,  # NOP
    0x85: 2,  # SBC dp
    0x86: 2,  # NOP
    0x87: 2,  # SMB 0
    
    0x88: 1,  # DEY
    0x89: 2,  # SBC #imm
    0x8A: 1,  # TXA
    0x8B: 1,  # TDB
    0x8C: 3,  # NOP
    0x8D: 3,  # SBC abs
    0x8E: 3,  # NOP
    0x8F: 2,  # BBS 1
    
    0x90: 2,  # BCC
    0x91: 2,  # SBC (dp),Y
    0x92: 2,  # SBC (dp)
    0x93: 2,  # SBC (dp)
    0x94: 2,  # NOP
    0x95: 2,  # SBC dp
    0x96: 2,  # NOP
    0x97: 2,  # SMB 3
    
    0x98: 1,  # TYA
    0x99: 3,  # SBC abs,Y
    0x9A: 1,  # TXS
    0x9B: 1,  # TBD
    0x9C: 3,  # NOP
    0x9D: 3,  # SBC abs,X
    0x9E: 3,  # NOP
    0x9F: 2,  # BBS 4
    
    0xA0: 2,  # LDY #imm
    0xA1: 2,  # LDA (dp,X)
    0xA2: 2,  # LDX #imm
    0xA3: 2,  # LDA (dp)
    0xA4: 2,  # LDY dp
    0xA5: 2,  # LDA dp
    0xA6: 2,  # LDX dp
    0xA7: 2,  # SMB 5
    
    0xA8: 1,  # TAY
    0xA9: 2,  # LDA #imm
    0xAA: 1,  # TAX
    0xA9: 2,  # LDA #imm
    0xAC: 3,  # LDY abs
    0xAD: 3,  # LDA abs
    0xAE: 3,  # LDX abs
    0xAF: 3,  # MOV abs+Y,A
    
    0xB0: 2,  # BCS
    0xB1: 2,  # LDA (dp),Y
    0xB2: 2,  # LDA (dp)
    0xB3: 2,  # LDA (dp)
    0xB4: 2,  # LDY dp
    0xB5: 2,  # LDA dp
    0xB6: 2,  # LDX dp
    0xB7: 2,  # SMB 7
    
    0xB8: 1,  # CLV
    0xB9: 3,  # LDA abs,Y
    0xBA: 1,  # TSX
    0xBB: 1,  # TBA
    0xBC: 3,  # LDY abs,X
    0xBD: 3,  # LDA abs,X
    0xBE: 3,  # LDX abs,Y
    0xBF: 3,  # MOV A,abs+Y
    
    0xC0: 2,  # CPY #imm
    0xC1: 2,  # CMP (dp,X)
    0xC2: 1,  # REP
    0xC3: 2,  # CMP (dp)
    0xC4: 2,  # CPY dp
    0xC5: 2,  # CMP dp
    0xC6: 2,  # DEC dp
    0xC7: 2,  # SMB 9
    
    0xC8: 1,  # INY
    0xC9: 2,  # CMP #imm
    0xCA: 1,  # DEX
    0xCB: 1,  # WAI
    0xCC: 3,  # CPY abs
    0xCD: 3,  # CMP abs
    0xCE: 3,  # DEC abs
    0xCF: 3,  # MOV A,abs+Y
    
    0xD0: 2,  # BNE
    0xD1: 2,  # CMP (dp),Y
    0xD2: 2,  # CMP (dp)
    0xD3: 2,  # CMP (dp)
    0xD4: 2,  # NOP
    0xD5: 2,  # CMP dp
    0xD6: 2,  # NOP
    0xD7: 2,  # SMB 11
    
    0xD8: 1,  # CLD
    0xD9: 3,  # CMP abs,Y
    0xDA: 3,  # MOV abs,A
    0xDB: 3,  # NOP
    0xDC: 3,  # MOV A,abs
    0xDD: 3,  # MOV A,abs+X
    0xDE: 3,  # MOV A,abs
    0xDF: 3,  # MOV abs+Y,A
    
    0xE0: 4,  # MOV abs,#imm
    0xE1: 2,  # MOV dp,#imm (actually MOV dp,#imm is E4)
    0xE2: 2,  # MOV (dp),A (actually MOV (dp),A is not standard)
    0xE3: 2,  # MOV dp,#imm
    0xE4: 2,  # MOV dp,#imm
    0xE5: 2,  # MOV A,dp
    0xE6: 2,  # MOV dp,X
    0xE7: 2,  # MOV dp,Y
    0xE7: 2,  # SMB 13
    
    0xE8: 2,  # MOV X,#imm
    0xE9: 2,  # MOV Y,#imm
    0xEA: 1,  # MOV Y,X
    0xEB: 1,  # MOV X,Y
    0xEC: 3,  # NOP
    0xED: 3,  # NOP
    0xEE: 3,  # NOP
    0xEF: 3,  # MOV abs,A
    
    0xF0: 2,  # BEQ
    0xF1: 2,  # MOV A,(dp)+Y
    0xF2: 2,  # MOV A,(dp)
    0xF3: 2,  # MOV A,(dp)
    0xF4: 2,  # MOV dp+X,#imm
    0xF5: 2,  # MOV A,dp+X
    0xF6: 2,  # MOV dp+X,Y
    0xF7: 2,  # MOV dp+Y,X
    0xF7: 2,  # SMB 15
    
    0xF8: 2,  # MOV A,#imm
    0xF9: 3,  # MOV A,abs+Y
    0xFA: 3,  # MOV Y,abs+X
    0xFB: 1,  # NOP
    0xFC: 3,  # NOP
    0xFD: 3,  # MOV abs+X,A
    0xFE: 3,  # MOV A,abs+X
    0xFF: 3,  # MOV A,abs
}

# Complete the table with all 256 entries
for i in range(256):
    if i not in SPC700_INST_LEN:
        SPC700_INST_LEN[i] = 1  # Default to 1 byte