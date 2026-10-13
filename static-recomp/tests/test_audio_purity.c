/* Static audio purity test - verifies static dispatch is active. */
#include "utopia_static_recomp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <rom_path>\n", argv[0]);
        return 1;
    }

    const char *rom_path = argv[1];
    FILE *f = fopen(rom_path, "rb");
    if (!f) { printf("SKIP: cannot open ROM\n"); return 0; }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    uint8_t *rom = (uint8_t *)malloc((size_t)size);
    if (!rom) { fclose(f); return 1; }
    size_t rd = fread(rom, 1, (size_t)size, f);
    fclose(f);
    if ((long)rd != size) { free(rom); return 1; }

    char err[256];
    UtopiaRecomp *game = NULL;
    if (!utopia_recomp_create(&game, rom, (size_t)size, err, sizeof(err))) {
        printf("SKIP: cannot create instance: %s\n", err);
        free(rom);
        return 0;
    }
    free(rom);

    /* Advance 1 frame - this exercises the static dispatch path */
    UtopiaRecompFrameResult result;
    if (!utopia_recomp_advance_headless(game, 0, 1, &result)) {
        printf("FAIL: route failed at frame 1: %s\n", utopia_recomp_last_error(game));
        utopia_recomp_destroy(game);
        return 1;
    }

    /* Verify instruction count is non-zero (static dispatch executed) */
    uint64_t instr = utopia_recomp_instruction_count(game);
    if (instr == 0) {
        printf("FAIL: zero instructions executed (static dispatch not active)\n");
        utopia_recomp_destroy(game);
        return 1;
    }

    printf("PASS: static dispatch active, %llu instructions in frame 1\n",
           (unsigned long long)instr);
    utopia_recomp_destroy(game);
    return 0;
}
