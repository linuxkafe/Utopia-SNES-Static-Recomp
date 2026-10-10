#include "ut_v28_video.h"
#include "ut_v11_runtime.h"
#include <string.h>
#include <stdio.h>

/* PPU renderer stub.
   Real implementation will translate SNES PPU registers into host
   framebuffer pixels, handling all supported rendering modes. */

int sc_v28_render_first_visible_frame(
    const SCV11Runtime *runtime,
    unsigned width, unsigned margin,
    uint16_t *bgr555_out, size_t bgr555_capacity,
    uint32_t *bgra_out, size_t bgra_capacity,
    SCV28VideoReport *report)
{
    if (!report) return 0;
    memset(report, 0, sizeof(*report));

    if (!runtime || !bgr555_out || !bgra_out ||
        bgr555_capacity < width || bgra_capacity < width) {
        snprintf(report->error, sizeof(report->error),
                 "Invalid render parameters.");
        return 0;
    }

    /* Clear the scanline to black. */
    for (unsigned x = 0u; x < width; ++x) {
        bgr555_out[x] = 0x0000u;
        bgra_out[x]   = 0xFF000000u;
    }
    report->scanline_count = 1u;
    report->mode = 0u;
    return 1;
}