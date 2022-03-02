#include "material.h"
#include "utils.h"
#include "camera.h"
#include "object.h"
#include "ray_tr_whitted.h"
#include "light_utils.h"
#include "screen.h"
#include "timer.h"
#include "kb_linux.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
//#include <linux/input.h>

void test_vectors(void) {
  // testing vectors
  V3f_t a = v3f(1, 2, 3);
  V3f_t b = v3f(3, -4, 0.5);
  printf("%s\n", repr_v3(mul_v3_f(a, 10)));
  printf("%s\n", repr_v3(mul_v3_f(a, 0.1)));
  printf("%s\n", repr_v3(mul_v3_f(a, -1)));

  printf("%s\n", repr_v3(mul_v3_v(a, b)));

  printf("%s\n", repr_v3(sum_v3(a, b)));
  printf("%s\n", repr_v3(diff_v3(a, b)));

  printf("%f\n", dot_v3(a, b));
  printf("%f\n", len_sq_v3(a));
  printf("%f\n", len_v3(a));
}

float frand(void) {
  return (float) (rand() * 1.0 / RAND_MAX);
}

float frand_range(float min, float max) {
  return min + frand() * (max-min);
}

void test_whitted(void) {

  srand(time(NULL));

  options_t options = (options_t) {
    .width = 400,
    .height = 400,
    .console_ch_ratio = 0.5f,
    .aa_coef = 3,
    .fov = 40.0f,
    .max_depth = 2,
    .background_color = v3f_s(0.1f),
    .ambient_occlusion = v3f_s(0.0f),
    .bias = 1e-4,
  };


  camera_t cam = {
    .position = v3f(0, 0, 1),
    .rotation = v3f(0,0,0),
    .fov = 45,
  };
  set_direction(&cam);
  //cam.c2w = get_cam2w_mat44f(&cam);


  V3f_t obj_col = v3f_s(1.0);//v3f(0.3f, 0.7f, 0.7f);
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

  V3f_t obj_col_3 = v3f(0.8f, 0.6f, 0.6f);
  Material_t m3 = (Material_t){0};
  m3.type = DIFF_GLOSSY | REFLECT | REFRACT;
  m3.pattern_type = PLAIN;
  m3.ior = 1.12f;
  m3.specular_exp = 55.0f;
  m3.d_col   = mul_v3_f(obj_col_3, 0.2f);
  m3.e_col   = mul_v3_f(obj_col_3, 0.0f);
  m3.rfl_col = mul_v3_f(obj_col_3, 1.0f);
  m3.rfr_col = mul_v3_f(obj_col_3, 1.0f);
  m3.s_col   = mul_v3_f(obj_col_3, 0.2f);


  int Nl = 1;
  light_t **lights = (light_t **)malloc(sizeof(light_t *)*Nl);
  for (int i=0; i<Nl; i++) lights[i] = (light_t *)malloc(sizeof(light_t) * 1);

  *lights[0] = (light_t){
    .type = DIRECT,
    .direction = normalize_v3(v3f(0.0f, 0.4f, -1.0f)),
    .intensity = v3f_s(1.0f),//v3f(0.3f,0.3f,0.3f),
    .position = v3f(0, 0, 100),
    .kc = 1.0f,
    .kl = 0.0f,
    .kq = 0.0f,
    .kp = 5.0f,
  };
/*
  *lights[1] = (light_t){
    .type = POINT,
    .direction = normalize_v3(v3f(0.0f, -0.4f, -1.0f)),
    .intensity = v3f(0.0f,0.0f,1.0f),
    .position = v3f(0, 2, 10),
    .kc = 1.0f,
    .kl = 0.0f,
    .kq = 0.01f,
    .kp = 25.0f,
  };

  *lights[2] = (light_t){
    .type = POINT,
    .direction = normalize_v3(v3f(0.2f, -0.4f, -1.0f)),
    .intensity = v3f(0.0f,1.0f,0.0f),
    .position = v3f(0, 4, 10),
    .kc = 1.0f,
    .kl = 0.0f,
    .kq = 0.01f,
    .kp = 25.0f
  };
*/
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
      .center = v3f(7,0,2),
      .radius = 1.0f,
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

/*
  for (int i=1; i < No; i++) {
    *objects[i] = (object_t) {
      .o_sphr = (sphere_t) {
        .type = SPHERE,
        .material = &m2,
        .center = v3f(frand_range(-20.0f, -20.0f), frand_range(-20.0f, 20.0f), frand_range(3.0f, 10.0f)),
        .radius = frand_range(1, 3),
      }
  };
  }
*/

  V3f_t *pixels = (V3f_t *)malloc(options.width * options.height * sizeof(V3f_t));

  /* show picture flie*/
/*
  render(&options, &cam, pixels, objects, No, lights, Nl);
  pixels2file(&options, pixels);
*/

  /* ASCII animation */
  double dt;
  double fps = 24.0;

  cTimer_t timer;
  cTimer_init(&timer);

  // cKeyboard_t kb;
  // cKeyboard_init(&kb);

  double mov_spd = 3;
  double rot_spd = M_PI * 0.5;

  double min_dt = 1.0/fps;
  int running = 1;
  init_screen(&options);

  while (running) {
    /*cur_time = clock();
    dt = (cur_time - prev_time) * 1.0 / CLOCKS_PER_SEC;
    if (dt < min_dt) continue;*/
    dt = cTimer_elapsed(&timer, 1);

    // if (cKeyboard_getKeyState(&kb, KEY_U)) { cam.rotation.y += dt * rot_spd; }
    // if (cKeyboard_getKeyState(&kb, KEY_J)) { cam.rotation.y -= dt * rot_spd; }
    // if (cKeyboard_getKeyState(&kb, KEY_H)) { cam.rotation.x += dt * rot_spd; }
    // if (cKeyboard_getKeyState(&kb, KEY_K)) { cam.rotation.x -= dt * rot_spd; }

    // if (cKeyboard_getKeyState(&kb, KEY_Q)) { running = 0; }
/*
    if (cKeyboard_getKeyState(&kb, KEY_W)) { cam.position = sum_v3(cam.position, mul_v3_f(cam.fwd, dt * mov_spd)); }
    if (cKeyboard_getKeyState(&kb, KEY_S)) { cam.position = sum_v3(cam.position, mul_v3_f(cam.fwd, -dt * mov_spd)); }
    if (cKeyboard_getKeyState(&kb, KEY_A)) { cam.position = sum_v3(cam.position, mul_v3_f(cam.rgt, -dt * mov_spd)); }
    if (cKeyboard_getKeyState(&kb, KEY_D)) { cam.position = sum_v3(cam.position, mul_v3_f(cam.rgt, dt * mov_spd)); }
*/
    set_direction(&cam);

    render(&options, &cam, pixels, objects, No, lights, Nl);
    print_screen(&options, pixels);

  }

  shut_down();
  
  // cKeyboard_shutdown(&kb);

  for (int i=0; i<Nl; i++) free(lights[i]);
  free(lights);

  for (int i=0; i<No; i++) free(objects[i]);
  free(objects);

  return;
}

void test_matrix(void) {
M44d_t s = m44d(    0.707107,  0,        -0.707107, 0,
                    -0.331295, 0.883452, -0.331295, 0,
                    0.624695,  0.468521, 0.624695,  0,
                    4.000574,  3.00043,  4.000574,  1);
  show_m44d(&s);
  M44d_t res = inv_mat44d(s);
  show_m44d(&res);

  return;
}

int main(void) {
  test_whitted();
  return 0;
}
