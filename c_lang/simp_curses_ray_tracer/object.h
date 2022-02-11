#ifndef OBJECT_H
#define OBJECT_H

#include <math.h>

#include "utils.h"
#include "material.h"
#include "light_utils.h"

enum OBJECT_TYPE{
	SPHERE = 1,
	PLANE,
	CUBE,
	TORUS
};

typedef struct {
	enum OBJECT_TYPE type;
	Material_t *material;
	V3f_t center;
} object_common_t;

typedef struct {
	enum OBJECT_TYPE type;
	Material_t *material;
	V3f_t center;

	float radius;
} sphere_t;

typedef struct {
	enum OBJECT_TYPE type;
	Material_t *material;
	V3f_t center;

	V3f_t direction; // normal vector to plane
} plane_t;

typedef struct {
	enum OBJECT_TYPE type;
	Material_t *material;
	V3f_t center;
} cube_t;

typedef struct {
	enum OBJECT_TYPE type;
	Material_t *material;
	V3f_t center;
} torus_t;

/* compound struct for objects */
typedef union {
	object_common_t com;
	sphere_t o_sphr;
	plane_t o_plane;
	cube_t o_cb;
	torus_t o_trs;
} object_t;

/* computes intersection coef for object */
int intersect(object_t *obj, ray_t *ray, float *intsct_coef, int *index, V2f_t *uv);
/* computes normal form point on surface of object */
V3f_t compute_normal(object_t *obj, V3f_t *p_hit);
/* Get surface properties of object */
void get_surf_properties(object_t *obj, V3f_t *p_hit, V3f_t *dir, int *index, V2f_t *uv, V3f_t *N, V2f_t *st);
#endif

