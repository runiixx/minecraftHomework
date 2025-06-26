#include <raylib.h>
#include <stdio.h>
#include <string.h>
//
// Created by vik on 6/26/25.
//
void draw_label(char** text, int lines, Vector3 position) {
    //------------------------------------------------------------------------------------------------------------------
    // Getting the max width
    //------------------------------------------------------------------------------------------------------------------
    unsigned int  max_width = 0;
    int i;
    for (i = 0; i < lines; i++) {
        max_width = (max_width > strlen(text[i])) ? max_width : strlen(text[i]);;
    }
    DrawRectangle((int)position.x, (int)position.y,max_width *25, i * 35, Fade(SKYBLUE,0.5f));
    //printf("max_width = %d\n", max_width);
    //DrawRectangle( 10, 10, 500, 93, Fade(SKYBLUE, 0.5f));
    int current_size = 0;
    for (;current_size <lines;current_size++) {
        DrawText(text[current_size], (int)position.x + 5, (int)position.y+ 32 * current_size + 5, 30, RED);

    }

}