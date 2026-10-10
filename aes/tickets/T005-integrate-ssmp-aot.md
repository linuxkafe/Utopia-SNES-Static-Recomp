---
ticket: T005
title: Integrate S-SMP AOT Authority
sprint: sprint-01
priority: high
status: in-progress
created: 2026-10-10
---

# T005 — Integrate S-SMP AOT Authority

## Context
T004 completed the 300-frame headless integration test with the CPU core. Now we need to integrate the S-SMP (Sony SPC700) audio processor using the Ahead-Of-Time (AOT) compilation approach, following the SimCity-SNES-Static-Recomp pattern.

## Acceptance Criteria
- [ ] S-SMP AOT authority generated from Utopia's SPC700 ROM code
- [ ] Fail-closed execution: unknown S-SMP PC triggers route failure
- [ ] S-SMP epoch manifest generated
- [ ] S-SMP/APU I/O access manifest generated
- [ ] Audio transport (S-CPU to S-SMP upload) implemented
- [ ] Project-owned S-DSP (32-phase) integrated
- [ ] PCM output at 32,040 Hz stereo verified
- [ ] No PCM overflow in 300-frame test

## Scope
**In scope:** S-SMP AOT generation, audio transport, S-DSP integration, PCM output.
**Out of scope:** Full game audio verification (requires game-specific audio code analysis).

## Dependencies
- T004 (300-frame headless test) — DONE

## Notes
- Follow SimCity-SNES-Static-Recomp audio architecture: static-audio/snes9x-bapu-aot for S-SMP, static-audio/simcity-project-dsp for S-DSP
- Utopia's S-SMP program must be extracted from ROM and analyzed for AOT compilation
- S-SMP epoch manifest maps S-SMP PC ranges to compiled code blocks
- Audio transport handles S-CPU to S-SMP ARAM upload during boot