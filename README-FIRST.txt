# Utopia SNES Static Recomp — README-FIRST

Before building or running, read README.md.

The ROM is not included in this repository. You must supply your own legally
obtained copy of *Utopia: The Creation of a Nation* (USA), matching
ROM-REQUIREMENTS.txt.

Build:
  make setup
  make build

Run (Linux):
  ./build/frontend/linux/utopia-linux --rom /path/to/Utopia.sfc

Headless test:
  ./build/frontend/linux/headless-test /path/to/Utopia.sfc 300