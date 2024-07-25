#define CTILS_IMPLEMENTATION 
#include "texlib.h"
#include "utils.h"
#include <raylib.h>
int main() {
  InitWindow(1000, 1000, "Hello Sailor");
  TexMat test = tex_create_blank_mat();
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    tex_draw_triangle((Vector2){0, 0}, (Vector2){500, 500}, (Vector2){0, 1000},
                      &test);
    EndDrawing();
  }
}
