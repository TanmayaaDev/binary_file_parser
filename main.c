#include <stdio.h>
#include <stdlib.h>
#include "binary_parser.h"

int main() {
    printf("=========================================\n");
    printf("   LOW-LEVEL BINARY FILE PARSER ENGINE   \n");
    printf("=========================================\n\n");

    const char *filename = "database_store.vdb";
    float sample_dataset[] = {10.5f, 20.25f, 30.125f, 40.0f, 50.875f};
    uint32_t sample_count = 5;

    // 1. Serialize binary format to disk
    printf("[1] Serializing %u float records to '%s'...\n", sample_count, filename);
    if (write_binary_file(filename, sample_dataset, sample_count) == 0) {
        printf("    -> Successfully written to disk with header & checksum!\n\n");
    }

    // 2. Read and parse binary format back into dynamic array
    printf("[2] Parsing and deserializing binary file '%s'...\n", filename);
    float *parsed_data = NULL;
    uint32_t parsed_count = 0;

    if (read_binary_file(filename, &parsed_data, &parsed_count) == 0) {
        printf("    -> Header validated! Successfully restored %u records:\n       [ ", parsed_count);
        for (uint32_t i = 0; i < parsed_count; i++) {
            printf("%.3f ", parsed_data[i]);
        }
        printf("]\n\n");
        free(parsed_data);
    }

    printf("Binary Parser test completed cleanly!\n");
    return 0;
}