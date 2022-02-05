#include <stddef.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"
#include "object.h"

#define MAX_RAY_DEPTH 3

t_object** objects;
int objects_num;

const float bias = 1e-4;

t_vec3f trace(t_ray *ray, int depth) {
	t_object* b_object = NULL;
	float minDist = INFINITY;
	float dist = INFINITY;

	for (int k=0; k<objects_num; k++) {
		if (intersect(objects[k], ray, &dist)) {
			if (dist < minDist) {
				b_object = objects[k];
				minDist = dist;
			}
		}
	}

	if (b_object == NULL) return (t_vec3f){0};

	t_vec3f p_hit = sum_vec3f(ray->origin, mul_vec3f_f(ray->direction, minDist));
	t_vec3f n_hit = compute_normal(b_object, &p_hit);
	t_vec3f surf_color = (t_vec3f){2.0, 2.0, 2.0};
	int inside = 0;
	if (dot_vec3f(ray->direction, n_hit) > 0) {
		n_hit = neg_vec3f(n_hit);
		inside = 1;
	}
	if ((b_object->com.reflection > 0 || b_object->com.transparency > 0) && depth < MAX_RAY_DEPTH) {
		float facing_ratio = -dot_vec3f(ray->direction, n_hit);

		float frensel_effect = mix(pow(1 - facing_ratio, 3), 1, 0.1);
		t_ray refl_ray = (t_ray) {
				sum_vec3f(p_hit, mul_vec3f_f(n_hit, bias)),
				reflect(ray->direction, n_hit),
				ray->color};

		t_vec3f reflection = trace(&refl_ray, depth+1);
		t_vec3f refraction = (t_vec3f){0};

		// TODO: understand what is it!
		if (b_object->com.transparency) {
			float ior = 1.1; //  (index of refraction?)
			float eta = (inside) ? ior : 1 / ior; // Are we inside of object?
			t_ray refr_ray = (t_ray){
					diff_vec3f(p_hit, mul_vec3f_f(n_hit, bias)),
					refract(ray->direction, n_hit, eta),
					ray->color};

			refraction = trace(&refr_ray, depth + 1);
		}

		surf_color = mul_vec3f_v(
				sum_vec3f(
					mul_vec3f_f(reflection, frensel_effect),
					mul_vec3f_f(refraction,
						(1-frensel_effect) * b_object->com.transparency)),
				b_object->com.surface_color);

	} else {
		/* Object is completely diffuse no need to retrace further */
		for (int i=0; i < objects_num; i++) {
			if (len_sq_vec3f(objects[i]->com.emission_color) > 0) {
				t_vec3f transmission = {1, 1, 1};
				t_ray emission_ray = (t_ray) {p_hit,
					normalize_vec3f(
							diff_vec3f(objects[i]->com.center, p_hit)),
					(t_vec3f){0}
				};

				if (dot_vec3f(n_hit, emission_ray.direction) <= 0) continue;

				float t0 = INFINITY;
				for (int j=0; j < objects_num; j++) {
					if (i == j) continue;
					if (intersect(objects[j], &emission_ray, &t0)) {
						transmission = (t_vec3f){0};
						break;
					}
				}
				 // TODO: Maybe it is transmission = l_obj_em_col * i_obj_col_1 * i_obj_col_2 * ... ?

				surf_color = sum_vec3f(surf_color,
						mul_vec3f_v(
							mul_vec3f_f(
								mul_vec3f_v(
									b_object->com.surface_color,
									transmission),
								dot_vec3f(n_hit, emission_ray.direction)),
							objects[i]->com.emission_color)
						);
			}
		}
	}

	return sum_vec3f(surf_color, b_object->com.emission_color);
}

t_vec3f** trace_all(const int image_width, const int image_height) {
	t_vec3f **pixels = malloc(image_width * sizeof(t_vec3f*));
	for (int i=0; i<image_width; i++) {
		pixels[i] = malloc(image_height * sizeof(t_vec3f));
	}

	for (int j=0; j<image_height; j++) {
		for (int i=0; i<image_width; i++) {
			t_ray prim_ray;
//			compute_prim_ray(i, j, &prim_ray);
			pixels[i][j] = trace(&prim_ray, 0);
		}
	}

	return NULL;
}

