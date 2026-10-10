#!/usr/bin/env python3
"""Utopia SNES ROM analyzer — extracts entry points, code regions, and dispatch info."""

import sys
import struct
from pathlib import Path

# 65C816 opcode table (simplified — only opcodes we care about for analysis)
OPCODES = {
    # 1-byte opcodes
    0x00: ('BRK', 1), 0x08: ('PHP', 1), 0x0a: ('ASL A', 1), 0x0c: ('TPS', 1),
    0x0e: ('ASL', 2), 0x10: ('BPL', 1), 0x18: ('CLC', 1), 0x1a: ('NOP', 1),
    0x1e: ('ASL', 3), 0x20: ('JSR', 2), 0x21: ('AND', 0), 0x22: ('JSL', 3),
    0x24: ('BIT', 0), 0x25: ('AND', 0), 0x28: ('PLP', 1), 0x29: ('AND', 0),
    0x2c: ('BIT', 2), 0x2d: ('AND', 2), 0x2e: ('ASL', 2), 0x30: ('BMI', 1),
    0x32: ('AND', 0), 0x38: ('SEC', 1), 0x3a: ('NOP', 1), 0x3c: ('BIT', 3),
    0x3d: ('AND', 3), 0x3e: ('ASL', 3), 0x40: ('RTI', 1), 0x42: ('TRB', 2),
    0x48: ('PHA', 1), 0x49: ('ORA', 0), 0x4a: ('LSR A', 1), 0x4c: ('JMP', 2),
    0x4e: ('LSR', 2), 0x50: ('BVC', 1), 0x51: ('ORA', 0), 0x52: ('ORA', 0),
    0x55: ('ORA', 2), 0x58: ('CLI', 1), 0x59: ('ORA', 3), 0x5d: ('ORA', 3),
    0x5e: ('LSR', 3), 0x60: ('RTS', 1), 0x62: ('PEI', 2), 0x68: ('PLA', 1),
    0x69: ('ORA', 0), 0x6a: ('EOR A', 1), 0x6c: ('JMP', 2), 0x6e: ('EOR', 2),
    0x70: ('BVS', 1), 0x71: ('ORA', 0), 0x72: ('ORA', 0), 0x78: ('SEI', 1),
    0x79: ('ORA', 3), 0x7e: ('EOR', 3), 0x81: ('STA', 0), 0x82: ('STA', 0),
    0x84: ('STY', 0), 0x85: ('STA', 0), 0x88: ('DEY', 1), 0x8a: ('TPX', 1),
    0x8c: ('STY', 2), 0x8d: ('STA', 2), 0x8e: ('STX', 2), 0x90: ('BCC', 1),
    0x91: ('STA', 0), 0x92: ('STA', 0), 0x98: ('TYA', 1), 0x99: ('STA', 3),
    0x9a: ('TXS', 1), 0x9e: ('SX LA', 3), 0xa0: ('LDY', 0), 0xa1: ('LDA', 0),
    0xa2: ('LDX', 0), 0xa4: ('LDY', 0), 0xa5: ('LDA', 0), 0xa6: ('LDX', 0),
    0xa8: ('TAY', 1), 0xa9: ('LDA', 0), 0xaa: ('TAX', 1), 0xac: ('LDY', 2),
    0xad: ('LDA', 2), 0xae: ('LDX', 2), 0xb0: ('BCS', 1), 0xb1: ('LDA', 0),
    0xb2: ('LDA', 0), 0xb4: ('LDY', 2), 0xb5: ('LDA', 2), 0xb6: ('LDX', 2),
    0xb8: ('CLV', 1), 0xb9: ('LDA', 3), 0xba: ('TSX', 1), 0xbc: ('LDY', 3),
    0xbd: ('LDA', 3), 0xbe: ('LDX', 3), 0xc0: ('CPY', 0), 0xc1: ('CMP', 0),
    0xc4: ('CPY', 2), 0xc5: ('CMP', 0), 0xc6: ('DEC', 2), 0xc8: ('INX', 1),
    0xc9: ('CMP', 0), 0xca: ('DEX', 1), 0xcc: ('CPY', 2), 0xcd: ('CMP', 2),
    0xce: ('DEC', 2), 0xd0: ('BNE', 1), 0xd1: ('CMP', 0), 0xd2: ('CMP', 0),
    0xd4: ('TRB', 2), 0xd5: ('CMP', 2), 0xd8: ('CLD', 1), 0xd9: ('CMP', 3),
    0xdd: ('CMP', 3), 0xde: ('DEC', 3), 0xe0: ('CPX', 0), 0xe1: ('SBC', 0),
    0xe4: ('CPX', 2), 0xe5: ('SBC', 0), 0xe6: ('INC', 2), 0xe8: ('INX', 1),
    0xe9: ('SBC', 0), 0xea: ('NOP', 1), 0xec: ('CPX', 2), 0xed: ('SBC', 2),
    0xee: ('INC', 2), 0xf0: ('BEQ', 1), 0xf1: ('SBC', 0), 0xf2: ('SBC', 0),
    0xf4: ('TRB', 2), 0xf5: ('SBC', 2), 0xf8: ('SED', 1), 0xf9: ('SBC', 3),
    0xfd: ('SBC', 3), 0xfe: ('INC', 3),
}


