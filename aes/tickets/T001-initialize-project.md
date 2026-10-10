# T001 — Initialize Project Structure

## Context
Greenfield project: static recompilation of Utopia: The Creation of a Nation (SNES, USA, 8 Mbit LoROM) to native C. Mirrors the SimCity-SNES-Static-Recomp architecture.

## Acceptance Criteria
- [ ] Directory structure matches SimCity pattern (static-recomp/, frontend/linux/, frontend/windows/, tools/, docs/, aes/)
- [ ] CMakeLists.txt at root and in static-recomp/ compiles the skeleton core
- [ ] Public API header `static-recomp/include/utopia_static_recomp.h` exists with the full API contract
- [ ] `make build` succeeds (core library only, no ROM required)
- [ ] `make test` passes (no ROM-dependent tests)
- [ ] `make check` passes (lint, format, no diagnostics)
- [ ] `docs/VISION.md`, `docs/REQUIREMENTS.md`, `docs/ROADMAP.md` created
- [ ] `CLAUDE.md` operational contract written
- [ ] AES infrastructure installed (kanban, hooks, verify-implementation.sh)
- [ ] Git initialised with initial commit

## Scope
**In scope:** All scaffolding, empty source skeletons, CMake targets, CI workflow, docs templates, AES setup.
**Out of scope:** Generated dispatch code, actual game logic implementation, frontend UI.

## Dependencies
None — this is the first ticket.

## Rollback
N/A — nothing to undo except the initial commit.

## Notes
The Utopia ROM is at `rom/extracted/Utopia - The Creation of a Nation (USA).sfc` (SHA-256: `2500d6c846c78bcb729f15535bf2b852a120411891cabaaaa6fc407906d0214e`). It must never be committed.