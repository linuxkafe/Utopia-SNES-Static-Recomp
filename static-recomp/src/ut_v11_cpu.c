#include "ut_v11_cpu.h"
#include "ut_v11_runtime.h"
#include "ut_v11_bus.h"
#include <stdio.h>

/* W65C816 CPU step — placeholder stub.
   Real implementation will dispatch generated switch-case code
   keyed by the current PC context. */

int sc_v11_cpu_step(SCV11Runtime *runtime) {
    if (!runtime || runtime->route_failed) return 0;
    /* For the skeleton build, advance past the stub and return success.
       The generated dispatch will replace this function. */
    runtime->scheduler.cpu_instructions++;
    runtime->scheduler.master_clock += 6u; /* approximate: 6 cycles per NOP */
    return 1;
}

int sc_v11_bootstrap_step(SCV11Runtime *runtime) {
    return sc_v11_cpu_step(runtime);
}