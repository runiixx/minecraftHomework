//
// Created by vik on 6/24/25.
//
#include "chunk.h"
#include <stdio.h>
#include <stdlib.h>

void print_chunk(chunk_t chunk, int width, int height, int depth) {
    printf("Chunk: width-%d, height-%d, depth-%d", width, height, depth);
    for (int x  = 0; x < width; x++) {
        for (int y  = 0; y < height; y++) {
            for (int z  = 0; z < depth; z++) {
                printf("%d ",chunk[x][y][z]);
            }
            printf("\n");
        }
        printf("\n");
    }

}

chunk_t read_chunk(int *width, int *height, int *depth) {
    scanf("%d%d%d", width, height, depth);

    chunk_t chunk = malloc(*width * sizeof *chunk);

    for (int x = 0; x < *width; x++) {
        chunk[x] = malloc(*height * sizeof **chunk);
        for (int y = *height-1; y >= 0; y--) {
            chunk[x][y] = malloc(*depth * sizeof ***chunk);

            for (int z = 0; z < *depth; z++)
                scanf("%hhd", &chunk[x][y][z]);
        }
    }

    return chunk;
}