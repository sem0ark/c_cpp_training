#include <stddef.h>
#include <stdlib.h>

#include "utils.h"
#include "object.h"

#define MAX_RAY_DEPTH 3

t_object** const objects;
int objects_num;


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
	int inside = 0;
	if (dot_vec3f(ray->direction, n_hit) > 0) {
		n_hit = neg_vec3f(n_hit);
		inside = 1;
	}

	if ((b_object->com.reflection > 0 || b_object->com.transparency > 0) && depth < MAX_RAY_DEPTH) {
		float facing_ratio = -dot_vec3f(ray->direction, n_hit);
	} else {
		/* Object is completely diffuse */
	}

	/* t_ray shadow_ray;
	shadow_ray.direction = diff_vec3f(light_pos, p_hit);
//	int is_shadow = 0;
	for (int k=0; k<objects_num; k++) {
		if (intersect(objects[k], &shadow_ray)) {
			return 0;
		}
	} */

//	return mul_vec3f_f(object->com.surface_color, light.brightness);
	return (t_vec3f){0};
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

