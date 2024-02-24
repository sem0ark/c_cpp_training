#include "material.h"
#include "utils.h"
#include "camera.h"
#include "object.h"
#include "ray_tr_whitted.h"
#include "light_utils.h"
#include "screen.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  srand(time(NULL));

  options_t options = (options_t) {
    .width = 200,
    .height = 200,
    .console_ch_ratio = 1.0f,
    .aa_coef = 10,
    .fov = 40.0f,
    .max_depth = 4,
    .background_color = v3f_s(0.1f),
    .ambient_occlusion = v3f_s(0.0f),
    .bias = 1e-4,
  };


  camera_t cam = {
    .position = v3f(0, 1, 1.5f),
    .rotation = v3f(M_PI/24.0f,0.1f,0),
    .fov = 45,
  };
  
  set_direction(&cam);

  V3f_t obj_col = v3f_s(1.0);
  Material_t m1 = (Material_t){0};
  m1.type = DIFF_GLOSSY;
  m1.pattern_type = CHECKER;
  m1.ior = 1.52f;
  m1.specular_exp = 55.0f;
  m1.d_col   = mul_v3_f(obj_col, 1.0f);
  m1.e_col   = mul_v3_f(obj_col, 0.0f);
  m1.rfl_col = mul_v3_f(obj_col, 0.0f);
  m1.rfr_col = mul_v3_f(obj_col, 0.0f);
  m1.s_col   = mul_v3_f(obj_col, 0.0f);

  V3f_t obj_col_2 = v3f_s(0.9);//v3f(0.6f, 0.6f, 0.8f);
  Material_t m2 = (Material_t){0};
  m2.type = DIFF_GLOSSY | REFLECT;
  m2.pattern_type = PLAIN;
  m2.ior = 1.52f;
  m2.specular_exp = 55.0f;
  m2.d_col   = mul_v3_f(obj_col_2, 0.2f);
  m2.e_col   = mul_v3_f(obj_col_2, 0.0f);
  m2.rfl_col = mul_v3_f(obj_col_2, 1.0f);
  m2.rfr_col = mul_v3_f(obj_col_2, 1.0f);
  m2.s_col   = mul_v3_f(obj_col_2, 0.2f);

  V3f_t obj_col_3 = v3f_s(0.9);//v3f(0.8f, 0.6f, 0.6f);
  Material_t m3 = (Material_t){0};
  m3.type = DIFF_GLOSSY | REFLECT | REFRACT;
  m3.pattern_type = PLAIN;
  m3.ior = 1.4f;
  m3.specular_exp = 55.0f;
  m3.d_col   = mul_v3_f(obj_col_3, 0.2f);
  m3.e_col   = mul_v3_f(obj_col_3, 0.0f);
  m3.rfl_col = mul_v3_f(obj_col_3, 1.0f);
  m3.rfr_col = mul_v3_f(obj_col_3, 1.0f);
  m3.s_col   = mul_v3_f(obj_col_3, 0.2f);


  int Nl = 3;
  light_t **lights = (light_t **)malloc(sizeof(light_t *)*Nl);
  for (int i=0; i<Nl; i++) lights[i] = (light_t *)malloc(sizeof(light_t) * 1);

  *lights[0] = (light_t){
    .type = DIRECT,
    .direction = normalize_v3(v3f(0.0f, 0.1f, -1.0f)),
    .intensity = v3f(1.0f,0.0f,0.0f),
    .position = v3f(0, 0, 10),
    .kc = 1.0f,
    .kl = 0.0f,
    .kq = 0.0f,
    .kp = 25.0f,
  };

  *lights[1] = (light_t){
    .type = DIRECT,
    .direction = normalize_v3(v3f(0.0f, -0.1f, -1.0f)),
    .intensity = v3f(0.0f,0.0f,1.0f),
    .position = v3f(0, 2, 10),
    .kc = 1.0f,
    .kl = 0.0f,
    .kq = 0.01f,
    .kp = 25.0f,
  };

  *lights[2] = (light_t){
    .type = DIRECT,
    .direction = normalize_v3(v3f(0.0f, -0.0f, -1.0f)),
    .intensity = v3f(0.0f,1.0f,0.0f),
    .position = v3f(0, 4, 10),
    .kc = 1.0f,
    .kl = 0.0f,
    .kq = 0.01f,
    .kp = 25.0f
  };

  int No = 3;
  object_t **objects = (object_t **)malloc(sizeof(object_t *)*No);
  for (int i=0; i<No; i++) objects[i] = (object_t *)malloc(sizeof(object_t) * 1);

  *objects[0] = (object_t) {
    .o_pln = (plane_t) {
      .type = PLANE,
      .material = &m1,
      .center = v3f(10,0,0),
      .norm = normalize_v3(v3f(0,0,1)),
    }
  };

  *objects[1] = (object_t) {
    .o_sphr = (sphere_t) {
      .type = SPHERE,
      .material = &m2,
      .center = v3f(5,2.5f,1),
      .radius = 0.5f,
    }
  };

  *objects[2] = (object_t) {
    .o_sphr = (sphere_t) {
      .type = SPHERE,
      .material = &m3,
      .center = v3f(6,1,2),
      .radius = 1.0f,
    }
  };

  V3f_t *pixels = (V3f_t *)malloc(options.width * options.height * sizeof(V3f_t));

  render(&options, &cam, pixels, objects, No, lights, Nl);
  pixels2file(&options, pixels);
  
  for (int i=0; i<Nl; i++) free(lights[i]);
  free(lights);

  for (int i=0; i<No; i++) free(objects[i]);
  free(objects);
  
  return 0;
}
