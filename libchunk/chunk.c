//
// Created by vik on 6/24/25.
//
#include "chunk.h"
#include <stdio.h>
#include <stdlib.h>

void free_chunk(chunk_t chunk, const Vector3_t size) {
    for (int x = 0; x < size.x; x++) {
        for (int y = 0; y < size.y; y++) {
            free(chunk[x][y]);
        }
        free(chunk[x]);
    }
    free(chunk);
}
chunk_t allocate_chunk(const Vector3_t size) {
    chunk_t chunk = malloc(size.x * sizeof *chunk);
    for (int x = 0; x < size.x; x++) {
        chunk[x] = malloc(size.y * sizeof **chunk);
        for (int y = 0; y < size.y; y++) {
            chunk[x][y] = malloc(size.z * sizeof ***chunk);
        }
    }
    return chunk;
}
