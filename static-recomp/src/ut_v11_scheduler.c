#include "ut_v11_scheduler.h"
#include "ut_v11_runtime.h"

/* NTSC timing constants for the Utopia ROM. */

uint32_t sc_v11_ntsc_scanlines(void) {
    return 262u;
}

uint32_t sc_v11_average_master_clocks_per_frame(void) {
    return 357366u;
}

int sc_v11_smp_sync_to_master(SCV11Runtime *runtime, uint64_t master_clock) {
    if (!runtime) return 0;
    (void)master_clock;
    /* Placeholder: real S-SMP sync will align audio state to the master clock. */
    return 1;
}