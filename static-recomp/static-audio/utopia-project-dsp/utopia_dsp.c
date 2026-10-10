/* Utopia-owned fixed 32-phase SNES S-DSP hardware model.
 * Minimal stub for build compatibility. */
#include <stdint.h>
#include <string.h>
#include "utopia/utopia_dsp.h"

void utopia_dsp_power_on(utopia_dsp *dsp, uint8_t *aram, uint8_t *aram_known) {
    if (!dsp) return;
    memset(dsp, 0, sizeof(*dsp));
    dsp->aram = aram;
    dsp->aram_known = aram_known;
}

uint32_t utopia_dsp_write_register(utopia_dsp *dsp, uint8_t reg, uint8_t value) {
    (void)dsp; (void)reg; (void)value;
    return 0;
}

uint32_t utopia_dsp_read_register(utopia_dsp *dsp, uint8_t reg, uint8_t *value) {
    (void)dsp; (void)reg; (void)value;
    return 0;
}

uint32_t utopia_dsp_step_phase(utopia_dsp *dsp) {
    (void)dsp;
    return 0;
}

uint32_t utopia_dsp_step_smp_cycles(utopia_dsp *dsp, uint32_t cycles) {
    (void)dsp; (void)cycles;
    return 0;
}

uint32_t utopia_dsp_step_sample(utopia_dsp *dsp) {
    (void)dsp;
    return 0;
}

int utopia_dsp_register_known(const utopia_dsp *dsp, uint8_t reg) {
    (void)dsp; (void)reg;
    return 0;
}

size_t utopia_dsp_pcm_available(const utopia_dsp *dsp) {
    (void)dsp;
    return 0;
}

size_t utopia_dsp_pcm_read(utopia_dsp *dsp, int16_t *stereo_frames, size_t capacity_frames) {
    (void)dsp; (void)stereo_frames; (void)capacity_frames;
    return 0;
}

size_t utopia_dsp_pcm_read_with_knownness(utopia_dsp *dsp, int16_t *stereo_frames, uint8_t *frame_known, size_t capacity_frames) {
    (void)dsp; (void)stereo_frames; (void)frame_known; (void)capacity_frames;
    return 0;
}

uint64_t utopia_dsp_pcm_hash(const utopia_dsp *dsp) {
    (void)dsp;
    return 0;
}

uint8_t utopia_dsp_phase(const utopia_dsp *dsp) {
    (void)dsp;
    return 0;
}