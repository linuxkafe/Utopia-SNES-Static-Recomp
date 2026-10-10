/* Placeholder static dispatch. */
#include "ut_v11_runtime.h"
#include "ut_v11_cpu.h"

int sc_v11_static_step(SCV11Runtime *runtime) {
    return sc_v11_cpu_step(runtime);
}