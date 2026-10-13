#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "utopia_static_recomp.h"

/* FNV-1a hash for frame buffer verification */
static uint32_t fnv1a_hash(const uint32_t *data, size_t len) {
    uint32_t hash = 2166136261u;
    for (size_t i = 0; i < len; i++) {
        uint32_t v = data[i];
        hash ^= (v & 0xFF); hash *= 16777619u;
        hash ^= ((v >> 8) & 0xFF); hash *= 16777619u;
        hash ^= ((v >> 16) & 0xFF); hash *= 16777619u;
        hash ^= ((v >> 24) & 0xFF); hash *= 16777619u;
    }
    return hash;
}

/* Reference frame hashes for first 10 frames (captured from static dispatch) */
    static const uint32_t REFERENCE_HASHES[10] = {
        0x05AACDC5, 0x05AACDC5, 0x05AACDC5, 0x05AACDC5, 0x05AACDC5,
        0x05AACDC5, 0x05AACDC5, 0x05AACDC5, 0x05AACDC5, 0x05AACDC5
    };

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <rom_path> <frame_count> [--verify]\n", argv[0]);
        return 1;
    }

    const char *rom_path = argv[1];
    uint32_t frame_count = (uint32_t)atoi(argv[2]);
    int verify_mode = (argc >= 4 && strcmp(argv[3], "--verify") == 0);

    if (frame_count == 0 || frame_count > 10000) {
        fprintf(stderr, "Invalid frame count (1-10000)\n");
        return 1;
    }

    /* Load ROM */
    FILE *f = fopen(rom_path, "rb");
    if (!f) {
        fprintf(stderr, "Cannot open ROM: %s\n", rom_path);
        return 1;
    }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    uint8_t *rom = (uint8_t *)malloc((size_t)size);
    if (!rom) { fclose(f); return 1; }
    size_t rd = fread(rom, 1, (size_t)size, f);
    fclose(f);
    if ((long)rd != size) { free(rom); return 1; }

    /* Create instance */
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
    int has_failure = 0;

    uint32_t frame_hashes[100] = {0};
    int hash_count = 0;

    printf("Advancing %u frames...\n", frame_count);

    while (completed < frame_count) {
        if (!utopia_recomp_advance_headless(game, none, 1, &result)) {
            fprintf(stderr, "Route failed at frame %u: %s\n",
                    completed, utopia_recomp_last_error(game));
            has_failure = 1;
            break;
        }

        completed++;

        /* Capture frame hash for first 10 frames */
        if (completed <= 10) {
            const uint32_t *fb = utopia_recomp_frame_bgra(game);
            uint32_t w = utopia_recomp_frame_width(game);
            frame_hashes[completed - 1] = fnv1a_hash(fb, w * 239);
            hash_count = completed;
        }

        /* Drain PCM */
        utopia_recomp_audio_discard(game);

        if (completed % 60 == 0) {
            printf("  Frame %u / %u... (instr=%llu, clock=%llu)\n",
                   completed, frame_count,
                   (unsigned long long)utopia_recomp_instruction_count(game),
                   (unsigned long long)utopia_recomp_master_clock(game));
        }
    }

    if (!has_failure) {
        printf("OK: %u frames advanced successfully\n", completed);
        printf("Current frame: %u\n", utopia_recomp_current_frame(game));
        printf("Instructions: %llu\n",
               (unsigned long long)utopia_recomp_instruction_count(game));
        printf("Master clock: %llu\n",
               (unsigned long long)utopia_recomp_master_clock(game));

        if (utopia_recomp_audio_overflowed(game)) {
            printf("WARNING: PCM overflow detected!\n");
            has_failure = 1;
        } else {
            printf("PCM overflow: no\n");
        }

        /* Print frame hashes for reference */
        if (hash_count > 0) {
            printf("\nFrame hashes (first %d):\n", hash_count);
            for (int i = 0; i < hash_count && i < (int)completed; i++) {
                printf("  Frame %d: 0x%08X\n", i + 1, frame_hashes[i]);
            }
        }

        if (verify_mode && hash_count > 0) {
            int mismatch = 0;
            for (int i = 0; i < hash_count; i++) {
                if (frame_hashes[i] != REFERENCE_HASHES[i]) {
                    printf("HASH MISMATCH frame %d: got 0x%08X, expected 0x%08X\n",
                           i + 1, frame_hashes[i], REFERENCE_HASHES[i]);
                    mismatch = 1;
                }
            }
            if (mismatch) {
                has_failure = 1;
            } else {
                printf("All hashes match reference.\n");
            }
        }
    }

    utopia_recomp_destroy(game);
    return has_failure ? 1 : 0;
}