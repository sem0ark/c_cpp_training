#ifndef LIGHT_UTILS_H
#define LIGHT_UTILS_H

#include "utils.h"

/* compound struct type Ray */
typedef struct {
	V3f_t origin;
	V3f_t direction;
} ray_t;
/* Compute reflection of ray */
V3f_t reflect(V3f_t ray_dir, V3f_t norm);
/* Comupte refraction of ray */
V3f_t refract(V3f_t ray_dir, V3f_t norm, float eta);

#endif
