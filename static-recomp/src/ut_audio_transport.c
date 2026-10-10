#include "ut_audio_transport.h"
#include <string.h>
#include <stdio.h>

static SCAudioTransportState g_state;
static int g_acquired = 0;

int ut_audio_transport_acquire(char *error, size_t error_capacity) {
    (void)error; (void)error_capacity;
    g_acquired = 1;
    memset(&g_state, 0, sizeof(g_state));
    return 1;
}

void ut_audio_transport_release(void) {
    g_acquired = 0;
    memset(&g_state, 0, sizeof(g_state));
}

const SCAudioTransportState *ut_audio_transport_state(void) {
    return g_acquired ? &g_state : NULL;
}

size_t ut_audio_transport_snapshot_size(void) {
    return sizeof(g_state);
}

int ut_audio_transport_snapshot_save(void *buf, size_t size) {
    if (!buf || size < sizeof(g_state)) return 0;
    memcpy(buf, &g_state, sizeof(g_state));
    return 1;
}

int ut_audio_transport_snapshot_load(const void *buf, size_t size,
                                     char *error, size_t error_capacity)
{
    if (!buf || size < sizeof(g_state)) {
        snprintf(error, error_capacity, "Audio transport snapshot too small.");
        return 0;
    }
    memcpy(&g_state, buf, sizeof(g_state));
    return 1;
}