#include "utopia_static_recomp.h"
#include <stdio.h>
#include <string.h>

/* Contract test for the host-side WRAM write API. */

static int test_wram_write_basic(const char *rom_path) {
    FILE *f = fopen(rom_path, "rb");
    if (!f) { printf("SKIP: cannot open ROM\n"); return 0; }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    uint8_t *rom = (uint8_t *)malloc((size_t)size);
    if (!rom) { fclose(f); return 0; }
    size_t rd = fread(rom, 1, (size_t)size, f);
    fclose(f);
    if ((long)rd != size) { free(rom); return 0; }

    char err[256];
    UtopiaRecomp *game = NULL;
    if (!utopia_recomp_create(&game, rom, (size_t)size, err, sizeof(err))) {
        printf("SKIP: cannot create instance: %s\n", err);
        free(rom);
        return 0;
    }
    free(rom);

    /* Write a known value to WRAM offset 0x0000. */
    uint8_t val = 0x42u;
    int ok = utopia_recomp_write_wram(game, 0x0000u, &val, 1u);
    if (!ok) { printf("FAIL: write_wram returned 0\n"); utopia_recomp_destroy(game); return 1; }

    /* Read it back. */
    uint8_t readback = 0u;
    ok = utopia_recomp_read_wram(game, 0x0000u, &readback, 1u);
    if (!ok) { printf("FAIL: read_wram returned 0\n"); utopia_recomp_destroy(game); return 1; }
    if (readback != 0x42u) { printf("FAIL: readback 0x%02X != 0x42\n", readback); utopia_recomp_destroy(game); return 1; }

    /* Out-of-bounds write should be rejected. */
    ok = utopia_recomp_write_wram(game, 0x1FFFu, &val, 2u);
    if (ok) { printf("FAIL: out-of-bounds write was accepted\n"); utopia_recomp_destroy(game); return 1; }

    printf("PASS: wram write contract\n");
    utopia_recomp_destroy(game);
    return 0;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("SKIP: no ROM path provided\n");
        return 0;
    }
    return test_wram_write_basic(argv[1]);
}