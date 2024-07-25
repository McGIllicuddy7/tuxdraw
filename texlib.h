#pragma once
#include <raylib.h>
#include <raymath.h>
typedef struct {
  Shader shader;
} TexMat;

TexMat tex_create_blank_mat();
TexMat tex_create_mat_from_program(const char * program);

void tex_free_mat(TexMat *mat);

void tex_draw_triangle(Vector2 a, Vector2 b, Vector2 c, TexMat *tex);
void tex_draw_triangle_unchecked(Vector2 a, Vector2 b,Vector2 c, TexMat * tex);

void tex_draw_quad(Vector2 a, Vector2 b, Vector2 c, Vector2 d, TexMat * tex);
void tex_draw_quad_unchecked(Vector2 a, Vector2 b, Vector2 c,Vector2 d, TexMat * tex);
