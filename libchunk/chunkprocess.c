//
// Created by vik on 6/26/25.
//
#include "chunk.h"


chunk_t block_shell(chunk_t chunk, chunk_t copy,const Vector3_t chunk_size,
                    const Vector3_t position, const char target_block,const char shell_block) {
    for (int x = position.x - 1; x <= position.x + 1; x++) {
        for (int y = position.y - 1; y <= position.y + 1; y++) {
            for (int z = position.z - 1; z <= position.z + 1; z++) {
                if ( x != position.x || y != position.y || z != position.z ) continue;
                if (x < 0 || x >= chunk_size.x) continue;
                if (y < 0 || y >= chunk_size.y) continue;
                if (z < 0 || z >= chunk_size.z) continue;
                if (chunk[x][y][z] != target_block)
                    copy = place_block(copy, chunk_size, (Vector3_t){x,y,z}, shell_block);
            }
        }
    }
    return copy;
}
