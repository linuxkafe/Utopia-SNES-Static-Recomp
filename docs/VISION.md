# VISION

## Problem
*Utopia: The Creation of a Nation* (SNES, 1996, USA, 8 Mbit LoROM, no co-processor) is a strategy game that runs on real SNES hardware via a W65C816 CPU and custom PPU/S-SMP/S-DSP sub-systems. To run it on modern systems without emulator overhead, interpretive latency, or JIT warm-up, we need a native static recompilation.

## Solution
Translate Utopia's W65C816 instructions into generated native C dispatch functions keyed by exact CPU state and program counter. The generated code runs directly on x86_64/ARM64 hosts without any interpreter loop, opcode decoder, or runtime recompiler. The static core handles the full SNES machine model — bus, WRAM, I/O, DMA, HDMA, PPU rendering, S-SMP audio, S-DSP sound effects — all in C.

## Value Proposition
- **Zero emulator overhead**: the guest CPU instructions become native machine instructions
- **Deterministic**: exact same execution path every run; snapshot/replay supported
- **Portable**: Linux (SDL2) and Windows (Win32/GDI) frontends from the same core
- **Cheatable**: host-side WRAM access for mods and cheats between frames
- **Auditable**: no hidden fallbacks, no runtime bytecode — fully transparent to the compiler

## Scope
This project covers the game core and headless test infrastructure. It does **not** include widescreen support (out of scope for Utopia's 4:3 layout), PC emulation, or online multiplayer.

## Evidence Standard
"Works" means: headless test advances N frames with no route failure, no PCM overflow, and frame buffer hash matches reference capture (Mesen/Snes9x). Every behavioural claim must be backed by a test or a documented reference in `docs/`.