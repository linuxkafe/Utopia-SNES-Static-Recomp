#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "utopia_static_recomp.h"

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480
#define TITLE "Utopia SNES Static Recomp"

static int g_running = 1;
static UtopiaRecomp *g_game = NULL;
static SDL_Window *g_window = NULL;
static SDL_Renderer *g_renderer = NULL;
static SDL_AudioDeviceID g_audio_dev = 0;
static char g_rom_path[4096] = "";

static void quit(int code) {
    g_running = 0;
    (void)code;
}

static void init_audio(void) {
    SDL_AudioSpec wanted, gotten;
    memset(&wanted, 0, sizeof(wanted));
    wanted.freq     = (int)utopia_recomp_host_audio_sample_rate();
    wanted.format   = AUDIO_S16SYS;
    wanted.channels = UTOPIA_RECOMP_AUDIO_CHANNELS;
    wanted.samples  = 512;
    wanted.callback = NULL;
    g_audio_dev = SDL_OpenAudioDevice(NULL, 0, &wanted, &gotten, 0);
    if (g_audio_dev == 0) {
        fprintf(stderr, "Warning: could not open audio device: %s\n",
                SDL_GetError());
        return;
    }
    SDL_PauseAudioDevice(g_audio_dev, 0);
}

static void drain_audio(void) {
    if (!g_audio_dev || !g_game) return;
    int16_t buffer[8192];
    size_t avail = utopia_recomp_audio_available(g_game);
    size_t to_drain = avail < 4096u ? avail : 4096u;
    size_t n = utopia_recomp_audio_read(g_game, buffer, to_drain);
    if (n > 0) SDL_QueueAudio(g_audio_dev, buffer, (uint32_t)(n * 2u));
}

static void render_frame(void) {
    if (!g_game || !g_renderer) return;
    const uint32_t *pixels = utopia_recomp_frame_bgra(g_game);
    if (!pixels) return;
    uint32_t w = utopia_recomp_frame_width(g_game);
    SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormat(0, (int)w,
                                                       UTOPIA_RECOMP_FRAME_HEIGHT,
                                                       32,
                                                       SDL_PIXELFORMAT_ARGB8888);
    if (!surf) return;
    memcpy(surf->pixels, pixels, (size_t)w * UTOPIA_RECOMP_FRAME_HEIGHT * sizeof(uint32_t));
    SDL_Texture *tex = SDL_CreateTextureFromSurface(g_renderer, surf);
    SDL_FreeSurface(surf);
    if (!tex) return;
    SDL_Rect dst = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderClear(g_renderer);
    SDL_RenderCopy(g_renderer, tex, NULL, &dst);
    SDL_RenderPresent(g_renderer);
    SDL_DestroyTexture(tex);
}

static int load_rom(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) {
        fprintf(stderr, "Cannot open ROM: %s\n", path);
        return 0;
    }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    uint8_t *rom = (uint8_t *)malloc((size_t)size);
    if (!rom) { fclose(f); return 0; }
    size_t rd = fread(rom, 1, (size_t)size, f);
    fclose(f);
    if ((long)rd != size) { free(rom); return 0; }
    char err[256];
    if (!utopia_recomp_create(&g_game, rom, (size_t)size, err, sizeof(err))) {
        fprintf(stderr, "Failed to create recomp instance: %s\n", err);
        free(rom);
        return 0;
    }
    free(rom);
    return 1;
}

