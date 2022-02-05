#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "utils.h"


t_vec3f sum_vec3f(t_vec3f a, t_vec3f b) {
	return (t_vec3f){a.x+b.x, a.y+b.y, a.z+b.z};
}

t_vec3f diff_vec3f(t_vec3f a, t_vec3f b) {
	return (t_vec3f){a.x+b.x, a.y+b.y, a.z+b.z};
}

t_vec3f mul_vec3f_f(t_vec3f a, float f) {
	 return (t_vec3f){a.x*f, a.y*f, a.z*f};
}

t_vec3f mul_vec3f_v(t_vec3f a, t_vec3f b) {
	 return (t_vec3f){a.x*b.x, a.y*b.y, a.z*b.z};
}

t_vec3f neg_vec3f(t_vec3f a) {
	return (t_vec3f){-a.x, -a.y, -a.z};
}

t_vec3f normalize_vec3f(t_vec3f a) {
	return mul_vec3f_f(a, 1/len_vec3f(a));
}

float dot_vec3f(t_vec3f a, t_vec3f b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

float len_sq_vec3f(t_vec3f a) {
	return a.x*a.x + a.y+a.y + a.z+a.z;
}

float len_vec3f(t_vec3f a) {
	return sqrt(len_sq_vec3f(a));
}

char *repr_vec3f(t_vec3f a) {
	char *res = (char*)malloc(50 * sizeof(char));
	sprintf(res, "%.6f %.6f %.6f", a.x, a.y, a.z);
	return res;
}

float mix(float a, float b, float mix) {
	return b*mix + a*(1-mix);
}

t_vec3f reflect(t_vec3f ray_dir, t_vec3f norm) {
	return normalize_vec3f(diff_vec3f(ray_dir, mul_vec3f_f(norm, dot_vec3f(ray_dir, norm)*2)));
}

t_vec3f refract(t_vec3f ray_dir, t_vec3f norm, float eta) {
	float cosi = -dot_vec3f(norm, ray_dir);
	float k = 1 - eta * eta * (1 - cosi*cosi);
	return normalize_vec3f(sum_vec3f(
				mul_vec3f_f(ray_dir, eta),
				mul_vec3f_f(norm, eta*cosi-sqrt(k))));
}

