---
ticket: T004
title: Write headless integration test (300 frames)
sprint: sprint-01
priority: high
status: in-progress
created: 2026-10-10
---

# T004 — Write Headless Integration Test (300 Frames)

## Context
T003 implemented the W65C816 CPU core. Now we need a comprehensive integration test
that advances 300 frames with the real ROM and verifies:
- No route failures
- No PCM overflow
- Frame buffer is non-empty
- Deterministic behavior

## Acceptance Criteria
- [ ] headless-test advances 300 frames with real ROM
- [ ] No route failures reported
- [ ] PCM overflow count is zero
- [ ] Frame buffer changes (non-static)
- [ ] Deterministic: two runs with same input produce identical output

## Scope
**In scope:** Enhance headless-test.c to run full 300-frame test with ROM, add deterministic hash verification.
**Out of scope:** Full game play verification (that's for later tickets), audio verification.

## Dependencies
- T003 (CPU core) — DONE

## Rollback
Revert headless-test.c changes.

## Notes
The current headless-test.c only tests without ROM. Need to integrate with real ROM path.