#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <raylib.h>
#include <raymath.h>
#include "libchunk/chunk.h"
#include "GUI/gui.h"
int main(void) {
    //------------------------------------------------------------------------------------------------------------------
    // Initializing a chunk
    //------------------------------------------------------------------------------------------------------------------
    int width=0, height=0, depth=0;
    char*** chunk = read_chunk_file(&width, &height, &depth);
    print_chunk(chunk, (Vector3_t){width, height, depth});
    print_block_chunk(chunk,(Vector3_t){width,height,depth},(Vector3_t){0,0,0});

    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    InitWindow(screenWidth, screenHeight, "Chunk test");


    Camera3D camera = init_camera();

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
    Vector3 anotherCubePosition = { 0.0f, 0.0f, 2.0f };
    DisableCursor();                    // Limit cursor to relative movement inside the window
    Vector3 cube_cursor = { 0.0f, 0.0f, 0.0f };
    SetTargetFPS(120);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    int third_mode = 1;
    char **cursor_status = malloc(2 * sizeof(char*));
    cursor_status[0] = malloc(10 * sizeof(char));
    cursor_status[1] = malloc(10 * sizeof(char));
    strcpy(cursor_status[0], "2D mode");
    strcpy(cursor_status[1], "3D mode");
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (!third_mode)UpdateCamera(&camera, CAMERA_FREE);
        Vector3 rawForward = Vector3Subtract(camera.target, camera.position);
        rawForward.y = 0;  // Zero out Y component to prevent vertical movement
        Vector3 forward = Vector3Normalize(rawForward);

        int dx = (int)roundf(forward.x);
        int dz = (int)roundf(forward.z);
        Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera.up));
        int strafeX = (int)roundf(right.x);
        int strafeZ = (int)roundf(right.z);

        if (IsKeyPressed('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        if (IsKeyPressed('P')) print_chunk(chunk, (Vector3_t){0,0,0});
        if (IsKeyPressed('T')) chunk_fill_sphere(chunk, (Vector3_t){width, height, depth}, (Vector3_t){5,5,5},4,2);
        if (IsKeyPressed('X')) third_mode = !third_mode;
        if (third_mode) {
            if (IsKeyPressed(KEY_F)) {
                if ((int)cube_cursor.x >=0 && (int)cube_cursor.x < width &&
                    (int)cube_cursor.y >=0 && (int)cube_cursor.y < height &&
                    (int)cube_cursor.z >=0 && (int)cube_cursor.z < depth) {
                    if (chunk[(int)cube_cursor.x][(int)cube_cursor.y][(int)cube_cursor.z] ==0)
                        place_block(chunk, (Vector3_t){width, height, depth},(Vector3_t){cube_cursor.x,cube_cursor.y, cube_cursor.z}, 2);
                    else
                        place_block(chunk, (Vector3_t){width, height, depth},(Vector3_t){cube_cursor.x,cube_cursor.y, cube_cursor.z}, 0);
                    }
            }
            if (IsKeyPressed(KEY_W)) {
                cube_cursor.x += dx;
                cube_cursor.z += dz;
            }
            if (IsKeyPressed(KEY_S)) {
                cube_cursor.x -= dx;
                cube_cursor.z -= dz;
            }

            if (IsKeyPressed(KEY_D)) {
                cube_cursor.x += strafeX;
                cube_cursor.z += strafeZ;
            }
            if (IsKeyPressed(KEY_A)) {
                cube_cursor.x -= strafeX;
                cube_cursor.z -= strafeZ;
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        if (third_mode) EnableCursor();
        else DisableCursor();
        render_chunk(chunk, (Vector3_t){width, height, depth});
        DrawCubeWires(cube_cursor,1.0f,1.0f,1.0f,MAROON);
        DrawGrid(10, 1.0f);
        EndMode3D();

        char **test = malloc(4 * sizeof(char*));
        test[0] = malloc(31 * sizeof(char));
        strcpy(test[0], "X - Toggle 2D/3D movement");
        test[1] = malloc(31 * sizeof(char));
        strcpy(test[1], "T - Inserts exactly one sphere lmao");
        test[2] = malloc(31 * sizeof(char));
        strcpy(test[2], "WASD - Moves camera/cursor");
        test[3] = malloc(31 * sizeof(char));
        strcpy(test[3], "ESC - Quit");
        draw_label(test,4,(Vector3){100,100,0});

        DrawRectangle(300,20, 50,50, Fade(SKYBLUE, 0.5f));
        if (third_mode) DrawText(cursor_status[0],305, 25, 30, MAROON);
        else DrawText(cursor_status[1],305, 25, 30, MAROON);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    free_chunk(chunk, (Vector3_t){width, height, depth});
    return 0;
}