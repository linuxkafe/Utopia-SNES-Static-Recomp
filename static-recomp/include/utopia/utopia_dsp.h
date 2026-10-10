#ifndef UTOPIA_DSP_H
#define UTOPIA_DSP_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define UTOPIA_DSP_VOICES 8u
#define UTOPIA_DSP_REG_COUNT 128u
#define UTOPIA_DSP_PHASES 32u
#define UTOPIA_DSP_PCM_FIFO_FRAMES 8192u

typedef enum utopia_dsp_envelope_mode {
    UTOPIA_DSP_ENV_RELEASE = 0,
    UTOPIA_DSP_ENV_ATTACK = 1,
    UTOPIA_DSP_ENV_DECAY = 2,
    UTOPIA_DSP_ENV_SUSTAIN = 3
} utopia_dsp_envelope_mode;

typedef enum {
    UTOPIA_DSP_STOP_NONE = 0,
    UTOPIA_DSP_STOP_INVALID_ARGUMENT = 5200,
    UTOPIA_DSP_STOP_REGISTER_UNKNOWN = 5201,
    UTOPIA_DSP_STOP_ARAM_REQUIRED_UNKNOWN = 5202,
    UTOPIA_DSP_STOP_PCM_FIFO_OVERFLOW = 5203,
    UTOPIA_DSP_STOP_PHASE_INVARIANT = 5204
} utopia_dsp_stop_reason;

typedef struct utopia_dsp_voice {
    int32_t envelope;
    int32_t previous_calculated_envelope;
    uint32_t interpolation_position;
    uint16_t brr_address;
    uint16_t brr_offset;
    uint8_t envelope_mode;
    uint8_t key_on_delay;
    uint8_t env_out;
    uint8_t buffer_pos;
    int16_t sample_buffer[12];
    int16_t output;
    uint8_t active;
    uint64_t brr_groups_decoded;
} utopia_dsp_voice;

typedef struct utopia_dsp {
    uint8_t *aram;
    uint8_t *aram_known;
    uint8_t regs[UTOPIA_DSP_REG_COUNT];
    uint8_t reg_known[UTOPIA_DSP_REG_COUNT / 8u];
    utopia_dsp_voice voices[UTOPIA_DSP_VOICES];

    uint8_t phase;
    uint16_t counter;
    uint16_t noise_lfsr;
    uint8_t out_reg_buffer;
    uint8_t env_reg_buffer;
    uint8_t voice_end_buffer;
    int32_t voice_output;
    int32_t out_samples[2];
    uint8_t out_samples_known[2];
    uint16_t pitch;
    uint16_t sample_address;
    uint16_t brr_next_address;
    uint8_t brr_next_known;
    uint8_t dir_latch;
    uint8_t noise_on_latch;
    uint8_t pmon_latch;
    uint8_t key_on;
    uint8_t new_key_on;
    uint8_t key_off;
    uint8_t every_other_sample;
    uint8_t source_number;
    uint8_t brr_header;
    uint8_t brr_header_known;
    uint8_t brr_data;
    uint8_t brr_data_known;
    uint8_t looped;
    uint8_t adsr1;

    int32_t echo_in[2];
    int32_t echo_out[2];
    uint8_t echo_out_known[2];
    int16_t echo_history[8][2];
    uint8_t echo_history_known[8][2];
    uint16_t echo_pointer;
    uint16_t echo_length;
    uint16_t echo_offset;
    uint8_t echo_history_pos;
    uint8_t esa_latch;
    uint8_t echo_on_latch;
    uint8_t echo_enabled_latch;

    int16_t pcm_fifo[UTOPIA_DSP_PCM_FIFO_FRAMES * 2u];
    uint8_t pcm_known_fifo[UTOPIA_DSP_PCM_FIFO_FRAMES];
    size_t pcm_read_index;
    size_t pcm_write_index;
    size_t pcm_count;
    uint64_t pcm_frames_produced;
    uint64_t pcm_known_frames_produced;
    uint64_t pcm_unknown_frames_produced;
    uint64_t pcm_overflows;
    uint64_t pcm_fnv1a64;

    uint64_t phase_steps;
    uint64_t sample_steps;
    uint64_t register_writes;
    uint64_t register_reads;
    uint64_t aram_reads;
    uint64_t aram_known_reads;
    uint64_t aram_unknown_reads;
    uint64_t aram_writes;
    uint64_t key_on_events;
    uint64_t key_off_events;
    uint8_t last_aram_phase;
    uint16_t last_aram_address;
    uint8_t last_aram_known;
    uint8_t last_latched_reg;
    uint8_t last_latch_phase;
    utopia_dsp_stop_reason last_stop;
} utopia_dsp;

void utopia_dsp_power_on(utopia_dsp *dsp, uint8_t *aram, uint8_t *aram_known);
utopia_dsp_stop_reason utopia_dsp_write_register(utopia_dsp *dsp, uint8_t reg, uint8_t value);
utopia_dsp_stop_reason utopia_dsp_read_register(utopia_dsp *dsp, uint8_t reg, uint8_t *value);
utopia_dsp_stop_reason utopia_dsp_step_phase(utopia_dsp *dsp);
utopia_dsp_stop_reason utopia_dsp_step_smp_cycles(utopia_dsp *dsp, uint32_t cycles);
utopia_dsp_stop_reason utopia_dsp_step_sample(utopia_dsp *dsp);
int utopia_dsp_register_known(const utopia_dsp *dsp, uint8_t reg);
size_t utopia_dsp_pcm_available(const utopia_dsp *dsp);
size_t utopia_dsp_pcm_read(utopia_dsp *dsp, int16_t *stereo_frames, size_t capacity_frames);
size_t utopia_dsp_pcm_read_with_knownness(utopia_dsp *dsp, int16_t *stereo_frames, uint8_t *frame_known, size_t capacity_frames);
uint64_t utopia_dsp_pcm_hash(const utopia_dsp *dsp);
uint8_t utopia_dsp_phase(const utopia_dsp *dsp);

#ifdef __cplusplus
}
#endif

#endif