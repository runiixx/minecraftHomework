//
// Created by vik on 6/27/25.
//

#ifndef UI_UX_H
#define UI_UX_H
#include "../libchunk/chunk.h"

void update_cube_cursor(chunk_t *chunk,Vector3_t *chunkSize, Vector3 *cube_cursor, Camera3D *camera);
void DrawTextBox(Rectangle bounds, char *text, int maxChars, bool *active);
#endif //UI_UX_H
