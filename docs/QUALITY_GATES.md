# QUALITY GATES

## Gate: Static Route Coverage
Every reachable PC address in the Utopia ROM must have a dispatch entry. Missing entries are BLOCKERs.

## Gate: PCM Overflow
`pcm_overflows` must be zero after any 300-frame headless test. Non-zero is BLOCKER.

## Gate: Frame Hash Match
The first 300 framebuffers must match the reference capture (Mesen/Snes9x) within tolerance. Mismatch is BLOCKER.

## Gate: S-SMP Fail-Closed
Any S-SMP execution at an unmanifested PC shall call `abort()` or equivalent. Silently skipping is BLOCKER.

## Gate: Per-Frame Guard
If the instruction guard triggers, the frame is marked failed and a diagnostic is logged. The route must not silently continue.

## Gate: SRAM Integrity
SRAM must survive reset and be correctly persisted to disk on exit. Corruption is MAJOR.

## Gate: No Emulator in Release
`nm` / `objdump` of the release binary shall not reveal any symbols from snes9x, bsnes, or other emulator cores (except the static AOT bapu audio which is an AOT-compiled authority, not an interpreter).