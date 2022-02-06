#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "utils.h"


V3f_t v3f(float x, float y, float z) {
	return (V3f_t) {x, y, z};
}

V3f_t sum_v3(V3f_t a, V3f_t b) {
	return (V3f_t){a.x+b.x, a.y+b.y, a.z+b.z};
}

V3f_t diff_v3(V3f_t a, V3f_t b) {
	return (V3f_t){a.x-b.x, a.y-b.y, a.z-b.z};
}

V3f_t mul_v3_f(V3f_t a, float f) {
	 return (V3f_t){a.x*f, a.y*f, a.z*f};
}

V3f_t mul_v3_v(V3f_t a, V3f_t b) {
	 return (V3f_t){a.x*b.x, a.y*b.y, a.z*b.z};
}

V3f_t neg_v3(V3f_t a) {
	return (V3f_t){-a.x, -a.y, -a.z};
}

V3f_t normalize_v3(V3f_t a) {
	return mul_v3_f(a, 1/len_v3(a));
}

float dot_v3(V3f_t a, V3f_t b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

float len_sq_v3(V3f_t a) {
	return a.x*a.x + a.y*a.y + a.z*a.z;
}

float len_v3(V3f_t a) {
	return sqrt(len_sq_v3(a));
}

char repr_res[50];
char *repr_v3(V3f_t a) {
	sprintf(repr_res, "%.6f %.6f %.6f", a.x, a.y, a.z);
	return repr_res;
}

float mix(float a, float b, float mix) {
	return b*mix + a*(1-mix);
}

V3f_t reflect(V3f_t ray_dir, V3f_t norm) {
	return normalize_v3(diff_v3(ray_dir, mul_v3_f(norm, dot_v3(ray_dir, norm)*2)));
}

V3f_t refract(V3f_t ray_dir, V3f_t norm, float eta) {
	float cosi = -dot_v3(norm, ray_dir);
	float k = 1 - eta * eta * (1 - cosi*cosi);
	return normalize_v3(sum_v3(
				mul_v3_f(ray_dir, eta),
				mul_v3_f(norm, eta*cosi-sqrt(k))));
}

void sv(V3f_t *a) {
	printf("%s\n", repr_v3(*a));
}
