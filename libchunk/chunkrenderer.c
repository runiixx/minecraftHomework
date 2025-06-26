//
// Created by vik on 6/24/25.
//
#include "chunk.h"
#include <raylib.h>

Camera3D init_camera() {
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
    return camera;
}
void render_chunk(const chunk_t chunk, const Vector3_t size) {
    for (int x = 0; x < size.x; x++) {
        for (int y = 0; y < size.y; y++) {
            for (int z = 0; z < size.z; z++) {
                float xf = (float)x;
                float yf = (float)y;
                float zf = (float)z;
                Vector3 Position={xf,yf,zf};
                Color color = BLACK;
                if (chunk[x][y][z] == 1) color = GREEN;
                if (chunk[x][y][z] == 2) color = MAROON;
                if (chunk[x][y][z] == 3) color = BLUE;
                if (chunk[x][y][z] !=0 && chunk[x][y][z] != 1 && chunk[x][y][z] != 3) {
                    DrawCube(Position,1.0f,1.0f,1.0f,color);
                    DrawCubeWires(Position, 1.0f, 1.0f, 1.0f, BLACK);
                }
            }
        }
    }
}
