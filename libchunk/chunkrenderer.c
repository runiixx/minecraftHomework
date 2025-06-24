//
// Created by vik on 6/24/25.
//
#include "chunk.h"
#include <raylib.h>

void render_chunk(chunk_t chunk, int width, int height, int depth) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int z = 0; z < depth; z++) {
                float xf = (float)x;
                float yf = (float)y;
                float zf = (float)z;
                Vector3 Position={xf,yf,zf};
                Color color;
                if (chunk[x][y][z] == 1) color = GREEN;
                if (chunk[x][y][z] == 2) color = MAROON;
                if (chunk[x][y][z] == 3) color = BLUE;
                if (chunk[x][y][z] !=0)
                    DrawCube(Position,1.0f,1.0f,1.0f,color);
            }
        }
    }
}
