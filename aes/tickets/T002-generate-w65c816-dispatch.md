# T002 — Generate W65C816 Dispatch for Utopia ROM

## Context
T001 established the project scaffold. The core's CPU step is currently a stub
(`sc_v11_cpu_step()` in `ut_v11_cpu.c` just increments a counter). To make the
static recompilation real, we must analyse the Utopia ROM's W65C816 code, map
every reachable PC to a native C dispatch, and emit the generated dispatch tables.

## Acceptance Criteria
- [ ] ROM entry point identified and verified (cold reset vector at $7FC0)
- [ ] All reachable code banks enumerated (LoROM: banks 0x80, 0xA0, 0xC0, 0xE0)
- [ ] Bootstrap dispatch table generated for the first 100 instructions
- [ ] Generated dispatch source compiles with the core
- [ ] Headless test advances at least 100 frames without route failure
- [ ] No unknown S-SMP PC values during boot

## Scope
**In scope:** ROM analysis, entry-point verification, bootstrap dispatch generation,
generated dispatch source files.
**Out of scope:** Full game-code dispatch (requires reverse engineering of all
game functions), S-SMP AOT authority generation, PPU rendering logic.

## Dependencies
- T001 (scaffold) — DONE
- ROM analysis tools (python3 + hexdump) — available

## Rollback
Delete generated dispatch files; the stub in `ut_v11_cpu.c` remains as fallback.

## Notes
The Utopia ROM is at `rom/extracted/Utopia - The Creation of a Nation (USA).sfc`
(SHA-256: `2500d6c846c78bcb729f15535bf2b852a120411891cabaaaa6fc407906d0214e`).
It must never be committed.