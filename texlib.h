#pragma once
#include <raylib.h>
#include <raymath.h>
typedef struct {
  Shader shader;
  Shader oval_shader;
} TexMat;
typedef struct{
  bool is_some;
  TexMat value;
}OptTexMat;

#define unwrap(v) assert(v.is_some); v.value
#define is_some(v) v.is_some
#define is_none(v) !v.is_some

TexMat tex_create_blank_mat();
OptTexMat tex_create_mat_from_program(const char * program);
OptTexMat tex_create_mat_from_file(const char * file_path);
void tex_free_mat(TexMat *mat);

void tex_draw_triangle(Vector2 a, Vector2 b, Vector2 c, TexMat *tex);
void tex_draw_triangle_unchecked(Vector2 a, Vector2 b,Vector2 c, TexMat * tex);

void tex_draw_quad(Vector2 a, Vector2 b, Vector2 c, Vector2 d, TexMat * tex);
void tex_draw_quad_unchecked(Vector2 a, Vector2 b, Vector2 c,Vector2 d, TexMat * tex);

void tex_draw_circle(Vector2 location, float radius, TexMat * tex);
