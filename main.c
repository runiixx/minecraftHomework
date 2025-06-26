#include <stdio.h>

#include "raylib.h"
#include "libchunk/chunk.h"
#include "libchunk/chunkcli.h"

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

    SetTargetFPS(120);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_FREE);

        if (IsKeyPressed('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        if (IsKeyPressed('P')) print_chunk(chunk, (Vector3_t){0,0,0});
        if (IsKeyPressed('T')) chunk_fill_sphere(chunk, (Vector3_t){width, height, depth}, (Vector3_t){5,5,5},4,2);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
        render_chunk(chunk, (Vector3_t){width, height, depth});
        DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

        DrawGrid(10, 1.0f);
        EndMode3D();

        DrawRectangle( 10, 10, 500, 93, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines( 10, 10, 500, 93, BLUE);

        DrawText("Free camera default controls:", 20, 20, 30, BLACK);
        DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 30, DARKGRAY);
        DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 30, DARKGRAY);
        DrawText("- Z to zoom to (0, 0, 0)", 40, 80, 30, DARKGRAY);
        DrawText("- P to print chunk in console", 40, 120, 30, DARKGRAY);

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