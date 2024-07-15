#define CTILS_IMPLEMENTATION
#include "texlib.h"
#include "utils.h"
#include <raylib.h>
int main() {
  InitWindow(1000, 1000, "Hello Sailor");
  Camera camera = {{5.0, 5.0, 5.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 1.0}, 45.0, 0};
  TexMat test = create_blank_tex_mat();
  while (!WindowShouldClose()) {
    BeginDrawing();
    BeginMode3D(camera);
    ClearBackground(BLACK);
    tex_draw_triangle((Vector2){0, 0}, (Vector2){500, 500}, (Vector2){0, 1000},
                      &test);
    EndMode3D();
    EndDrawing();
  }
}
