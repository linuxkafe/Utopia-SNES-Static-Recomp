# REQUIREMENTS

## Functional Requirements

### FR-001: ROM Loading
The system shall load an exact 524,288-byte Utopia (USA) .sfc ROM image and verify its SHA-256 hash before proceeding.

### FR-002: CPU Execution
The W65C816 CPU shall execute instructions via generated static dispatch keyed by exact PC context. No general-purpose interpreter loop shall be present in production dispatch.

### FR-003: Per-Frame Instruction Guard
Each frame shall be bounded by a maximum instruction count (`UTOPIA_FRAME_INSTRUCTION_GUARD`). If exceeded, the route fails with a diagnostic message.

### FR-004: PPU Rendering
The PPU shall render the first visible scanline each frame into an ARGB8888 framebuffer. The renderer shall handle modes 0–6, BG1/BG2/BG3/BG4, window effects, and color math as exercised by the ROM.

### FR-005: S-SMP Audio
The S-SMP shall execute its program from the cartridge's ARAM copy. Unknown PC values during audio epochs shall fail-closed with a diagnostic.

### FR-006: S-DSP Audio
The project-owned 32-phase S-DSP shall implement register timing, BRR decoding, Gaussian interpolation, envelopes, noise, pitch modulation, echo/FIR, and signed 16-bit stereo PCM at 32,040 Hz.

### FR-007: Controller Input
Two controller ports shall be accessible. Each frame receives an input mask (bitmask of button states). Controller history shall be preserved for snapshot replay.

### FR-008: SRAM Persistence
Battery-backed SRAM (32 KiB) shall be preserved across resets and savable/loading via the public API.

### FR-009: Snapshots
Save/load snapshots shall capture full runtime state (CPU registers, PPU state, S-SMP, S-DSP, WRAM, SRAM, controller history) and be deterministically replayable.

### FR-010: WRAM Write API
Host code shall be able to poke guest WRAM between frames via `utopia_recomp_write_wram()`. Writes are not visible mid-frame.

### FR-011: PCM Output
The core shall produce interleaved stereo signed 16-bit PCM at 32,040 Hz. The frontend owns playback.

### FR-012: NTSC Timing
Frame advancement shall respect NTSC timing: 262 scanlines, ~357,366 master clocks per frame, nominal 60.0988 Hz presentation rate.

## Non-Functional Requirements

### NFR-001: Build
The core must build with CMake ≥ 3.20, GCC or Clang, C11 standard. The Linux frontend requires SDL2 devel packages.

### NFR-002: Performance
On a reference x86_64 host, a single frame (16.6 ms budget at 60 Hz) shall complete in under 15 ms at `-O2`/`-O3` Release.

### NFR-003: Determinism
Given identical ROM and input sequence, the core shall produce byte-identical framebuffers and PCM output across runs.

### NFR-004: No Emulator Fallback
The release build shall contain no interpreter, JIT, or emulator fallback path. Any unknown state shall fail closed.

### NFR-005: ROM Not Bundled
The ROM is never committed or distributed with the build. Runtime requires an externally supplied matching image.

### NFR-006: Generated Code Immutability
Generated dispatch code is produced by `make generate` and must not be hand-edited. Source-of-truth is the generation script.