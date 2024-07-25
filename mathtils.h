#pragma once
#include <raylib.h>
#include <raymath.h>
typedef struct {
  Vector2 points[3];
}Tri;
typedef struct{
  Vector2 points[4];
}Quad;
Tri make_valid_tri(Vector2 a, Vector2 b, Vector2 c);
Quad make_valid_quad(Vector2 a, Vector2 b, Vector2 c, Vector2 d);

