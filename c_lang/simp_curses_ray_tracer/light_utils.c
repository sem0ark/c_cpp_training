#include "light_utils.h"
#include "utils.h"

void get_light_properties(light_t *lgt, V3f_t *p_hit, V3f_t *sray_dir, float *L2, float *int_coef) {
	switch (lgt->type) {
		case DIRECT: {
			*L2 = INFINITY;
			*sray_dir = neg_v3(lgt->direction);
			*int_coef = 1.0f;
			return;
		}
		case POINT: {
			*sray_dir = diff_v3(lgt->position, *p_hit);
			*L2 = len_sq_v3(*sray_dir);
			float l = sqrtf(*L2);
			*sray_dir = mul_v3_f(*sray_dir, 1/l);
			*int_coef = 1 / (lgt->kc + l * lgt->kl + *L2 * lgt->kq);
			return;
		}
		case SPOT: {
			*sray_dir = diff_v3(lgt->position, *p_hit);
			*L2 = len_sq_v3(*sray_dir);
			float l = sqrtf(*L2);
			*sray_dir = mul_v3_f(*sray_dir, 1/l);
			*int_coef = powf(MAX(-dot_v3(*sray_dir, lgt->direction), 0), lgt->kp)
										/ (lgt->kc + l * lgt->kl + *L2 * lgt->kq);
			return;
		}
		default:
			return;
	}
}

V3f_t reflect(V3f_t *dir, V3f_t *norm) {
	return normalize_v3(
			diff_v3(
				*dir,
				mul_v3_f(*norm,
					dot_v3(*dir, *norm)*2))
	);
}

V3f_t refract(V3f_t *dir, V3f_t *norm, float ior) {
	float cosi = CLAMP(dot_v3(*dir, *norm), -1, 1);
	float etai=1, etat = ior;
	V3f_t n = *norm;
	if (cosi < 0) { cosi = -cosi; } else {swapf(&etai, &etat); n = neg_v3(n); }
	float eta = etai / etat;
	float k = 1 - eta*eta*(1-cosi*cosi);
	return (k<0) ? (V3f_t){0} :
		sum_v3(mul_v3_f(*dir, eta),
				mul_v3_f(n, (eta*cosi - sqrtf(k))));
}

/* kr - reflection coef */
void fresnel(V3f_t *dir, V3f_t *norm, float ior, float *kr) {
	float cosi = CLAMP(dot_v3(*dir, *norm), -1, 1);
	float etai = 1, etat = ior;
	if (cosi > 0) { swapf(&etai, &etat); }
	// Compute sini using Shell's law
	float sint = etai/etat * sqrtf(MAX(0.0f, 1-cosi*cosi));
	if (sint >= 1) {
		*kr = 1;
	} else {
		float cost = sqrtf(MAX(0.0f, 1 - sint*sint));
		cosi = fabsf(cosi);
		float Rs = ((etat*cosi) - (etai*cost)) / ((etat*cosi) + (etai*cost));
		float Rp = ((etai*cosi) - (etat*cost)) / ((etai*cosi) + (etat*cost));
		*kr = (Rs*Rs + Rp*Rp)/2;
	}
	return;
}

