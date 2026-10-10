# ROADMAP

## Backlog

| # | Item | Impact | Effort | Priority | Status |
|---|------|--------|--------|----------|--------|
| 1 | Generate W65C816 dispatch for Utopia ROM | Critical | High | High | [TODO] |
| 2 | Implement PPU renderer (mode 0–6) | Critical | High | High | [TODO] |
| 3 | Integrate S-SMP AOT (Snes9x bapu) | Critical | Medium | High | [TODO] |
| 4 | Implement project-owned S-DSP | Critical | Medium | High | [TODO] |
| 5 | Write headless integration test (300 frames) | High | Low | Medium | [TODO] |
| 6 | Create SDL2 Linux frontend | High | Medium | Medium | [TODO] |
| 7 | Add WRAM write cheat API | Medium | Low | Low | [TODO] |
| 8 | Add snapshot save/load | Medium | Medium | Medium | [TODO] |
| 9 | Cross-compile for Windows | Medium | Low | Low | [TODO] |
| 10 | Deploy script (deploy-linux.sh) | Low | Low | Low | [TODO] |

## Principles
- Each item above must have a ticket in `aes/tickets/` before work begins.
- "Done" means: test passes, lint passes, and documentation is updated.
- No widescreen support for Utopia — the game uses a fixed 4:3 layout.

## Known Constraints
- The Utopia ROM has no known widescreen map data (unlike SimCity). The core should not attempt margin expansion.
- Utopia's PPU usage is less complex than SimCity's; mode 7 (rotated/scrolled BG) is unlikely but must be handled gracefully.