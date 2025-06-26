//
// Created by vik on 6/23/25.
//

#ifndef CHUNK_H
#define CHUNK_H
#define BLOCK_AIR       0
#define BLOCK_GRASS     1
#define BLOCK_WOOD      2
#define BLOCK_STONE      3

#include <raylib.h>

typedef char*** chunk_t;
typedef struct {
    int x,y,z;
} Vector3_t;

Camera3D init_camera();
void render_chunk(const chunk_t chunk, const Vector3_t size);
void free_chunk(chunk_t chunk, const Vector3_t size);
chunk_t place_block( chunk_t chunk, const Vector3_t size, const Vector3_t position, char block);
chunk_t allocate_chunk(const Vector3_t size);
chunk_t chunk_place_block(chunk_t chunk, int width, int height, int depth, int x, int y, int z, char block);

chunk_t chunk_fill_cuboid(chunk_t chunk, const Vector3_t chunk_size,
    const Vector3_t p1, const Vector3_t p2, char block);
chunk_t chunk_fill_sphere(chunk_t chunk, const Vector3_t chunk_size,
    const Vector3_t position, double radius, char block);

//----------------------------------------------------------------------------------------------------------------------
// CHUNK_CLI
//----------------------------------------------------------------------------------------------------------------------
chunk_t read_chunk_file(int *width, int *height, int *depth);
chunk_t read_chunk(int *width, int *height, int *depth);
void print_chunk(chunk_t chunk, Vector3_t size);
void print_block_chunk(chunk_t chunk, const Vector3_t chunk_size, const Vector3_t block_position);
#endif //CHUNK_H
