#include <math.h>

#include "utils.h"

#ifndef OBJECT_H
#define OBJECT_H

#define MIN(a, b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a > _b ? _a : _b; })
#define MAX(a, b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a < _b ? _a : _b; })

enum OBJECT_TYPE{
	SPHERE,
	CUBE,
	TORUS
};

typedef struct {
	enum OBJECT_TYPE type;

	t_vec3f surface_color;
	t_vec3f emission_color;
	t_vec3f center;

	float transparency;
	float reflection;
} t_object_common;

typedef struct {
	enum OBJECT_TYPE type;

	t_vec3f surface_color;
	t_vec3f emission_color;
	t_vec3f center;
	float transparency;
	float reflection;

	float radius;
} t_sphere;

typedef struct {
	enum OBJECT_TYPE type;
} t_cube;

typedef struct {
	enum OBJECT_TYPE type;
} t_torus;

typedef union {
	t_object_common com;
	t_sphere o_sphr;
	t_cube o_cb;
	t_torus o_trs;
} t_object;


int intersect(t_object *obj, t_ray *ray, float *intsct_coef);
t_vec3f compute_normal(t_object *obj, t_vec3f *p_hit);

#endif
