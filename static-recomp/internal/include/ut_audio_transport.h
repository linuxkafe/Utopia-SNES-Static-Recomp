#ifndef UT_AUDIO_TRANSPORT_H
#define UT_AUDIO_TRANSPORT_H

#include <stddef.h>
#include <stdint.h>

typedef struct SCAudioTransportState SCAudioTransportState;

struct SCAudioTransportState {
    uint8_t ready_observed;
    uint8_t upload_handshake_started;
    uint8_t upload_complete;
    uint8_t upload_verified;
    uint16_t entrypoint;
    uint32_t upload_block_count;
    uint32_t upload_write_count;
    uint32_t upload_unique_byte_count;
    uint32_t upload_overlap_writes;
    uint32_t upload_verify_mismatches;
    uint32_t generated_scpu_apu_sites;
    uint32_t observed_scpu_apu_sites;
    uint32_t unmanifested_scpu_apu_accesses;
    uint32_t post_upload_scpu_reads;
    uint32_t post_upload_scpu_writes;
    char upload_image_sha256[65];
    char upload_mask_sha256[65];
    char scpu_apu_manifest_sha256[65];
};

int ut_audio_transport_acquire(char *error, size_t error_capacity);
void ut_audio_transport_release(void);
const SCAudioTransportState *ut_audio_transport_state(void);
size_t ut_audio_transport_snapshot_size(void);
int ut_audio_transport_snapshot_save(void *buf, size_t size);
int ut_audio_transport_snapshot_load(const void *buf, size_t size,
                                     char *error, size_t error_capacity);

#endif