static void handle_input(uint16_t *mask) {
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        switch (ev.type) {
            case SDL_QUIT:          quit(0); return;
            case SDL_KEYDOWN:
                switch (ev.key.keysym.sym) {
                    case SDLK_ESCAPE: quit(0); return;
                    case SDLK_F1:    /* settings menu placeholder */ break;
                    case SDLK_z: *mask |= UTOPIA_INPUT_B; break;
                    case SDLK_x: *mask |= UTOPIA_INPUT_A; break;
                    case SDLK_a: *mask |= UTOPIA_INPUT_L; break;
                    case SDLK_s: *mask |= UTOPIA_INPUT_R; break;
                    case SDLK_RETURN: *mask |= UTOPIA_INPUT_START; break;
                    case SDLK_BACKSPACE: *mask |= UTOPIA_INPUT_SELECT; break;
                    case SDLK_q: *mask |= UTOPIA_INPUT_Y; break;
                    case SDLK_UP:    *mask |= UTOPIA_INPUT_UP; break;
                    case SDLK_DOWN:  *mask |= UTOPIA_INPUT_DOWN; break;
                    case SDLK_LEFT:  *mask |= UTOPIA_INPUT_LEFT; break;
                    case SDLK_RIGHT: *mask |= UTOPIA_INPUT_RIGHT; break;
                }
                break;
            case SDL_KEYUP:
                switch (ev.key.keysym.sym) {
                    case SDLK_z:          *mask &= ~UTOPIA_INPUT_B; break;
                    case SDLK_x:          *mask &= ~UTOPIA_INPUT_A; break;
                    case SDLK_a:          *mask &= ~UTOPIA_INPUT_L; break;
                    case SDLK_s:          *mask &= ~UTOPIA_INPUT_R; break;
                    case SDLK_RETURN:     *mask &= ~UTOPIA_INPUT_START; break;
                    case SDLK_BACKSPACE:  *mask &= ~UTOPIA_INPUT_SELECT; break;
                    case SDLK_q:          *mask &= ~UTOPIA_INPUT_Y; break;
                    case SDLK_UP:         *mask &= ~UTOPIA_INPUT_UP; break;
                    case SDLK_DOWN:       *mask &= ~UTOPIA_INPUT_DOWN; break;
                    case SDLK_LEFT:       *mask &= ~UTOPIA_INPUT_LEFT; break;
                    case SDLK_RIGHT:      *mask &= ~UTOPIA_INPUT_RIGHT; break;
                }
                break;
        }
    }
}

int main(int argc, char **argv) {
    const char *rom_path = NULL;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--rom") == 0 && i + 1 < argc) {
            rom_path = argv[++i];
        } else if (argv[i][0] == '-') {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
        }
    }
    if (!rom_path) {
        /* Try environment variable */
        rom_path = getenv("UTOPIA_ROM_PATH");
    }
    if (!rom_path) {
        fprintf(stderr, "Usage: %s --rom <path/to/Utopia.sfc>\n", argv[0]);
        return 1;
    }
    strncpy(g_rom_path, rom_path, sizeof(g_rom_path) - 1);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL2 init failed: %s\n", SDL_GetError());
        return 1;
    }

    g_window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                          WINDOW_WIDTH, WINDOW_HEIGHT,
                          SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!g_window) {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    g_renderer = SDL_CreateRenderer(g_window, -1,
                                     SDL_RENDERER_ACCELERATED |
                                     SDL_RENDERER_PRESENTVSYNC);
    if (!g_renderer) {
        g_renderer = SDL_CreateRenderer(g_window, -1,
                                         SDL_RENDERER_SOFTWARE);
    }
    if (!g_renderer) {
        fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(g_window);
        SDL_Quit();
        return 1;
    }

    if (!load_rom(rom_path)) {
        fprintf(stderr, "Failed to load ROM.\n");
        SDL_DestroyRenderer(g_renderer);
        SDL_DestroyWindow(g_window);
        SDL_Quit();
        return 1;
    }

    init_audio();

    uint16_t input_mask = 0u;
    while (g_running) {
        handle_input(&input_mask);
        if (!g_running) break;

        UtopiaRecompFrameResult result;
        if (!utopia_recomp_advance(g_game, input_mask, 1, &result)) {
            fprintf(stderr, "Route failed: %s\n", utopia_recomp_last_error(g_game));
            break;
        }
        if (result.frame_rendered) {
            drain_audio();
            render_frame();
        }
    }

    if (g_audio_dev) SDL_CloseAudioDevice(g_audio_dev);
    if (g_game) utopia_recomp_destroy(g_game);
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    SDL_Quit();
    return 0;
}