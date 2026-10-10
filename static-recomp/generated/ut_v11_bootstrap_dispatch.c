/* Placeholder generated dispatch files.
   These are stubs that allow the project to compile.
   The real generated code is produced by the generation scripts
   (not yet implemented). */

#include "ut_v11_runtime.h"
#include "ut_v11_cpu.h"

/* v11 bootstrap dispatch — power-on entry point. */
int sc_v11_bootstrap_step(SCV11Runtime *runtime) {
    return sc_v11_cpu_step(runtime);
}

/* v11 CPU dispatch index (entry points for each PC page). */
typedef int (*DispatchFunc)(SCV11Runtime *);

static DispatchFunc g_cpu_dispatch_table[256] = {0};

void utopia_generate_dispatch_table(void) {
    for (int i = 0; i < 256; ++i) {
        g_cpu_dispatch_table[i] = sc_v11_cpu_step;
    }
}