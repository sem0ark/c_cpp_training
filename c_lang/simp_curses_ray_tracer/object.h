#ifndef OBJECT_H
#define OBJECT_H

#include <math.h>

#include "utils.h"
#include "light_utils.h"

enum OBJECT_TYPE{
	SPHERE,
	CUBE,
	TORUS
};

typedef struct {
	enum OBJECT_TYPE type;

	V3f_t surface_color;
	V3f_t emission_color;
	V3f_t center;

	float transparency;
	float reflection;
} object_common_t;

typedef struct {
	enum OBJECT_TYPE type;

	V3f_t surface_color;
	V3f_t emission_color;
	V3f_t center;
	float transparency;
	float reflection;

	float radius;
} sphere_t;

typedef struct {
	enum OBJECT_TYPE type;
} cube_t;

typedef struct {
	enum OBJECT_TYPE type;
} torus_t;

typedef union {
	object_common_t com;
	sphere_t o_sphr;
	cube_t o_cb;
	torus_t o_trs;
} object_t;

/* computes intersection coef for object */
int intersect(object_t *obj, ray_t *ray, float *intsct_coef);
/* computes normal form point on surface of object */
V3f_t compute_normal(object_t *obj, V3f_t *p_hit);

#endif

