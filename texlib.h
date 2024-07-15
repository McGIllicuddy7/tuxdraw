#pragma once
#include <raylib.h>
#include <raymath.h>
typedef struct {
  void *data;
} TexMat;
TexMat create_blank_tex_mat();
void free_tex_mat(TexMat *mat);
void tex_draw_triangle(Vector2 a, Vector2 b, Vector2 c, TexMat *tex);
