#ifndef UT_BOOTSTRAP_DISPATCH_H
#define UT_BOOTSTRAP_DISPATCH_H

#include "ut_v11_runtime.h"

/* Bootstrap dispatch — handles the first ~50 instructions after reset */
int ut_bootstrap_step(SCV11Runtime *runtime);

/* Read a byte from ROM at the given address */
uint8_t rom_read(const SCV11Runtime *r, uint16_t addr);

#endif