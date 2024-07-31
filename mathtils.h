#pragma once
#include <raylib.h>
#include <raymath.h>
typedef struct {
  Vector2 points[3];
}Tri;
typedef struct{
  Vector2 points[4];
}Quad;
[[gnu::always_inline]]
inline Tri make_valid_tri(Vector2 a, Vector2 b, Vector2 c){
  Vector2 out[3] = {};
  float thetas[3] = {};
  Vector2 center = Vector2Scale(Vector2Add(Vector2Add(a,b),c),1.0/3.0);
  thetas[0] = Vector2Angle(Vector2Normalize(Vector2Subtract(a,center)), (Vector2){1.0, 0.0});
  thetas[1] = Vector2Angle(Vector2Normalize(Vector2Subtract(b,center)), (Vector2){1.0, 0.0});
  thetas[2] = Vector2Angle(Vector2Normalize(Vector2Subtract(c,center)), (Vector2){1.0, 0.0});
  if(thetas[0] <=thetas[1] && thetas[1]<= thetas[2]){
    out[0] =a;
    out[1] =b;
    out[2] =c;
  } else if(thetas[1]<=thetas[0] && thetas[0]<thetas[2]){
    out[0] =b;
    out[1] =a;
    out[2] = c;

  } else if (thetas[0] <=thetas[2] && thetas[2] <= thetas[1]){
    out[0] =a;
    out[1] =c;
    out[2]=b;

  } else if(thetas[2] <=thetas[0] && thetas[0] <=thetas[1]){
    out[0]= c;
    out[1] =a;
    out[2] = b;

  } else if(thetas[1]<=thetas[2] && thetas[2] <=thetas[0]){
    out[0] =b;
    out[1] =c;
    out[2] =a;
  } else if(thetas[2] <=thetas[1] && thetas[1] <=thetas[0]){
    out[0] = c;
    out[1] = b;
    out[2] =a;
  }
  Tri v_out = {out[0], out[1], out[2]};
  return v_out;
}
[[gnu::always_inline]]
inline Quad make_valid_quad(Vector2 a, Vector2 b, Vector2 c, Vector2 d){
  Vector2 out[4] = {a,b,c,d};
  float thetas[4] = {};
  Vector2 center = Vector2Scale(Vector2Add(Vector2Add(a,b),Vector2Add(c,d)),0.25);
  thetas[0] = Vector2Angle(Vector2Normalize(Vector2Subtract(a,center)), (Vector2){1.0, 0.0});
  thetas[1] = Vector2Angle(Vector2Normalize(Vector2Subtract(b,center)), (Vector2){1.0, 0.0});
  thetas[2] = Vector2Angle(Vector2Normalize(Vector2Subtract(c,center)), (Vector2){1.0, 0.0});
  thetas[3] = Vector2Angle(Vector2Normalize(Vector2Subtract(d,center)), (Vector2){1.0, 0.0});
  for(int i =0; i<4; i++){
    float min_theta = thetas[i];
    int min_idx = i;
    for(int j = i; j<4; j++){
        if( thetas[j]<min_theta){
          min_theta = thetas[j];
          min_idx =j;
        }
    }
    Vector2 tmp = out[i];
    out[i] = out[min_idx];
    out[min_idx] = tmp;
    float ftmp = thetas[i];
    thetas[i] = thetas[min_idx];
    thetas[min_idx] = ftmp;
  }  
  Quad v_out = {out[0], out[1], out[2], out[3]};
  return v_out;
}
