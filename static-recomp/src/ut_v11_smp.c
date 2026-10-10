#include "ut_v11_smp.h"
#include "ut_v11_runtime.h"

/* S-SMP step — placeholder stub.
   The real implementation uses the static AOT authority to dispatch
   SPC700 instructions. */

int sc_v11_smp_step(SCV11Runtime *runtime) {
    if (!runtime || runtime->route_failed) return 0;
    /* No-op for skeleton build. */
    (void)runtime;
    return 1;
}