#ifndef UT_V11_BUS_H
#define UT_V11_BUS_H

#include "ut_v11_runtime.h"

uint8_t sc_v11_bus_read(const SCV11Runtime *runtime, uint16_t addr, uint8_t bank);
void sc_v11_bus_write(SCV11Runtime *runtime, uint16_t addr, uint8_t value, uint8_t bank);

#endif