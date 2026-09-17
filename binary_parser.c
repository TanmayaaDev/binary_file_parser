#include <stdio.h>
#include <stdlib.h>
#include "binary_parser.h"

// Calculate basic additive checksum over float payload
static uint32_t calculate_checksum(const float *data, uint32_t count) {
    uint32_t sum = 0;
    const uint8_t *byte_ptr = (const uint8_t*)data;
    size_t total_bytes = count * sizeof(float);
    
    for (size_t i = 0; i < total_bytes; i++) {
        sum += byte_ptr[i];
    }
    return sum;
}

int write_binary_file(const char *filename, const float *data, uint32_t count) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file for writing");
        return -1;
    }

    FileHeader header;
    header.magic = MAGIC_BYTES;
    header.version = 1;
    header.num_records = count;
    header.checksum = calculate_checksum(data, count);

    // Write Header
    if (fwrite(&header, sizeof(FileHeader), 1, file) != 1) {
        perror("Failed to write binary header");
        fclose(file);
        return -1;
    }

    // Write Raw Float Payload
    if (fwrite(data, sizeof(float), count, file) != count) {
        perror("Failed to write float data payload");
        fclose(file);
        return -1;
    }

    fclose(file);
    return 0;
}

int read_binary_file(const char *filename, float **out_data, uint32_t *out_count) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening binary file for reading");
        return -1;
    }

    FileHeader header;
    if (fread(&header, sizeof(FileHeader), 1, file) != 1) {
        perror("Failed to read header");
        fclose(file);
        return -1;
    }

    // Header Validation: Magic Bytes Check
    if (header.magic != MAGIC_BYTES) {
        fprintf(stderr, "Error: Invalid magic bytes (0x%X). Not a valid .vdb file!\n", header.magic);
        fclose(file);
        return -1;
    }

    // Allocate memory for dynamic payload
    float *data = (float*)malloc(header.num_records * sizeof(float));
    if (!data) {
        perror("Memory allocation failed");
        fclose(file);
        return -1;
    }

    if (fread(data, sizeof(float), header.num_records, file) != header.num_records) {
        perror("Failed to read binary float payload");
        free(data);
        fclose(file);
        return -1;
    }

    fclose(file);

    // Validate Checksum Integrity
    uint32_t computed_checksum = calculate_checksum(data, header.num_records);
    if (computed_checksum != header.checksum) {
        fprintf(stderr, "Error: Data corruption detected! Checksum mismatch.\n");
        free(data);
        return -1;
    }

    *out_data = data;
    *out_count = header.num_records;
    return 0;
}