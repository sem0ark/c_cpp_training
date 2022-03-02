#include <stdio.h>

#include "ray_tracer.h"
#include "camera.h"
#include "utils.h"
#include "object.h"




object_t o_sphere(V3f_t sr_col, V3f_t em_col, V3f_t c, float trp, float rfl, float r) {
  object_t obj = {.o_sphr = (sphere_t) {
        SPHERE,
        sr_col,
        em_col,
        c, trp, rfl, r
  }};
  return obj;
}

/*
int main(void) {
  int N = 1;
  object_t **objects = (object_t**)malloc(sizeof(object_t*) * 3);
  for (int i=0; i<N; i++) {
    objects[i] = (object_t*)malloc(sizeof(object_t) * 1);
  }

  *objects[0] = o_sphere(v3f(0,0,1),v3f(0,1,0), v3f(0,0,10), 0.0, 0.0, 10);

  const int w = 3;
  const int h = 3;

  camera_t cam = {v3f(0,0,10), v3f(0,0,0), 30};

  V3f_t** res_pic = render(w, h, cam, objects, N);
  res_pic[0][0] = v3f(1,0.3,0.5);
  for (int j=0; j<h; j++) {
    for (int i=0; i<w; i++) {
      printf("%s\n", repr_vec3f(res_pic[i][j]));
    }
  }
  return 0;
} */
