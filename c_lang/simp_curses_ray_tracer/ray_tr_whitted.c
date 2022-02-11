#include <stddef.h>

#include "light_utils.h"
#include "utils.h"
#include "object.h"
#include "camera.h"
#include "material.h"

int trace(ray_t *ray,    object_t **objects, int obj_size,
					float *t_near, int *index,
					V2f_t *uv,     object_t **hit_object) {
	*hit_object = NULL;
	for (int k=0; k < obj_size; k++) {
		float t_nearK = INFINITY;
		int indexK;
		V2f_t uvK;
		if (intersect(objects[k], ray, &t_nearK, &indexK, &uvK) && t_nearK < *t_near) {
			*hit_object = objects[k];
			*t_near = t_nearK;
			*index = indexK;
			*uv = uvK;
		}
	}
	return (*hit_object != NULL);
}

V3f_t cast_ray(
			ray_t *ray,       object_t **objects, int obj_size,
			light_t **lights, int lights_size,    options_t *options, int depth)
{

	if (depth > options->max_depth) {
		return options->background_color;
	}

	V3f_t hit_color = options->background_color;

	float	t_near = INFINITY;
	V2f_t uv;
	int	index = 0;
	object_t *hit_object = NULL;

	if (trace(ray, objects, obj_size, &t_near, &index, &uv, &hit_object)) {
		V3f_t hit_point = sum_v3(ray->origin, mul_v3_f(ray->direction, t_near));
		V3f_t norm; // normal
		V2f_t st; 	// ST coord

		get_surf_properties(hit_object, &hit_point, &ray->direction, &index, &uv, &norm, &st);

		V3f_t refr_color, refl_color, obj_lighted_color;

		if (hit_object->com.material->type & REFRACT) {
			ray_t refr_ray;

			refr_ray.direction = normalize_v3(refract(&ray->direction, &norm, hit_object->com.material->ior));

			refr_ray.origin = (dot_v3(refr_ray.direction, norm) < 0) ?
				sum_v3(hit_point, mul_v3_f(norm, options->bias)) :
				sum_v3(hit_point, mul_v3_f(norm, -options->bias));

			refr_color = cast_ray(&refr_ray, objects, obj_size, lights, lights_size, options, depth+1);
		}

		if (hit_object->com.material->type & REFLECT) {
			ray_t refl_ray;
			refl_ray.direction = normalize_v3(reflect(&ray->direction, &norm));

			refl_ray.origin = (dot_v3(refl_ray.direction, norm) < 0) ?
				sum_v3(hit_point, mul_v3_f(norm, options->bias)) :
				sum_v3(hit_point, mul_v3_f(norm, -options->bias));

			refl_color = cast_ray(&refl_ray, objects, obj_size, lights, lights_size, options, depth+1);
		}

		if (hit_object->com.material->type & DIFF_GLOSSY) {
			ray_t shadow_ray;
			// Using Phong illumination model
			V3f_t light_amt={0}, specular_color={0};

			shadow_ray.origin = (dot_v3(ray->direction, norm) < 0) ?
				sum_v3(hit_point, mul_v3_f(norm, options->bias)) :
				sum_v3(hit_point, mul_v3_f(norm, -options->bias));
			V3f_t V_dir = neg_v3(shadow_ray.direction);

			// loop over all lights
			for (int i=0; i<lights_size; i++) {
				shadow_ray.direction = diff_v3(lights[i]->position, hit_point);
				float light_dist2 = len_sq_v3(shadow_ray.direction);
				shadow_ray.direction = normalize_v3(shadow_ray.direction);
				float ldotn = MAX(0.0f, dot_v3(shadow_ray.direction, norm));

				V3f_t tmp = neg_v3(shadow_ray.direction);

				object_t *shadow_obj = NULL;
				float t_near_shadow = INFINITY;
				int in_shadow = trace(&shadow_ray, objects, obj_size,
																&t_near_shadow, &index, &uv, &shadow_obj) &&
														t_near_shadow*t_near_shadow < light_dist2;
				light_amt = sum_v3(light_amt, mul_v3_f(lights[i]->intensity, (1-in_shadow)*ldotn));
				V3f_t refl_dir = reflect(&tmp, &norm);
				}
			}
	}

	return hit_color;
}

void render(options_t *options, camera_t *camera, V3f_t *pixels,
						object_t **objects, int obj_size,
						light_t **lights, int lights_size)
{
	V3f_t *pix = pixels;
	float inv_h = 1 / (float) options->height;
	float inv_w = 1 / (float) options->width;
	float img_asp_ratio = options->width * inv_h;
	ray_t prime_ray;
	prime_ray.origin = camera->positon;

	for (int j=0; j<options->height; j++) {
		for (int i=0; i<options->width; i++) {
			get_ray(camera, inv_w, inv_h, img_asp_ratio, i, j, &prime_ray);
			*(pix++) = cast_ray(&prime_ray, objects, obj_size, lights, lights_size, options, 0);
		}
	}
}
