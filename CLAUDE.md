# Utopia SNES Static Recomp — Operational Contract

## Project
**Utopia: The Creation of a Nation** (SNES, USA, 8 Mbit LoROM, no co-processor)
Static recompilation to native C, mirroring the SimCity-SNES-Static-Recomp
architecture. SDL2 Linux frontend + Win32/GDI Windows frontend.

## Essential Commands
- `make setup` — install build deps (cmake, gcc/g++, libsdl2-dev)
- `make build` — configure + build (Release)
- `make test` — run CTest
- `make check` — lint + tests + format
- `make doctor` — environment diagnostics
- `make clean` — remove build artefacts
- `make deploy` — stage dist/linux/ via deploy-linux.sh

## Critical Files
- `static-recomp/include/utopia_static_recomp.h` — public API
- `static-recomp/src/utopia_static_recomp.c` — public API implementation
- `static-recomp/src/ut_v11_runtime.c` — machine, bus, CPU, scheduler
- `static-recomp/src/ut_v28_video.c` — PPU rendering
- `static-recomp/CMakeLists.txt` — core build
- `frontend/linux/main.c` — SDL2 frontend

## Never-Do List
- Never commit the ROM or any derivative ROM data.
- Never ship an interpreter/JIT/emulator fallback — this is fully static.
- Never modify generated dispatch code by hand; regenerate via `make generate`.
- Never touch PPU/camera WRAM addresses behind the core's back.
- Never skip the per-frame instruction guard.

## Evidence Required
- All claims about ROM addresses, timing, or behaviour must cite a test or a
  verified reference (Mesen/Snes9x capture, or a documented reverse-engineering
  note in `docs/`).
- "Works" means: headless test advances N frames with no route failure and no
  PCM overflow, and the frame hash matches the reference capture.