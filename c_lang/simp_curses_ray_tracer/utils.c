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
