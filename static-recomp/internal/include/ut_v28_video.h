#ifndef UT_V28_VIDEO_H
#define UT_V28_VIDEO_H

#include <stddef.h>
#include <stdint.h>

typedef struct SCV11Runtime SCV11Runtime;

typedef struct SCV28VideoReport SCV28VideoReport;

struct SCV28VideoReport {
    char error[192];
    uint32_t scanline_count;
    uint32_t mode;
};

int sc_v28_render_first_visible_frame(
    const SCV11Runtime *runtime,
    unsigned width, unsigned margin,
    uint16_t *bgr555_out, size_t bgr555_capacity,
    uint32_t *bgra_out, size_t bgra_capacity,
    SCV28VideoReport *report);

#endif