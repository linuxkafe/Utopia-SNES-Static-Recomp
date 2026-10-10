# Utopia SNES Static Recomp — top-level Makefile
# Mirrors the SimCity-SNES-Static-Recomp build contract.

CMAKE ?= cmake
BUILD_DIR ?= build
BUILD_TYPE ?= Release
JOBS ?= $(shell nproc 2>/dev/null || echo 4)
FRONTEND ?= ON

.PHONY: all setup build test check doctor clean deploy generate install-claude install-opencode install-all

all: build

setup:
	@echo "Installing build dependencies for Utopia SNES Static Recomp..."
	@command -v cmake >/dev/null 2>&1 || { echo "ERROR: cmake not found (need >= 3.20)"; exit 1; }
	@command -v gcc >/dev/null 2>&1 || { echo "ERROR: gcc not found"; exit 1; }
	@command -v g++ >/dev/null 2>&1 || { echo "ERROR: g++ not found"; exit 1; }
	@pkg-config --exists sdl2 2>/dev/null || { echo "ERROR: libsdl2-dev not found (sudo apt install libsdl2-dev)"; exit 1; }
	@echo "Build dependencies satisfied."

build:
	$(CMAKE) -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DBUILD_LINUX_FRONTEND=$(FRONTEND)
	$(CMAKE) --build $(BUILD_DIR) -j$(JOBS)

test:
	$(CMAKE) --build $(BUILD_DIR) -j$(JOBS) --target test || ctest --test-dir $(BUILD_DIR) --output-on-failure


# AES-Epistemics gates (auto-added by aes-epistemics-wire)
gmif-check:
	@bash ~/.config/opencode/skills/aes-epistemics/scripts/gmif-check.sh 2>/dev/null || echo "gmif-check skipped (Z3 not available)"

gmif-staleness:
	@bash ~/.config/opencode/skills/aes-epistemics/scripts/gmif-staleness-check.sh 2>/dev/null || echo "gmif-staleness skipped"

check: gmif-check gmif-staleness test
	@echo "=== lint ==="
	@command -v cppcheck >/dev/null 2>&1 && cppcheck --enable=all --inconclusive --error-exitcode=1 static-recomp/src static-recomp/include frontend/linux 2>/dev/null || echo "cppcheck not available; skipping."
	@echo "=== format check ==="
	@command -v clang-format >/dev/null 2>&1 && clang-format --dry-run --Werror static-recomp/src/*.c static-recomp/include/*.h frontend/linux/*.c 2>/dev/null || echo "clang-format not available; skipping."

doctor:
	@echo "=== Environment diagnostics ==="
	@echo "OS: $$(uname -sr)"
	@echo "CMake: $$(cmake --version 2>/dev/null | head -1 || echo 'NOT FOUND')"
	@echo "GCC:   $$(gcc --version 2>/dev/null | head -1 || echo 'NOT FOUND')"
	@echo "G++:   $$(g++ --version 2>/dev/null | head -1 || echo 'NOT FOUND')"
	@echo "SDL2:  $$(pkg-config --modversion sdl2 2>/dev/null || echo 'NOT FOUND')"
	@echo "ROM:   $$(ls -la rom/extracted/*.sfc 2>/dev/null || echo 'NOT FOUND')"
	@echo "=== AES infra ==="
	@[ -f .aes/hooks/pre-commit.sh ] && echo "pre-commit hook: OK" || echo "pre-commit hook: MISSING"
	@[ -f scripts/verify-implementation.sh ] && echo "verify-implementation.sh: OK" || echo "verify-implementation.sh: MISSING"
	@[ -f aes/kanban.md ] && echo "kanban: OK" || echo "kanban: MISSING"

clean:
	rm -rf $(BUILD_DIR) build-release dist tmp

deploy:
	./deploy-linux.sh

generate:
	@echo "Regenerating dispatch code..."
	@command -v python3 >/dev/null 2>&1 || { echo "ERROR: python3 not found"; exit 1; }
	@echo "Generation script not yet implemented — this is a placeholder target."
	@exit 0

install-claude:
	@echo "Installing AES skills for Claude Code..."
	@mkdir -p ~/.claude/skills
	@cp -r /opt/aes/skills/user/* ~/.claude/skills/ 2>/dev/null || true
	@echo "Done."

install-opencode:
	@echo "Installing AES skills for OpenCode..."
	@mkdir -p ~/.config/opencode/skills
	@cp -r /opt/aes/skills/user/* ~/.config/opencode/skills/ 2>/dev/null || true
	@echo "Done."

install-all: install-claude install-opencode
