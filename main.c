#define CTILS_IMPLEMENTATION 
#include "texlib.h"
#include "utils.h"
#include <raylib.h>
int main() {
  InitWindow(1000, 1000, "Hello Sailor");
  OptTexMat testOpt = tex_create_mat_from_file("ground_frag.glsl");
  assert(testOpt.is_some);
  TexMat test = testOpt.value;
  float scale = 50.0;
  while (!WindowShouldClose()) {
    if(IsKeyDown(KEY_W)){
      scale += GetFrameTime()*50;
    } else if(IsKeyDown(KEY_S)){
      scale -= GetFrameTime()*50;
    }
    if(scale>666){
      scale = 666;
    }
    if( scale<0){
      scale = 0;
    }
    BeginDrawing();
    ClearBackground(BLACK);
   // tex_draw_quad((Vector2){200, 200}, (Vector2){800, 800}, (Vector2){200, 800},(Vector2){800,200},
    //                  &test);
    tex_draw_circle((Vector2){500, 500},scale, &test );
    DrawFPS(950, 950);
    EndDrawing();
  }
}
