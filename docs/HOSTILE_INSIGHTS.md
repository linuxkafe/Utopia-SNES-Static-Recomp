# HOSTILE INSIGHTS

## [Architecture] - Static dispatch must cover the full ROM address space
- **Task**: Initial ROM analysis
- **Insight**: Utopia's W65C816 code is concentrated in specific banks. The dispatch table must cover 0x8000–0xFFFF in each bank, but not all addresses are executable.
- **Origin**: ROM header analysis at 0x7FC0
- **Impact**: Missed addresses cause fail-closed at runtime instead of compile-time
- **Applied To**: All dispatch generation
- **Date**: 2026-10-10

## [Audio] - S-SMP AOT authority is game-specific
- **Task**: Audio architecture decision
- **Insight**: The Snes9x bapu AOT must be generated per-game. The authority bitmap is unique to Utopia's S-SMP program. Sharing code between projects is possible but the authority bitmaps are not interchangeable.
- **Origin**: SimCity-SNES-Static-Recomp audio architecture review
- **Impact**: Cannot reuse SimCity's audio AOT; must regenerate for Utopia
- **Applied To**: `static-recomp/static-audio/` structure
- **Date**: 2026-10-10