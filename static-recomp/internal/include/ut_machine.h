#ifndef UT_MACHINE_H
#define UT_MACHINE_H

#include <stddef.h>
#include <stdint.h>
#include "ut_v11_runtime.h"

uint16_t ut_machine_read_wram16(const SCV11Runtime *runtime, size_t offset);
void ut_machine_write_wram16(SCV11Runtime *runtime, size_t offset, uint16_t value);

#endif