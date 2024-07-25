#include "texlib.h"
#include <raylib.h>
#include <raymath.h>
#include <string.h>
#include <rlgl.h>
#include <time.h>
#include <stdio.h>
#include "mathtils.h"
#include "utils.h"
/*
 TexMat functions
 */
TexMat tex_create_mat_from_program(const char * program){
      return (TexMat){0};
}
TexMat tex_create_blank_mat() {
  String vs_code = read_file_to_string("shaders/base.vs");
  String fs_code = read_file_to_string("shaders/base.fs");
  Shader t =LoadShader("shaders/base.vs", "shaders/base.fs");
  TexMat out = {t};
  destroy(vs_code);
  destroy(fs_code);
  return out;
} 

/*
 Drawing functions*/
void tex_draw_triangle(Vector2 a, Vector2 b, Vector2 c, TexMat *tex){
  Tri t = make_valid_tri(a,b,c);
  tex_draw_triangle_unchecked(t.points[0], t.points[1], t.points[2], tex);
}

void tex_draw_quad(Vector2 a, Vector2 b, Vector2 c, Vector2 d, TexMat * tex){
  Quad q = make_valid_quad(a,b,c,d);
  tex_draw_quad_unchecked(q.points[0], q.points[1], q.points[2], q.points[3], tex);
}

void tex_draw_quad_unchecked(Vector2 a, Vector2 b, Vector2 c,Vector2 d, TexMat * tex){
  BeginShaderMode(tex->shader);
  rlBegin(RL_TRIANGLES);
  float w = GetScreenWidth();
  float h = GetScreenHeight();
  rlTexCoord2f(a.x/w, a.y/h);
  rlColor4ub(255, 0, 0, 255);
  rlVertex2f(a.x, a.y);

  rlTexCoord2f(b.x/w, b.y/h);
  rlColor4ub(0, 255, 0, 255);
  rlVertex2f(b.x, b.y);

  rlTexCoord2f(c.x/w, c.y/h);
  rlColor4ub(0, 0, 255, 255);
  rlVertex2f(c.x, c.y);

  rlTexCoord2f(c.x/w, c.y/h);
  rlColor4ub(0, 0, 255, 255);
  rlVertex2f(c.x, c.y);

  rlTexCoord2f(d.x/w, d.y/h);
  rlColor4ub(0, 255, 0, 255);
  rlVertex2f(d.x, d.y);
    
  rlTexCoord2f(a.x/w, a.y/h);
  rlColor4ub(255, 0, 0, 255);
  rlVertex2f(a.x, a.y);
  rlEnd();
  EndShaderMode();
}

void tex_draw_triangle_unchecked(Vector2 a, Vector2 b, Vector2 c, TexMat *tex) {
  rlBegin(RL_TRIANGLES);
  float w = GetScreenWidth();
  float h = GetScreenHeight();
  rlTexCoord2f(a.x/w, a.y/h);
  rlColor4ub(255, 0, 0, 255);
  rlVertex2f(a.x, a.y);

  rlTexCoord2f(b.x/w, b.y/h);
  rlColor4ub(0, 255, 0, 255);
  rlVertex2f(b.x, b.y);

  rlTexCoord2f(c.x/w, c.y/h);
  rlColor4ub(0, 0, 255, 255);
  rlVertex2f(c.x, c.y);
  rlEnd();
}

