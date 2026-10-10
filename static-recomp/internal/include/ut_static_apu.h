#ifndef UT_STATIC_APU_H
#define UT_STATIC_APU_H

#include <stddef.h>
#include "ut_audio_transport.h"
#include "ut_audio_clock_profile.h"

typedef struct SCStaticApuStatus SCStaticApuStatus;

struct SCStaticApuStatus {
    uint8_t current_epoch;
    uint8_t aot_failed;
    uint16_t smp_pc;
    uint32_t aot_fail_reason;
    uint32_t code_write_barriers;
    uint64_t aot_validated_instructions;
    uint64_t pcm_frames;
    uint64_t pcm_known_frames;
    uint64_t pcm_unknown_frames;
    uint64_t pcm_hash;
    uint64_t pcm_overflows;
};

int sc_static_apu_acquire(char *error, size_t error_capacity);
void sc_static_apu_release(void);
int sc_static_apu_status(SCStaticApuStatus *status);
size_t sc_static_apu_snapshot_size(void);
int sc_static_apu_snapshot_save(void *buf, size_t size);
int sc_static_apu_snapshot_load(const void *buf, size_t size,
                                char *error, size_t error_capacity);

#endif