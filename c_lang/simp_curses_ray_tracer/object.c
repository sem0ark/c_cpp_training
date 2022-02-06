#include <math.h>

#include "utils.h"
#include "object.h"



int intersect_sphere(object_t *obj, ray_t *ray, float *intsct_coef) {
	V3f_t l = diff_v3(obj->o_sphr.center, ray->origin);
	float tca = dot_v3(l, ray->direction);
	if (tca < 0) return 0;
	float d2 = len_sq_v3(l) - tca*tca;
	float r2 = obj->o_sphr.radius * obj->o_sphr.radius;
	if (d2 > r2) return 0;
	float thc = sqrt(r2 - d2);
	float t = 0;
	if (tca > thc) { *intsct_coef = tca - thc; }
	else 					 { *intsct_coef = tca + thc; }
	return 1;
}


/* Not implemented */
int intersect_cube(object_t *obj, ray_t *ray, float *intsct_coef) {return 0;}

/* Not implemented */
int intersect_torus(object_t *obj, ray_t *ray, float *intsct_coef) {return 0;}



int intersect(object_t *obj, ray_t *ray, float *intsct_coef) {
	switch (obj->com.type) {
		case SPHERE:
			return intersect_sphere(obj, ray, intsct_coef);
		case CUBE:
			return  intersect_cube(obj, ray, intsct_coef);
		case TORUS:
			return intersect_torus(obj, ray, intsct_coef);
		default:
			return 0;
	};
}


V3f_t compute_normal_sphere(object_t *obj, V3f_t *p_hit) {
	return (V3f_t){0};
}

V3f_t compute_normal_cube(object_t *obj, V3f_t *p_hit) {
	return (V3f_t){0};
}

V3f_t compute_normal_torus(object_t *obj, V3f_t *p_hit) {
	return (V3f_t){0};
}



V3f_t compute_normal(object_t *obj, V3f_t *p_hit) {
	switch (obj->com.type) {
		case SPHERE:
			return compute_normal_sphere(obj, p_hit);
		case CUBE:
			return  compute_normal_cube(obj, p_hit);
		case TORUS:
			return compute_normal_torus(obj, p_hit);
		default:
			return (V3f_t){0};
	};
}



