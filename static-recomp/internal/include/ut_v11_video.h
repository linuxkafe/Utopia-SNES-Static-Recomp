#ifndef UT_V11_VIDEO_H
#define UT_V11_VIDEO_H

#include <stdint.h>
#include "ut_v11_runtime.h"

uint8_t ut_v11_ppu_mode(const SCV11Runtime *runtime);
uint8_t ut_v11_ppu_is_large_mode(const SCV11Runtime *runtime);

#endif