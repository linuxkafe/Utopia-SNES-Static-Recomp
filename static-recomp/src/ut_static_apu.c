#include "ut_static_apu.h"
#include <string.h>
#include <stdio.h>

static SCStaticApuStatus g_status;
static int g_acquired = 0;

int sc_static_apu_acquire(char *error, size_t error_capacity) {
    (void)error; (void)error_capacity;
    g_acquired = 1;
    memset(&g_status, 0, sizeof(g_status));
    return 1;
}

void sc_static_apu_release(void) {
    g_acquired = 0;
    memset(&g_status, 0, sizeof(g_status));
}

int sc_static_apu_status(SCStaticApuStatus *status) {
    if (!status || !g_acquired) return 0;
    memcpy(status, &g_status, sizeof(g_status));
    return 1;
}

size_t sc_static_apu_snapshot_size(void) {
    return sizeof(g_status);
}

int sc_static_apu_snapshot_save(void *buf, size_t size) {
    if (!buf || size < sizeof(g_status)) return 0;
    memcpy(buf, &g_status, sizeof(g_status));
    return 1;
}

int sc_static_apu_snapshot_load(const void *buf, size_t size,
                                char *error, size_t error_capacity)
{
    if (!buf || size < sizeof(g_status)) {
        snprintf(error, error_capacity, "Snapshot buffer too small.");
        return 0;
    }
    memcpy(&g_status, buf, sizeof(g_status));
    return 1;
}