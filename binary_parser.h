#ifndef BINARY_PARSER_H
#define BINARY_PARSER_H

#include <stdint.h>
#include <stddef.h>

#define MAGIC_BYTES 0x56444231 // ASCII "VDB1"

// 16-Byte Packed Binary Header
typedef struct __attribute__((packed)) {
    uint32_t magic;       // Must equal MAGIC_BYTES
    uint32_t version;     // Format version (e.g., 1)
    uint32_t num_records; // Total floating-point entries stored
    uint32_t checksum;    // Simple additive checksum validation
} FileHeader;

// Function Contracts
int write_binary_file(const char *filename, const float *data, uint32_t count);
int read_binary_file(const char *filename, float **out_data, uint32_t *out_count);

#endif