#include <math.h>

#include "utils.h"
#include "light_utils.h"
#include "object.h"



int intersect_sphere(object_t *obj, ray_t *ray, float *intsct_coef) {
// geometric solution
#if 0
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
#else // analitic solution
	V3f_t L = diff_v3(ray->origin, obj->com.center);
	float a = len_sq_v3(ray->direction);
	float b = 2 * dot_v3(ray->direction, L);
	float c = len_sq_v3(L) - obj->o_sphr.radius * obj->o_sphr.radius;
	float t0, t1;
	if (!solve_quadratic(a,b,c,&t0,&t1)) return 0;
	if (t0<0) t0=t1;
	if (t0<0) return 0;
	*intsct_coef = t0;

	return 1;
#endif
}

int intersect_plane(object_t *obj, ray_t *ray, float *intsct_coef) {
	float den = fabsf(dot_v3(obj->o_plane.direction, ray->direction));
	if (den > 1e-6){
		*intsct_coef = dot_v3(
				diff_v3(obj->o_plane.center, ray->origin),
				obj->o_plane.direction) / den;
		return (*intsct_coef>=0);
	}
	return 0;
}

/* Not implemented */
int intersect_cube(object_t *obj, ray_t *ray, float *intsct_coef) {return 0;}

/* Not implemented */
int intersect_torus(object_t *obj, ray_t *ray, float *intsct_coef) {return 0;}



int intersect(object_t *obj, ray_t *ray, float *intsct_coef, int *index, V2f_t *uv) {
	switch (obj->com.type) {
		case SPHERE:
			return intersect_sphere(obj, ray, intsct_coef);
		case PLANE:
			return intersect_plane(obj, ray, intsct_coef);
		case CUBE:
			return  intersect_cube(obj, ray, intsct_coef);
		case TORUS:
			return intersect_torus(obj, ray, intsct_coef);
		default:
			return 0;
	};
}

/*
V3f_t compute_normal_sphere(object_t *obj, V3f_t *p_hit) {
	return normalize_v3(diff_v3(*p_hit, obj->o_sphr.center));
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
} */


void get_surf_properties_shpr(object_t *obj, V3f_t *p_hit, V3f_t *dir, int *index, V2f_t *uv, V3f_t *N, V2f_t *st) {
	*N = diff_v3(*p_hit, obj->o_sphr.center);
	return;
}

void get_surf_properties_pln(object_t *obj, V3f_t *p_hit, V3f_t *dir, int *index, V2f_t *uv, V3f_t *N, V2f_t *st) {
	*N = obj->o_plane.direction;
	st->x = fmodf(p_hit->x - obj->com.center.x, 1);
	st->y = fmodf(p_hit->y - obj->com.center.y, 1);
	return;
}

void get_surf_properties_cb(object_t *obj, V3f_t *p_hit, V3f_t *dir, int *index, V2f_t *uv, V3f_t *N, V2f_t *st) {
	return;
}

void get_surf_properties_trs(object_t *obj, V3f_t *p_hit, V3f_t *dir, int *index, V2f_t *uv, V3f_t *N, V2f_t *st) {
	return;
}

void get_surf_properties(object_t *obj, V3f_t *p_hit, V3f_t *dir, int *index, V2f_t *uv, V3f_t *N, V2f_t *st) {
	switch (obj->com.type) {
		case SPHERE:
			get_surf_properties_shpr(obj, p_hit, dir, index, uv, N, st);
			break;
		case PLANE:
			get_surf_properties_shpr(obj, p_hit, dir, index, uv, N, st);
			break;
		case CUBE:
			get_surf_properties_cb(obj, p_hit, dir, index, uv, N, st);
			break;
		case TORUS:
			get_surf_properties_trs(obj, p_hit, dir, index, uv, N, st);
			break;
		default:
			return;
	};
}
