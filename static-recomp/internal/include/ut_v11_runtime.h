#ifndef UT_V11_RUNTIME_H
#define UT_V11_RUNTIME_H

#include <stddef.h>
#include <stdint.h>

#define SC_MMIO_BASE 0x4020u
#define SC_V11_SRAM_SIZE 32768u

/* W65C816 CPU state */
typedef struct {
    uint8_t  a;       /* Accumulator */
    uint8_t  x;       /* X register (low byte of 16-bit X) */
    uint8_t  y;       /* Y register (low byte of 16-bit Y) */
    uint16_t pc;      /* Program counter */
    uint16_t sp;      /* Stack pointer (65xx uses 0x0100-0x01FF) */
    uint8_t  p;       /* Processor status (S D B I H N V Z C) */
    uint8_t  bank;    /* Overlay bank register */
    uint8_t  status;  /* Full 8-bit status for emulation (N V - B D I Z C) */
} UT_CPU;

/* Runtime version: the V11 dispatch path is the current stable path. */
typedef struct SCV11Runtime SCV11Runtime;

struct SCV11Runtime {
    /* Machine state */
    struct {
        uint8_t wram[0x2000];
        uint8_t mmio[0x100];
        uint8_t controller_history[0x1000];
        uint16_t joypad[2];
        uint8_t *rom;
        size_t   rom_size;
        UT_CPU   cpu;
    } machine;

    /* Scheduler */
    struct {
        uint32_t frame;
        uint64_t cpu_instructions;
        uint64_t master_clock;
    } scheduler;

    /* Route state */
    uint8_t  route_failed;
    char     route_error[192];

    /* Audio sink callback */
    void (*audio_sink)(void *ctx, int16_t left, int16_t right);
    void *audio_sink_context;

    /* Host-wide features */
    uint8_t host_widescreen_enabled;

    /* Audio transport (S-SMP upload) */
    struct {
        uint32_t observed_access_site_mask;
    } audio_transport;

    /* SRAM */
    uint8_t sram[SC_V11_SRAM_SIZE];
    uint8_t sram_dirty;

    /* Input history for snapshots */
    uint16_t *input_history;
    uint32_t  input_history_count;
    uint32_t  input_history_capacity;
};

/* Called by utopia_static_recomp.c during instance creation. */
void sc_v11_runtime_init(SCV11Runtime *runtime, const uint8_t *rom, size_t rom_size);
void sc_v11_set_audio_sink(SCV11Runtime *runtime,
                           void (*sink)(void*, int16_t, int16_t),
                           void *context);
int  sc_v11_step(SCV11Runtime *runtime);
int  sc_v11_fail(SCV11Runtime *runtime, uint32_t address, const char *reason);

#endif