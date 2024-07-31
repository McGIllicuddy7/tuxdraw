#include "texlib.h"
#include <raylib.h>
#include <raymath.h>
#include <string.h>
#include <rlgl.h>
#include <time.h>
#include <stdio.h>
#include "mathtils.h"
#include "utils.h"
#include <stdbool.h>
/*
 TexMat functions
 */
const char * vertex_shader_code = "#version 330\n" 
// Input vertex attributes
"in vec3 vertexPosition;"
"in vec2 vertexTexCoord;"
"in vec3 vertexNormal;"
"in vec4 vertexColor;"

// Input uniform values
"uniform mat4 mvp;"

// Output vertex attributes (to fragment shader)
"out vec2 fragTexCoord;"
"out vec4 fragColor;"

// NOTE: Add here your custom variables

"void main()"
"{"
    // Send vertex attributes to fragment shader
    "fragTexCoord = vertexTexCoord;"
    "fragColor = vertexColor;"

    // Calculate final vertex position
    "gl_Position = mvp*vec4(vertexPosition, 1.0);"
"}";
const char * frag_shader_code = 

// NOTE: Add here your custom variables

"void main()"
"{"
    // Texel color fetching from texture sampler
    "vec4 texelColor = texture(texture0, fragTexCoord);"

    // NOTE: Implement here your fragment shader code

    "finalColor.r = fragColor.r;"
    "finalColor.g = fragColor.g; "
    "finalColor.b = fragColor.b;"
    "finalColor.a = fragColor.a;"
"}";
OptTexMat tex_create_mat_from_file(const char * file_path){
  String s = read_file_to_string(file_path);
OptTexMat out =tex_create_mat_from_program(s.items);
  destroy(s);
  return out;
}

OptTexMat tex_create_mat_from_program(const char * program){
  String s = new_string(program);
  const char * l = "main()";
  int idx = -1;
  bool findable = true;
  for(int i =0; i<s.length; i++){
    bool found = true;  
    for(int j = 0; j<6; j++){
        if(j+i >=s.length){
            found = false;
            findable = false;
            break;
        }
        if(s.items[i+j] != l[j]){
            found = false;
        } 
      }
    if(found){
      idx = i;
      break;
    }
    if(!findable){
      break;
    }
  }
  if (idx == -1){
      destroy(s);
      return (OptTexMat){false};
  }
  insert(s, idx, '_');
  const char * vars =
"in vec2 fragTexCoord;\n"
"in vec4 fragColor;\n"

// Input uniform values
"uniform sampler2D texture0;\n"
"uniform vec4 colDiffuse;\n"

// Output fragment color
"out vec4 finalColor;\n";
  String tmp = string_format("#version 330\n%s\n%s\nvoid main(){_main();}",vars, s.items);
  printf("%s\n", tmp.items);
  String circ_tmp = string_format("#version 330\n%s\nuniform vec2 location; uniform float rad_w; uniform float rad_h; %s\nvoid main(){float a = fragTexCoord.x-location.x; float b = fragTexCoord.y-location.y;if ((sqrt(a*a/(rad_w*rad_w)+b*b/(rad_h*rad_h)))>=1.0){discard;}_main();}", vars,s.items);
  Shader base =  LoadShaderFromMemory(vertex_shader_code, tmp.items);
  Shader circle = LoadShaderFromMemory(vertex_shader_code, circ_tmp.items);
  destroy(tmp);
  destroy(s);
  destroy(circ_tmp);
  return (OptTexMat){true,(TexMat){base, circle, GetShaderLocation(circle, "location"), GetShaderLocation(circle, "rad_w"),GetShaderLocation(circle, "rad_h")}};
}
TexMat tex_create_blank_mat() { 
  OptTexMat out = (tex_create_mat_from_program(frag_shader_code));
  assert(out.is_some);
  return out.value;
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
  rlEnd();
  EndShaderMode();
}

void tex_draw_circle(Vector2 location, float radius, TexMat * tex){
  BeginShaderMode(tex->oval_shader);
  rlBegin(RL_TRIANGLES);
  float w = GetScreenWidth();
  float h = GetScreenHeight();
  Vector2 norm_location = (Vector2){location.x/w, location.y/h};
  float norm_rad_y = radius/(h);
  float norm_rad_x = radius/(w);
  SetShaderValue(tex->oval_shader, tex->circ_location_idx, &norm_location, SHADER_UNIFORM_VEC2);
  SetShaderValue(tex->oval_shader, tex->circ_width_idx, &norm_rad_x, SHADER_UNIFORM_FLOAT);
  SetShaderValue(tex->oval_shader, tex->circ_height_idx, &norm_rad_y, SHADER_UNIFORM_FLOAT);
  Quad tmp = make_valid_quad(
    (Vector2){location.x+radius, location.y+radius}, 
    (Vector2){location.x+radius, location.y-radius}, 
    (Vector2){location.x-radius, location.y+radius},
    (Vector2){location.x-radius, location.y-radius});
  Vector2 a = tmp.points[0];
  Vector2 b = tmp.points[1];
  Vector2 c = tmp.points[2];
  Vector2 d = tmp.points[3];
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
