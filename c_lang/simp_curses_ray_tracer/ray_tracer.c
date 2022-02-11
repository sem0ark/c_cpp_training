#include <stddef.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"
#include "light_utils.h"
#include "object.h"
#include "camera.h"

#define MAX_RAY_DEPTH 3
// TODO: delete after testing
#include <stdio.h>

const float bias = 1e-4;
V3f_t trace(ray_t *ray, int depth, object_t** objects, int objects_num) {
	object_t* b_object = NULL;
	float minDist = INFINITY;
	float dist = INFINITY;

	for (int k=0; k<objects_num; k++) {
		/*printf("%d ", objects[k]->com.type);
		sv(&ray->origin);
		printf("%s\n", repr_v3(objects[k]->com.surface_color));*/
		if (intersect(objects[k], ray, &dist)) {
			if (dist < minDist) {
				b_object = objects[k];
				minDist = dist;
			}
		}
	}

	if (b_object == NULL) return (V3f_t){0.4,0.4,0.4};

	V3f_t p_hit = sum_v3(ray->origin, mul_v3_f(ray->direction, minDist));
	V3f_t n_hit = compute_normal(b_object, &p_hit);
	V3f_t surf_color = (V3f_t){0};
	int inside = 0;
	if (dot_v3(ray->direction, n_hit) > 0) {
		n_hit = neg_v3(n_hit);
		inside = 1;
	}
	if ((b_object->com.reflection > 0 || b_object->com.transparency > 0) \
			&& depth < MAX_RAY_DEPTH) {

		float facing_ratio = -dot_v3(ray->direction, n_hit);

		float frensel_effect = mix(pow(1 - facing_ratio, 3), 1, 0.3);

		ray_t refl_ray = (ray_t) {
				sum_v3(p_hit, mul_v3_f(n_hit, bias)),
				reflect(ray->direction, n_hit)};

		V3f_t reflection = trace(&refl_ray, depth+1, objects, objects_num);
		V3f_t refraction = (V3f_t){0};

		// TODO: understand what is it ?!
		if (b_object->com.transparency > 0) {
			float ior = 1.52; //  (index of refraction?)
			float eta = (inside) ? ior : 1 / ior; // Are we inside of object?
			ray_t refr_ray = (ray_t){
					diff_v3(p_hit, mul_v3_f(n_hit, bias)),
					refract(ray, &n_hit, eta)};

			refraction = trace(&refr_ray, depth + 1, objects, objects_num);
		}

		surf_color = mul_v3_v(
				sum_v3(
					mul_v3_f(reflection, frensel_effect * b_object->com.reflection),
					mul_v3_f(refraction, (1-frensel_effect) * b_object->com.transparency)),
				b_object->com.surface_color);

	}
	for (int i=0; i < objects_num; i++) {
		if (len_sq_v3(objects[i]->com.emission_color) > 0) {
			V3f_t transmission = {1, 1, 1};
			ray_t emission_ray = (ray_t) {p_hit,
				normalize_v3(diff_v3(objects[i]->com.center, p_hit))};

				if (dot_v3(n_hit, emission_ray.direction) <= 0) continue;

			float t0 = INFINITY;
			for (int j=0; j < objects_num; j++) {
				if (i == j) continue;
				if (intersect(objects[j], &emission_ray, &t0)) {
					transmission = (V3f_t){0};
					break;
				}
			}
			surf_color = sum_v3(surf_color,
					mul_v3_v(
						mul_v3_f(
							mul_v3_v(b_object->com.surface_color, transmission),
							dot_v3(n_hit, emission_ray.direction)
								* (1 - (b_object->com.transparency + b_object->com.reflection))),
						objects[i]->com.emission_color)
					);
		}
	}
	return clamp_v3(sum_v3(surf_color, b_object->com.emission_color), 0.0f, 1.0f);
}



// finish render function
V3f_t* render(const unsigned int image_width,
								 const unsigned int image_height,
								 camera_t *camera,
								 V3f_t* pixels,
								 object_t** objs,
								 const int objs_size) {

	ray_t prim_ray;
	float inv_w=1/(float)image_width, inv_h=1/(float)image_height;
	unsigned int c = 0;
	for (int j=0; j<image_height; j++) {
		for (int i=0; i<image_width; i++) {
			get_ray(camera, inv_w, inv_h, i, j, &prim_ray);
			pixels[c] = trace(&prim_ray, 0, objs, objs_size);
			c++;
		}
	}
	return pixels;
}

