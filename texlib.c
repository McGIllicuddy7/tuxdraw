#include "texlib.h"
#include <raylib.h>
#include <raymath.h>
#include <string.h>
#include <rlgl.h>
#include <time.h>
#include <stdio.h>
TexMat create_blank_tex_mat() { return (TexMat){NULL}; }

void tex_draw_triangle(Vector2 a, Vector2 b, Vector2 c, TexMat *tex) {
  rlBegin(RL_TRIANGLES);
  rlColor4ub(255, 0, 0, 255);
  rlVertex2f(b.x, b.y);
  rlVertex2f(a.x, a.y);
  rlVertex2f(c.x, c.y);
  rlEnd();
}
