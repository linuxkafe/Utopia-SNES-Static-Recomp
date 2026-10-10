# Utopia SNES Static Recomp

Native static recompilation core for *Utopia: The Creation of a Nation*
(SNES, USA, 8 Mbit LoROM, no co-processor). Windows and Linux frontends
are supported; the core builds on both platforms.

The original game ROM is not included. Use an externally supplied, legally
obtained ROM matching `ROM-REQUIREMENTS.txt`.

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

## Licensing

This repository ships no `LICENSE` file. The project is derived from the
SimCity-SNES-Static-Recomp architecture. Any Snes9x-derived code in the
audio path remains under its original license.

## Verification

"Walking" means: headless test advances 300 frames with no route failure,
no PCM overflow, and the frame buffer is non-empty. All behavioural claims
must be backed by a test or a documented reference in `docs/`.