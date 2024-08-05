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
  float speed = 256.0;
  Vector2 location = {500,500};
  SetTargetFPS(60); 
  while (!WindowShouldClose()) {
    if(IsKeyDown(KEY_SPACE)){
      scale += GetFrameTime()*50;
    } else if(IsKeyDown(KEY_V)){
      scale -= GetFrameTime()*50;
    }
    if(scale>666){
      scale = 666;
    }
    if( scale<0){
      scale = 0;
    }
    if(IsKeyDown(KEY_W)){
      location.y-=GetFrameTime()*speed;
    }
    if(IsKeyDown(KEY_S)){
      location.y +=GetFrameTime()*speed;
    }
    if(location.y>1000){
      location.y = 1000;
    }
    if(location.y<0){
      location.y = 0;
    }
    if(IsKeyDown(KEY_A)){
      location.x-=GetFrameTime()*speed;
    }
    if(IsKeyDown(KEY_D)){
      location.x += GetFrameTime()*speed;
    }
    if(location.x>1000){
      location.x = 1000;
    }
    if(location.x<0){
      location.x = 0;
    }
    BeginDrawing();
    ClearBackground(BLACK);
    //tex_draw_quad((Vector2){200, 200}, (Vector2){800, 800}, (Vector2){200, 800},(Vector2){800,200},&test);
    tex_draw_circle(location,scale, &test );
    tex_draw_line((Vector2){0,0}, (Vector2){1000,1000},100.0, &test);
    //DrawTexture(test.tex.texture,0,0, WHITE);
    DrawFPS(950, 950);
    EndDrawing();
  }
  CloseWindow();
}
