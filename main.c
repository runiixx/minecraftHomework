#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <raylib.h>
#include <raymath.h>
#include "libchunk/chunk.h"
#include "GUI/gui.h"
#include "UI_UX/ui_ux.h"
int main(void) {
    //------------------------------------------------------------------------------------------------------------------
    // Initializing a chunk
    //------------------------------------------------------------------------------------------------------------------
    Vector3_t chunkSize={0,0,0};
    //char*** chunk = read_chunk_file(&chunkSize);
    chunk_t chunk = init_chunk(&chunkSize);
    //const int screenWidth = GetScreenWidth();
    //const int screenHeight = GetScreenHeight();
    const int screenWidth = 1000;
    const int screenHeight = 1000;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_VSYNC_HINT);            // optional
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);      // resizable
    SetWindowState(FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(screenWidth, screenHeight, "Chunk test");
    EnableCursor();

    Camera3D camera = init_camera();

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
    Vector3 anotherCubePosition = { 0.0f, 0.0f, 2.0f };
    DisableCursor();                    // Limit cursor to relative movement inside the window
    Vector3 cube_cursor = { (float)chunkSize.x/2, 1.0f, (float)chunkSize.z/2 };
    SetTargetFPS(120);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    int third_mode = 1;
    char **cursor_status = malloc(2 * sizeof(char*));
    cursor_status[0] = malloc(10 * sizeof(char));
    cursor_status[1] = malloc(10 * sizeof(char));
    strcpy(cursor_status[0], "2D mode");
    strcpy(cursor_status[1], "3D mode");
    Vector2 mouseOffset = { 0 };
    bool dragging = false;
    camera.position = (Vector3){ (float)chunkSize.x/2-4,CAMERA_POSITION_Y, (float)chunkSize.z/2};
    camera.target = (Vector3){ CAMERA_TARGET_X, CAMERA_TARGET_Y, CAMERA_TARGET_Z};
    Rectangle input_test = {100, 100,100, 100};
    char text[15] = "\0";
    bool inputActive = false;
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        //printf("X:%f Y:%f Z:%f\n", camera.target.x, camera.target.y, camera.target.z);
        // Update
        //----------------------------------------------------------------------------------
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse = GetMousePosition();
            if (mouse.y < 30) { // custom title bar height
                dragging = true;
                Vector2 winPos = { GetWindowPosition().x, GetWindowPosition().y };
                mouseOffset.x = mouse.x;
                mouseOffset.y = mouse.y;
            }
        }
        if (!third_mode)UpdateCamera(&camera, CAMERA_FREE);
        if (IsKeyPressed('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        if (IsKeyPressed('P')) print_chunk(chunk, (Vector3_t){0,0,0});
        if (IsKeyPressed('T')) chunk_fill_sphere(chunk, chunkSize, (Vector3_t){5,5,5},4,2);
        if (IsKeyPressed('X')) third_mode = !third_mode;
        if (third_mode) {
            update_cube_cursor(&chunk,&chunkSize,&cube_cursor, &camera);
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        if (third_mode) EnableCursor();
        else DisableCursor();


        // Then render only visible cubes
        //render_chunk(chunk, chunkSize, frustumPlanes);
        render_chunk(chunk, chunkSize, camera);
        DrawCubeWires(cube_cursor,1.0f,1.0f,1.0f,MAROON);
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
        int fps = GetFPS();
        DrawRectangle(300,20, 50,50, Fade(SKYBLUE, 0.5f));
        if (third_mode) DrawText(cursor_status[0],305, 25, 30, MAROON);
        else DrawText(cursor_status[1],305, 25, 30, MAROON);
        //DrawTextBox(input_test,text,15,&inputActive);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    free_chunk(chunk, chunkSize);
    return 0;
}