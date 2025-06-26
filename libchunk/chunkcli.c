//
// Created by vik on 6/24/25.
//
#include "chunkcli.h"
#include "chunk.h"
#include <stdio.h>
#include <stdlib.h>
chunk_t read_chunk_file(int *width, int *height, int *depth) {
    FILE *file = fopen("Chunks/1.in", "r");
    if (file == NULL) return NULL;
    fscanf(file,"%d%d%d", width, height, depth);


    chunk_t chunk = malloc(*width * sizeof *chunk);

    for (int x = 0; x < *width; x++) {
        chunk[x] = malloc(*height * sizeof **chunk);
        for (int y = *height-1; y >= 0; y--) {
            chunk[x][y] = malloc(*depth * sizeof ***chunk);

            for (int z = 0; z < *depth; z++)
                fscanf(file,"%hhd", &chunk[x][y][z]);
        }
    }

    return chunk;
}
void print_block_chunk(chunk_t chunk, const Vector3_t chunk_size, const  Vector3_t block_position) {
    if (block_position.x < 0 || block_position.x >= chunk_size.x) {
        printf("ERROR: X coordinate is not valid\n");
        return;
    }
    if (block_position.y < 0 || block_position.y >= chunk_size.y) {
        printf("ERROR: Y coordinate is not valid\n");
        return;
    }
    if (block_position.z < 0 || block_position.z >= chunk_size.z) {
        printf("ERROR: Z coordinate is not valid\n");
        return;
    }
    printf("Block %d at X:%d Y:%d Z:%d\n",chunk[block_position.x][block_position.y][block_position.z],
        block_position.x,block_position.y,block_position.z);
}
void print_chunk(chunk_t chunk, Vector3_t size) {
    printf("Chunk: width-%d, height-%d, depth-%d", size.x, size.y, size.z);
    for (int x  = 0; x < size.x; x++) {
        for (int y  = 0; y < size.y; y++) {
            for (int z  = 0; z < size.z; z++) {
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
