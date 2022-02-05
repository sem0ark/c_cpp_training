#include <math.h>

#include "utils.h"
#include "object.h"



int intersect_sphere(t_sphere sp, t_ray *ray, float *intsct_coef) {
	t_vec3f l = diff_vec3f(sp.center, ray->origin);
	float tca = dot_vec3f(l, ray->direction);
	if (tca < 0) return 0;
	float d2 = len_sq_vec3f(l) - tca*tca;
	float r2 = sp.radius * sp.radius;
	if (d2 > r2) return 0;
	float thc = sqrt(r2 - d2);
	float t = 0;
	if (tca > thc) { *intsct_coef = tca - thc; }
	else 					 { *intsct_coef = tca + thc; }
	return 1;
}


/* Not implemented */
int intersect_cube(t_cube cb, t_ray *ray, float *intsct_coef) {return 0;}

/* Not implemented */
int intersect_torus(t_torus tr, t_ray *ray, float *intsct_coef) {return 0;}



int intersect(t_object *obj, t_ray *ray, float *intsct_coef) {
	switch (obj->com.type) {
		case SPHERE:
			return intersect_sphere(obj->o_sphr, ray, intsct_coef);
		case CUBE:
			return  intersect_cube(obj->o_cb, ray, intsct_coef);
		case TORUS:
			return intersect_torus(obj->o_trs, ray, intsct_coef);
		default:
			return 0;
	};
}


t_vec3f compute_normal_sphere(t_sphere sp, t_vec3f *p_hit) {
	return (t_vec3f){0};
}

t_vec3f compute_normal_cube(t_cube sp, t_vec3f *p_hit) {
	return (t_vec3f){0};
}

t_vec3f compute_normal_torus(t_torus sp, t_vec3f *p_hit) {
	return (t_vec3f){0};
}



t_vec3f compute_normal(t_object *obj, t_vec3f *p_hit) {
	switch (obj->com.type) {
		case SPHERE:
			return compute_normal_sphere(obj->o_sphr, p_hit);
		case CUBE:
			return  compute_normal_cube(obj->o_cb, p_hit);
		case TORUS:
			return compute_normal_torus(obj->o_trs, p_hit);
		default:
			return (t_vec3f){0};
	};
}



