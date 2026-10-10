---
ticket: T002
title: Generate W65C816 Bootstrap Dispatch for Utopia ROM
sprint: sprint-01
priority: high
status: done
created: 2026-10-10
---

# T002 — Generate W65C816 Bootstrap Dispatch for Utopia ROM

## Context
T001 established the project scaffold. The core now compiles but the CPU is a stub that just increments a counter. To make the emulation real, we must analyze the Utopia ROM and generate dispatch code for the boot sequence and main game loop.

## Acceptance Criteria
- [x] ROM analyzed: LoROM 8Mbit, reset vector at $81A7
- [x] Bootstrap sequence manually decoded (SEP #$30 through BRK)
- [x] ut_bootstrap_dispatch.c implements first ~20 instructions
- [x] Page-based dispatch index (ut_cpu_dispatch_index) in place
- [x] Build succeeds with no errors
- [x] Tests pass (utopia-static-audio-purity)
- [x] Pre-commit gate passes for T002

## Scope
**In scope:** Bootstrap dispatch (first ~20 instructions after reset), dispatch index infrastructure, ROM analysis script.
**Out of scope:** Full opcode coverage (will be done in subsequent tickets), S-SMP audio dispatch, PPU rendering logic.

## Dependencies
- T001 (project scaffold) — DONE

## Rollback
Remove generated dispatch files and revert CMakeLists.txt changes. The stub cpu_step remains as fallback.

## Notes
- Reset vector: $81A7 (LoROM bank 0x81, offset 0x01A7)
- Bootstrap sequence: SEP #$30 → PHA → DEX → PLX → PHX → PHB → LDA #$00 → BRK
- The BRK at 0x01B0 vectors to the NMI handler at $82B7 (based on ROM vectors)
- Full opcode decoding will be added incrementally in T003+