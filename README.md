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

**Not yet — headless only.** The static recompilation core is functional and passes 300-frame headless tests (601K instructions/frame, no route failures, constant frame hash 0x05AACDC5 = backdrop color), but the following critical components are **stubs only**:

- **PPU Renderer (modes 0-6)** — stub implementation; renders constant backdrop color (no visible game content)
- **S-DSP (32-phase)** — stub implementation; no audio output
- **S-SMP AOT Compilation** — S-SMP code translated (11,022 addresses, 151 epochs) but not yet integrated

The SDL2 frontend window opens but renders only the SNES backdrop color (black/blank). No game content is visible. The headless test is the current verification gate.

## About the Game

*Utopia: The Creation of a Nation* (1991, Celestial Software / Gremlin Interactive) is a **real-time strategy / city-building simulation** with a **sci-fi / space colonization** setting. The SNES port (USA, 1993, published by Jaleco) supports the **Super NES Mouse**.

**Setting:** The game takes place in the future on a new planet. You play a planetary governor evacuating a colony hit by an alien biological weapon. Your objective: colonize the new planet, manage the colony, and raise quality of life to reach utopia — while competing against an alien race colonizing the same planet.

**Key features:**
- **Real-time strategy / city-building** — build infrastructure, manage resources, population, taxes, trade
- **Micromanagement** — tax rate, birth rate, production chains, personnel allocation
- **Competition** — an alien race colonizes the same planet; no alliances possible, conflict inevitable
- **Espionage** — alien cities are off-map; rely on espionage to gather intelligence
- **10 scenarios** — each with a different planet and alien race (Eldorians, Vroarscans, Soomanii, etc.)
- **Isometric graphics** — built with Deluxe Paint
- **SNES Mouse support** — the SNES port supports the Super NES Mouse peripheral
- **Expansion disk** — *Utopia: The New Worlds* adds 10 more scenarios (e.g., Sal-Kadeem with oil-covered terrain)

The SNES port (USA, 8 Mbit LoROM, no co-processor) was published by Jaleco and supports the Super NES Mouse peripheral.

## What fully static recompilation means

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