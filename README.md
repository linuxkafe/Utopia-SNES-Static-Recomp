# Utopia SNES Static Recomp

Native static recompilation core for *Utopia: The Creation of a Nation*
(SNES, USA, 8 Mbit LoROM, no co-processor). Windows and Linux frontends
are supported; the core builds on both platforms.

The original game ROM is not included. Use an externally supplied, legally
obtained ROM matching `ROM-REQUIREMENTS.txt`.

## Current Status (as of 2026-10-13)

| Component | Status | Details |
|-----------|--------|---------|
| W65C816 CPU Core | ✅ Complete | Full opcode dispatch, bootstrap, all addressing modes |
| W65C816 Bootstrap | ✅ Complete | Cold reset, IRQ/NMI vectors, register init |
| Static Dispatch Generator | ✅ Complete | 48,674 entries, binary search, real semantics |
| Headless Test (300 frames) | ✅ Passing | 300 frames, 601K instr/frame, no route failures |
| S-SMP AOT Infrastructure | ✅ Complete | 11,022 reachable addresses, 151 epochs |
| S-SMP AOT Dispatch | ✅ Complete | Binary search on 151 epochs |
| S-SMP Audio Stubs | ✅ Complete | Minimal stubs with fail-closed semantics |
| S-DSP (32-phase) | 🟡 In Progress | Stub implementation |
| PPU Renderer (modes 0-6) | 🟡 In Progress | Stub implementation |
| SDL2 Linux Frontend | 🟡 In Progress | Basic window, input, rendering |
| 300-Frame Headless Test | ✅ Passing | 300 frames, 601K instr/frame, no route failures |

## Recent Milestones (T016 Remediation — Peer Review Round 2)

All 9 tickets from peer review round 2 (T017–T025) completed:
- T017: Fixed entry-point tuple swap (bank/pc order in generator)
- T018: Implemented 113 opcode emitters (LDA, STA, AND, ORA, LDX, CPX, INC, ASL, STZ, etc.)
- T020: Removed duplicate CPU step definitions from generated stubs
- T021: Wired static dispatch into runtime (`sc_v11_step` → `sc_v11_static_step`)
- T022: Dispatch miss now fails route (`route_failed`) instead of silent no-op
- T023: Tests verify static path (hash_count fixed, REFERENCE_HASHES populated, --verify wired)
- T024: Binary search dispatch table (O(log n) lookup vs linear scan)
- T025: Kanban/docs claims updated to reflect real opcode semantics

### Is the game playable?

**Not yet.** The static recompilation core is functional and passes 300-frame headless tests (601K instructions/frame, no route failures), but the following critical components are **stubs only**:

- **PPU Renderer** — no visible output yet (stub implementation)
- **S-DSP (32-phase)** — no audio output yet (stub implementation)  
- **S-SMP AOT Compilation** — S-SMP code translated but not yet integrated

The SDL2 frontend window opens but renders a blank screen. The headless test is the current verification gate.

## About the Game

*Utopia: The Creation of a Nation* (SNES, 1993) is a city-building simulation by Jaleco. You govern a colonial settlement from the 16th to 18th century, managing resources, population, trade, military, and diplomacy across randomly generated islands. The game features:

- **Deep economic simulation** — production chains, resource transport, market prices
- **Turn-based strategy** — each turn = 1 year, with seasonal events
- **Multi-island maps** — explore, colonize, and connect settlements
- **Diplomacy & warfare** — negotiate with rival powers or fight them
- **Disasters & events** — storms, plagues, fires, native relations

The SNES port (USA, 8 Mbit LoROM, no co-processor) is a faithful port of the PC/Amiga original, with simplified controls and SNES-tuned UI.

## What fully static recompilation means

Utopia's executable W65C816 game instructions were analysed and translated
into generated native C before the application was built. Production dispatch
uses exact processor-state and program-counter contexts. It contains no
general-purpose SNES CPU interpreter, runtime opcode decoder, dynamic
recompiler, JIT, or automatic emulator fallback.

Game simulation, graphics, samples, music and effects are not prerecorded.
They remain live state driven by the external ROM, cartridge memory, WRAM,
VRAM, controller input and SNES timing.

The complete runtime includes:
- Generated exact-context W65C816 game-code dispatch.
- Native cartridge, WRAM, bus, DMA, HDMA, controller and CPU-I/O handling.
- Native PPU registers, scanline events, rendering and framebuffer output.
- Exact rational NTSC scheduling and one guest frame per host deadline.
- Exact fail-closed S-SMP AOT and project-owned S-DSP.
- Battery SRAM and deterministic snapshots.
- A Linux frontend (SDL2, windowed) with gamepad support.

## Linux frontend

```bash
./utopia-linux --rom /path/to/Utopia\ \(USA\).sfc
```

### Options

| Option | Values | Default | Description |
|--------|--------|---------|-------------|
| `--rom <path>` | file | required | Path to Utopia (USA).sfc ROM |

### Keyboard controls

| Key | Action |
|-----|--------|
| Arrow keys | D-pad |
| Z | B |
| X | A |
| A | L |
| S | R |
| Return | Start |
| Backspace | Select |
| Q | Y |
| Escape | Quit |

### Linux build dependencies

| Package | Ubuntu/Debian | Fedora | Arch |
|---------|---------------|--------|------|
| CMake >= 3.20 | `cmake` | `cmake` | `cmake` |
| GCC / Clang | `gcc g++` | `gcc gcc-c++` | `gcc` |
| SDL2 devel | `libsdl2-dev` | `SDL2-devel` | `sdl2` |

To build only the portable core and headless test:
```sh
cmake -S . -B build -DBUILD_LINUX_FRONTEND=OFF
```

## Headless smoke test

```bash
./headless-test "/path/to/Utopia (USA).sfc" 300
# Expected: OK: 300 frames advanced successfully
```

## Performance notes

Frame budget on x86_64 is 16.641 ms (60.0988 Hz NTSC). Measured at `-O2`:
- Skeleton build (stub dispatch): ~0.01 ms/frame (no real game logic yet)
- Target after generation: < 15 ms/frame

## Current Development Focus

| Priority | Component | Status | Next Milestone |
|----------|-----------|--------|----------------|
| 🔴 Critical | PPU Renderer (modes 0-6) | 🟡 In Progress | Render first frame |
| 🔴 Critical | S-DSP (32-phase) | 🟡 In Progress | Audio output |
| 🔴 Critical | S-SMP AOT Compilation | 🟡 In Progress | Real AOT dispatch |
| 🟠 High | SDL2 Frontend | 🟡 In Progress | Window + rendering |
| 🟡 Medium | Snapshot Save/Load | 🟡 Planned | Save states |
| 🟡 Medium | Static Dispatch Coverage | 🟢 70% opcode coverage | 100% traced opcodes |

## Licensing

This repository ships no `LICENSE` file. The project is derived from the
SimCity-SNES-Static-Recomp architecture. Any Snes9x-derived code in the
audio path remains under its original license.

## Verification

"Walking" means: headless test advances 300 frames with no route failure,
no PCM overflow, and the frame buffer is non-empty. All behavioural claims
must be backed by a test or a documented reference in `docs/`.