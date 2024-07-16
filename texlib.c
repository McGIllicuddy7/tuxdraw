#include "texlib.h"
#include <raylib.h>
#include <raymath.h>
#include <string.h>
#include <time.h>
TexMat create_blank_tex_mat() { return (TexMat){NULL}; }

void tex_draw_triangle(Vector2 a, Vector2 b, Vector2 c, TexMat *tex) {
  Material m = LoadMaterialDefault();
  float buff[] = {a.x, a.y, 0, b.x, b.y, 0, c.x, c.y, 0};
  float coords[] = {0, 0, 0.5, 1.0, 1.0, 0};
  float normals[] = {0, 1, 0, 0, 1, 0, 0, 1, 0};
  Mesh mesh = {0};
  mesh.triangleCount = 1;
  mesh.vertexCount = 3;
  mesh.vertices = MemAlloc(sizeof(float) * 3 * 3);
  memcpy(mesh.vertices, buff, sizeof(float) * 9);
  mesh.texcoords = MemAlloc(sizeof(float) * 2 * 3);
  memcpy(mesh.texcoords, coords, sizeof(float) * 2 * 3);
  mesh.normals = MemAlloc(sizeof(float) * 3 * 3);
  memcpy(mesh.normals, normals, sizeof(float) * 3 * 3);
  UploadMesh(&mesh, false);
  DrawMesh(mesh, m, MatrixIdentity());
  UnloadMesh(mesh);
  UnloadMaterial(m);
}
