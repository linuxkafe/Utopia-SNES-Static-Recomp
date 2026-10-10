---
ticket: T006
title: Full S-SMP AOT Generation from ROM
sprint: sprint-01
priority: high
status: in-progress
created: 2026-10-10
---

# T006 — Full S-SMP AOT Generation from ROM

## Context
T005 integrated minimal S-SMP/AOT stubs that allow the build and 300-frame test to pass. Now we need to generate the full S-SMP AOT authority from the actual Utopia ROM's S-SMP program, following the SimCity-SNES-Static-Recomp pattern.

## Acceptance Criteria
- [ ] S-SMP program extracted from ROM and analyzed for all reachable PC addresses
- [ ] AOT code bitmap generated covering all reachable S-SMP instructions
- [ ] S-SMP epoch manifest generated mapping PC ranges to compiled epochs
- [ ] S-SMP/APU I/O access manifest generated
- [ ] AOT compilation produces valid dispatch functions for all reachable S-SMP PCs
- [ ] Fail-closed execution: any unknown S-SMP PC triggers route failure
- [ ] 300-frame test passes with real S-SMP execution (no more stub)
- [ ] PCM output matches reference capture (or is deterministic)

## Scope
**In scope:** Full S-SMP AOT compilation pipeline, epoch analysis, code bitmap generation, AOT authority generation.
**Out of scope:** Full game audio verification (requires game-specific audio code analysis), S-DSP waveform accuracy certification.

## Dependencies
- T005 (minimal audio stubs) — DONE
- ROM analysis tools (Python scripts for S-SMP disassembly)

## Rollback
Revert to minimal stubs (T005 state). The AOT generation scripts are separate and can be removed cleanly.

## Notes
- Follow SimCity-SNES-Static-Recomp audio architecture: snes9x-bapu-aot for S-SMP, project-owned S-DSP
- Utopia's S-SMP program is 16KB at ROM offset 0x2000-0x6000
- Need to generate epoch topology from S-SMP program flow analysis
- AOT authority bitmap must cover all reachable PCs; unknown PC = fail-closed