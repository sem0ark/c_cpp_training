#include "utils.h"

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

