#ifndef LIGHT_UTILS_H
#define LIGHT_UTILS_H

#include "utils.h"

/* compound struct type Ray */
typedef struct {
	V3f_t origin;
	V3f_t direction;
} ray_t;

/* compound struct for light source */
typedef struct {
	V3f_t position;
	V3f_t intensity;
} light_t;

/* Compute reflection of ray */
V3f_t reflect(V3f_t *dir, V3f_t *norm);

/* Comupte refraction of ray */
V3f_t refract(V3f_t *dir, V3f_t *norm, float ior);

/* Compute fresnel coef */
void fresnel(V3f_t *dir, V3f_t *norm, float ior, float *kr);

#endif
