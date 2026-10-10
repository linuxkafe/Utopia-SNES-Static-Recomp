#ifndef UT_V11_CPU_H
#define UT_V11_CPU_H

#include "ut_v11_runtime.h"

/* W65C816 CPU step — main dispatch entry point */
int sc_v11_cpu_step(SCV11Runtime *runtime);

/* Bootstrap dispatch (called during initial boot sequence) */
int sc_v11_bootstrap_step(SCV11Runtime *runtime);

/* Initialize the CPU dispatch table */
void ut_cpu_dispatch_init(void);

#endif