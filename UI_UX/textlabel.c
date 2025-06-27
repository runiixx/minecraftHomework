//
// Created by vik on 6/27/25.
//
#include <raylib.h>
#include "ui_ux.h"
#include "../libchunk/chunk.h"

void DrawTextBox(Rectangle bounds, char *text, int maxChars, bool *active)
{
    static int letterCount = 0;
    static int framesCounter = 0;
    static float backspaceTimer = 0.0f;
    static bool backspaceHeld = false;

    float delta = GetFrameTime();
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        *active = CheckCollisionPointRec(mouse, bounds);
    }

    if (*active)
    {
        int key = GetCharPressed();
        while (key > 0)
        {
            if ((key >= 32) && (key <= 125) && (letterCount < maxChars))
            {
                text[letterCount] = (char)key;
                text[letterCount + 1] = '\0';
                letterCount++;
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (letterCount > 0) {
                letterCount--;
                text[letterCount] = '\0';
            }
            backspaceHeld = true;
            backspaceTimer = 0.0f;
        } else if (IsKeyDown(KEY_BACKSPACE) && backspaceHeld) {
            backspaceTimer += delta;
            if (backspaceTimer >= 0.5f) {
                if ((int)((backspaceTimer - 0.5f) / 0.05f) != (int)((backspaceTimer - 0.5f - delta) / 0.05f)) {
                    if (letterCount > 0) {
                        letterCount--;
                        text[letterCount] = '\0';
                    }
                }
            }
        } else {
            backspaceHeld = false;
        }
    }

    // Draw box
    DrawRectangleLinesEx(bounds, 2, *active ? RED : GRAY);
    DrawText(text, bounds.x + 5, bounds.y + 15, 20, BLACK);

    if (*active && ((framesCounter / 20) % 2 == 0)) {
        DrawText("_", bounds.x + 8 + MeasureText(text, 20), bounds.y + 15, 20, BLACK);
    }

    if (*active) framesCounter++;
    else framesCounter = 0;
}
