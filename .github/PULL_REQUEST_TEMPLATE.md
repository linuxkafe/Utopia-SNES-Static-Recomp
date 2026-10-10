# Utopia SNES Static Recomp — PULL REQUEST TEMPLATE

## What does this PR do?
[Describe the change in 1-2 sentences.]

## What is the expected behaviour?
[What should happen? E.g. "The game boots and the title screen renders correctly."]

## How was this tested?
- [ ] `make check` passes (lint, tests, format)
- [ ] Headless test advances N frames with no route failure
- [ ] Frame buffer matches reference capture (if applicable)
- [ ] No PCM overflow reported

## Evidence
- [ ] All claims cite a test or documented reference (Mesen/Snes9x capture or `docs/` note)
- [ ] ROM hash verified against `ROM-REQUIREMENTS.txt`

## Checklist
- [ ] No interpreter/JIT/emulator fallback introduced
- [ ] Generated dispatch code was regenerated, not hand-edited
- [ ] No PPU/camera WRAM addresses touched behind the core's back
- [ ] Per-frame instruction guard still active