def decode_branch(rom, addr):
    """Decode a branch instruction and return the target address."""
    b = rom[addr]
    if b in (0x10, 0x30, 0x50, 0x70, 0x90, 0xb0, 0xd0, 0xf0):
        label = {'0x10': 'BPL', '0x30': 'BMI', '0x50': 'BVC', '0x70': 'BVS',
                 '0x90': 'BCC', '0xb0': 'BCS', '0xd0': 'BNE', '0xf0': 'BEQ'}[f'0x{b:x}']
        operand = rom[addr + 1]
        if operand & 0x80:
            operand -= 0x100
        target = addr + 2 + operand
        return label, target
    return None, None


def decode_addressing(rom, op, addr, inst_addr):
    """Decode operand bytes for a given opcode and addressing mode."""
    if op == 1:
        return [rom[inst_addr + 1]]
    elif op == 2:
        lo = rom[inst_addr + 1]
        hi = rom[inst_addr + 2]
        return [lo, hi, (hi << 8) | lo]
    elif op == 3:
        lo = rom[inst_addr + 1]
        mid = rom[inst_addr + 2]
        hi = rom[inst_addr + 3]
        return [lo, mid, hi, (hi << 16) | (mid << 8) | lo]
    return []


def find_entry_points(rom, banks=(0x80, 0x81, 0x82)):
    """Find all JML/JMP/JSL instructions in the given banks."""
    results = []
    for bank in banks:
        offset_base = (bank - 0x80) * 0x8000
        bank_end = offset_base + 0x8000
        pos = offset_base
        while pos < bank_end - 4:
            b = rom[pos]
            # JML: 5C xx xx xx
            if b == 0x5C:
                target = rom[pos+1] | (rom[pos+2] << 8) | (rom[pos+3] << 16)
                results.append(('JML', bank, pos, target))
            # JSL: 22 xx xx xx
            elif b == 0x22:
                target = rom[pos+1] | (rom[pos+2] << 8) | (rom[pos+3] << 16)
                results.append(('JSL', bank, pos, target))
            # JMP (short): 4C xx xx
            elif b == 0x4C and pos + 2 < bank_end:
                target = rom[pos+1] | (rom[pos+2] << 8)
                results.append(('JMP', bank, pos, target))
            pos += 1
    return results


def main():
    rom_path = Path(sys.argv[1]) if len(sys.argv) > 1 else Path('Utopia - The Creation of a Nation (USA).sfc')
    with open(rom_path, 'rb') as f:
        rom = f.read()

    print(f"ROM size: {len(rom):,} bytes")
    print()

    # Header analysis
    print("=== ROM Header ===")
    title = rom[0x7FC0:0x7FD0].rstrip(b'\x20').decode('ascii', errors='replace')
    layout = rom[0x7FDC]
    rom_size = [0, 128, 256, 384, 512, 768, 1024, 1536, 2048, 256, 3072, 3584, 4096][rom[0x7FDD]] if rom[0x7FDD] < 0x0A else rom[0x7FDD] * 128
    ram_size = [0, 1, 2, 4, 8, 16, 32][rom[0x7FDE]] if rom[0x7FDE] < 7 else rom[0x7FDE]
    country = ['Japan', 'USA', 'Europe', 'Scandinavia', 'Korea', 'China', 'Other'][rom[0x7FDF]] if rom[0x7FDF] < 7 else 'Unknown'
    version = rom[0x7FE0]
    print(f"Title: {title}")
    print(f"Layout: {'LoROM' if layout in (0x01, 0x02) else 'HiROM'} (0x{layout:02X})")
    print(f"ROM size: {rom_size} KB")
    print(f"RAM size: {ram_size} KB")
    print(f"Country: {country}")
    print(f"Version: {version}")

    # Vectors
    nmi_lo, nmi_hi = rom[0x7FFC], rom[0x7FFD]
    rst_lo, rst_hi = rom[0x7FFE], rom[0x7FFF]
    nmi_pc = (nmi_hi << 8) | nmi_lo
    rst_pc = (rst_hi << 8) | rst_lo
    print(f"\nNMI vector: ${nmi_pc:06X}")
    print(f"Reset vector: ${rst_pc:06X}")

    # Entry points in code banks
    print("\n=== Code Entry Points (Bank 0x80-0x83) ===")
    entries = find_entry_points(rom, banks=(0x80, 0x81, 0x82, 0x83))
    for typ, bank, pos, target in sorted(entries):
        print(f"  {typ} @ bank {bank:#06x}:${pos:04X} -> ${target:06X}")

    # Check for known patterns
    print("\n=== Boot Sequence Analysis ===")
    # The reset sequence typically includes SEP, PHA, DEX, PLX, PHX, PHB, LDA
    reset_seq = [0xC2, 0x38, 0x48, 0xDA, 0x5A, 0x0B, 0x8B, 0xA9]
    for bank in (0x80, 0x81):
        offset_base = (bank - 0x80) * 0x8000
        for i in range(8):
            if rom[offset_base + i] == reset_seq[i]:
                print(f"  Found boot sequence at bank {bank:#06x} offset 0x{i:04X}")
                break

    print("\n=== Code Density by Bank ===")
    for bank in range(0x80, 0x90):
        offset_base = (bank - 0x80) * 0x8000
        chunk = rom[offset_base:offset_base+0x8000]
        nonzero = sum(1 for b in chunk if b != 0)
        total = len(chunk)
        density = nonzero / total * 100
        print(f"  Bank {bank:#06x}: {nonzero:>6} / {total:>5} = {density:.1f}%")


if __name__ == '__main__':
    main()
