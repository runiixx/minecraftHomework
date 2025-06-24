//
// Created by vik on 6/23/25.
//

#ifndef CHUNK_H
#define CHUNK_H
#define BLOCK_AIR       0
#define BLOCK_GRASS     1
#define BLOCK_WOOD      2
#define BLOCK_STONE      3

typedef char*** chunk_t;
chunk_t read_chunk(int *width, int *height, int *depth);
void print_chunk(chunk_t chunk, int width, int height, int depth);
chunk_t chunk_place_block(chunk_t chunk, int width, int height, int depth, int x, int y, int z, char block);
chunk_t chunk_fill_cuboid(chunk_t chunk, int width, int height, int depth, int x0,int y0,int z0, int x1,int y1,int z1, char block);
chunk_t chunk_fill_sphere(chunk_t chunk, int width, int height, int depth, int x, int y, int z, int radius, char block);
#endif //CHUNK_H
