//
// Created by vik on 6/24/25.
//

#ifndef CHUNKCLI_H
#define CHUNKCLI_H
#include "chunk.h"

chunk_t read_chunk_file(int *width, int *height, int *depth);
chunk_t read_chunk(int *width, int *height, int *depth);
void print_chunk(chunk_t chunk, Vector3_t size);
void print_block_chunk(chunk_t chunk, const Vector3_t chunk_size, const Vector3_t block_position);
#endif //CHUNKCLI_H
