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
    tex_draw_quad((Vector2){200, 200}, (Vector2){800, 800}, (Vector2){200, 800},(Vector2){800,200},
                      &test);
    EndDrawing();
  }
}
