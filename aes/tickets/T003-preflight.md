---
ticket: T003
title: Implement Full W65C816 Opcode Dispatch
sprint: sprint-01
priority: high
status: in-progress
created: 2026-10-10
---

# T003 — Implement Full W65C816 Opcode Dispatch

## Context
T002 established the bootstrap dispatch for the first ~20 instructions. Now we need to expand coverage to handle all opcodes used by Utopia's game code. This is the core of the static recompilation — every reachable PC must have a dispatch entry.

## Acceptance Criteria
- [ ] All 65C816 opcodes implemented (zero-page, absolute, indexed, implied, immediate)
- [ ] Branch instructions handle page-crossing correctly
- [ ] Stack operations (PHP, PLP, PHA, PLA, JSR, RTS, BRK, RTI) work correctly
- [ ] Build succeeds with no errors or warnings
- [ ] Tests pass
- [ ] Headless test advances at least 10 frames without route failure

## Scope
**In scope:** Complete W65C816 opcode set for the games's code regions.
**Out of scope:** S-SMP audio dispatch (T005), PPU rendering (T004+), full game logic verification.

## Dependencies
- T002 (bootstrap dispatch) — DONE

## Rollback
Revert to stub cpu_step. All dispatch code is in generated/ and can be removed cleanly.

## Notes
- Utopia uses standard W65C816 instructions (no custom extensions)
- Key opcodes to prioritize: ADC, SBC, AND, ORA, EOR, LDA, STA, LDY, STY, LDX, STX, INC, DEC, CMP, BCC, BCS, BEQ, BNE, BPL, BMI, BVC, BVS, BRK, JMP, JSR, RTS, RTI, PHP, PLP, PHA, PLA, TAX, TXA, TAY, TYA, TSX, TXS, SEI, CLI, SEC, CLC, CLV, CLD, SED, NOP, ASL, LSR, ROL, ROR
- Addressing modes: implied, immediate, zero-page, zero-page,X, absolute, absolute,X, absolute,Y, (indirect,X), (Y),indirect, absolute,X (indexed indirect)