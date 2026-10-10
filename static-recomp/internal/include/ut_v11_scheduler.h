#ifndef UT_V11_SCHEDULER_H
#define UT_V11_SCHEDULER_H

#include "ut_v11_runtime.h"

int sc_v11_smp_sync_to_master(SCV11Runtime *runtime, uint64_t master_clock);
uint32_t sc_v11_ntsc_scanlines(void);
uint32_t sc_v11_average_master_clocks_per_frame(void);

#endif