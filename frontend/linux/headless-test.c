#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utopia_static_recomp.h"

/* Headless smoke test: advance N frames with no input, verify
   the route does not fail and audio does not overflow. */

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <rom_path> <frame_count>\n", argv[0]);
        return 1;
    }
    const char *rom_path = argv[1];
    uint32_t frame_count = (uint32_t)atoi(argv[2]);

    FILE *f = fopen(rom_path, "rb");
    if (!f) { fprintf(stderr, "Cannot open ROM: %s\n", rom_path); return 1; }
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
        fprintf(stderr, "Create failed: %s\n", err);
        free(rom);
        return 1;
    }
    free(rom);

    uint32_t completed = 0u;
    uint16_t none = 0u;
    UtopiaRecompFrameResult result;
    while (completed < frame_count) {
        if (!utopia_recomp_advance_headless(game, none, 1, &result)) {
            fprintf(stderr, "Route failed at frame %u: %s\n",
                    completed, utopia_recomp_last_error(game));
            utopia_recomp_destroy(game);
            return 1;
        }
        completed++;
        /* Drain any PCM produced. */
        utopia_recomp_audio_discard(game);
    }

    printf("OK: %u frames advanced successfully\n", completed);
    printf("Current frame: %u\n", utopia_recomp_current_frame(game));
    printf("Instructions: %llu\n",
           (unsigned long long)utopia_recomp_instruction_count(game));
    printf("Master clock: %llu\n",
           (unsigned long long)utopia_recomp_master_clock(game));
    if (utopia_recomp_audio_overflowed(game)) {
        printf("WARNING: PCM overflow detected!\n");
        utopia_recomp_destroy(game);
        return 1;
    }
    printf("PCM overflow: no\n");
    utopia_recomp_destroy(game);
    return 0;
}