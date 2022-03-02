#ifndef LIGHT_UTILS_H
#define LIGHT_UTILS_H

#include "utils.h"

enum LIGHT_TYPE {
  DIRECT,
  SPOT,
  POINT,
};

/* compound struct type Ray */
typedef struct {
  V3f_t origin;
  V3f_t direction;
} ray_t;

/* compound struct for light source */
typedef struct {
  enum LIGHT_TYPE type;
  V3f_t position;
  V3f_t intensity;
  V3f_t direction;
  float kq, kl, kc, kp;
} light_t;

/* Compute reflection of ray */
V3f_t reflect(V3f_t *dir, V3f_t *norm);

/* Comupte refraction of ray */
V3f_t refract(V3f_t *dir, V3f_t *norm, float ior);

/* Compute fresnel coef */
void fresnel(V3f_t *dir, V3f_t *norm, float ior, float *kr);

/* Get light properties */
void get_light_properties(light_t *, V3f_t *p_hit, V3f_t *shadow_ray_dir,
                          float *l_sq, float *intensity_coef);
#endif
