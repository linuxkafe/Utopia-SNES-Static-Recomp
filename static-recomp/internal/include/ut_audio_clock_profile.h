#ifndef UT_AUDIO_CLOCK_PROFILE_H
#define UT_AUDIO_CLOCK_PROFILE_H
#include <stdint.h>
#define UT_AUDIO_CLOCK_PROFILE_NAME "ntsc-measured-32040"
#define UT_AUDIO_CLOCK_RATIO_NUMERATOR UINT32_C(15664)
#define UT_AUDIO_CLOCK_RATIO_DENOMINATOR UINT32_C(328125)
#define UT_AUDIO_CLOCK_MASTER_HZ UINT32_C(21477270)
static inline uint32_t ut_audio_master_delta_to_smp_cycles(uint64_t master_delta, uint32_t *remainder) {
    const uint64_t whole = master_delta / UT_AUDIO_CLOCK_RATIO_DENOMINATOR;
    const uint64_t partial = master_delta % UT_AUDIO_CLOCK_RATIO_DENOMINATOR;
    const uint64_t numerator = partial * UT_AUDIO_CLOCK_RATIO_NUMERATOR + *remainder * UT_AUDIO_CLOCK_RATIO_NUMERATOR;
    const uint64_t cycles = whole * UT_AUDIO_CLOCK_RATIO_NUMERATOR + numerator / UT_AUDIO_CLOCK_RATIO_DENOMINATOR;
    *remainder = (uint32_t)(numerator % UT_AUDIO_CLOCK_RATIO_DENOMINATOR);
    return (uint32_t)cycles;
}
static inline uint32_t ut_audio_master_delta_to_smp_cycles_simple(uint64_t master_delta) {
    uint32_t dummy_remainder = 0;
    return ut_audio_master_delta_to_smp_cycles(master_delta, &dummy_remainder);
}
static inline uint32_t ut_audio_master_to_smp_phase(uint64_t master_clock, uint32_t initial_remainder) {
    const uint64_t partial = master_clock % UT_AUDIO_CLOCK_RATIO_DENOMINATOR;
    return (uint32_t)((partial * UT_AUDIO_CLOCK_RATIO_NUMERATOR) % UT_AUDIO_CLOCK_RATIO_DENOMINATOR);
}
static inline uint64_t ut_audio_master_to_smp_cycles(uint64_t master_clock, uint32_t initial_remainder) {
    const uint64_t whole = master_clock / UT_AUDIO_CLOCK_RATIO_DENOMINATOR;
    const uint64_t partial = master_clock % UT_AUDIO_CLOCK_RATIO_DENOMINATOR;
    return whole * UT_AUDIO_CLOCK_RATIO_NUMERATOR + (partial * UT_AUDIO_CLOCK_RATIO_NUMERATOR + initial_remainder) / UT_AUDIO_CLOCK_RATIO_DENOMINATOR;
}
#endif