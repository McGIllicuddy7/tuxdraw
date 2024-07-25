#pragma once
#include <raylib.h>
#include <raymath.h>
typedef struct {
  void *data;
} TexMat;
#define Option(T) struct {bool is_valid; union{T value; void * nothing;};}
TexMat tex_create_blank_mat();
Option(TexMat) tex_create_mat(const char * code);

void tex_free_mat(TexMat *mat);
void tex_draw_triangle(Vector2 a, Vector2 b, Vector2 c, TexMat *tex);

