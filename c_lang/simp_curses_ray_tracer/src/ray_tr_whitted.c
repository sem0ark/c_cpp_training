#include <stddef.h>

#include "light_utils.h"
#include "utils.h"
#include "object.h"
#include "camera.h"
#include "material.h"

int trace(ray_t *ray,    object_t **objects, int obj_size,
          float *t_near, int *index,
          V2f_t *uv,     object_t **hit_object)
{
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
  if (depth > options->max_depth) { return options->ambient_occlusion; }

  V3f_t hit_color = (V3f_t){0};

  float t_near = INFINITY;
  V2f_t uv;
  int index = 0;
  object_t *hit_object = NULL;

  if (trace(ray, objects, obj_size, &t_near, &index, &uv, &hit_object)) {
    V3f_t hit_point = sum_v3(ray->origin, mul_v3_f(ray->direction, t_near));
    V3f_t norm; // normal
    V2f_t st;   // ST coord

    get_surf_properties(hit_object, &hit_point, &ray->direction, &index, &uv, &norm, &st);

    V3f_t refr_color, refl_color, obj_lighted_color;
    refl_color = refr_color = obj_lighted_color = (V3f_t){0};

    hit_color = sum_v3(hit_color, options->ambient_occlusion);
    hit_color = sum_v3(hit_color, hit_object->com.material->e_col);

    if (hit_object->com.material->type & REFRACT) {
      ray_t refr_ray;

      refr_ray.direction = normalize_v3(refract(&ray->direction, &norm, hit_object->com.material->ior));

      refr_ray.origin = (dot_v3(refr_ray.direction, norm) < 0) ?
        sum_v3(hit_point, mul_v3_f(norm, -options->bias)) :
        sum_v3(hit_point, mul_v3_f(norm, options->bias));

      refr_color = cast_ray(&refr_ray, objects, obj_size, lights, lights_size, options, depth+1);
    }

    if (hit_object->com.material->type & REFLECT) {
      ray_t refl_ray;
      refl_ray.direction = normalize_v3(reflect(&ray->direction, &norm));

      refl_ray.origin = (dot_v3(refl_ray.direction, norm) < 0) ?
        sum_v3(hit_point, mul_v3_f(norm, -options->bias)) :
        sum_v3(hit_point, mul_v3_f(norm, options->bias));

      refl_color = cast_ray(&refl_ray, objects, obj_size, lights, lights_size, options, depth+1);
    }

    if (hit_object->com.material->type & REFRACT) {
      float kr;
      fresnel(&ray->direction, &norm, hit_object->com.material->ior, &kr);
      hit_color = sum_v3(hit_color, sum_v3(
          mul_v3_f(mul_v3_v(refr_color, hit_object->com.material->rfr_col), (1-kr)),
          mul_v3_f(mul_v3_v(refl_color, hit_object->com.material->rfl_col), kr)));
    } else {
      hit_color = sum_v3(hit_color, mul_v3_v(refl_color, hit_object->com.material->rfl_col));
    }

    if (hit_object->com.material->type & DIFF_GLOSSY) {
      V3f_t diff_color = (V3f_t){0};
      V3f_t spec_color = (V3f_t){0};

      ray_t shadow_ray;
      float L2, int_coef;

      // Using Phong illumination model
      shadow_ray.origin = (dot_v3(ray->direction, norm) < 0) ?
        sum_v3(hit_point, mul_v3_f(norm, options->bias)) :
        sum_v3(hit_point, mul_v3_f(norm, -options->bias));

      // loop over all lights
      for (int i=0; i<lights_size; i++) {
        get_light_properties(lights[i], &hit_point,
          &shadow_ray.direction, &L2, &int_coef);
        if (int_coef < 0.001) continue;

        V3f_t H_vec = normalize_v3(diff_v3(shadow_ray.direction, ray->direction));

        object_t *shadow_obj = NULL;
        float t_nears = INFINITY;

        int in_shadow = trace(&shadow_ray, objects, obj_size,
                              &t_nears, &index, &uv, &shadow_obj)
                        && t_nears*t_nears < L2;

        float ldotn = MAX(dot_v3(shadow_ray.direction, norm), 0);

        diff_color = sum_v3(diff_color, mul_v3_f(lights[i]->intensity,
                            int_coef * ldotn * (1 - in_shadow)));

        spec_color = sum_v3(spec_color,
            mul_v3_f(lights[i]->intensity,
              powf(MAX(dot_v3(norm, H_vec), 0),
                hit_object->com.material->specular_exp)
                  * int_coef * (ldotn > 0) * (1 - in_shadow)));
      }

      obj_lighted_color = sum_v3(
          mul_v3_v(diff_color,
            mul_v3_v(hit_object->com.material->d_col,
              eval_texture_color(hit_object->com.material, &st))),
          mul_v3_v(spec_color, hit_object->com.material->s_col));
    }
    return sum_v3(hit_color, obj_lighted_color);

  } else { return options->background_color; }
}


void render(options_t *options, camera_t *camera, V3f_t *pixels,
            object_t **objects, int obj_size,
            light_t **lights, int lights_size)
{
  V3f_t *pix = pixels;
  float inv_h = 1 / (float) options->height / (float) options->aa_coef;
  float inv_w = 1 / (float) options->width  / (float) options->aa_coef;
  float img_asp_ratio = options->aa_coef * options->width * inv_h;
  ray_t prime_ray;
  prime_ray.origin = camera->position;

  V3f_t cur_color;
  for (int y=0; y<options->height; y++) {
    for (int x=0; x<options->width; x++) {
      cur_color = (V3f_t){0};

      for (int dy=0; dy<options->aa_coef; dy++) {
        for (int dx=0; dx<options->aa_coef; dx++) {
          get_ray(camera, inv_w, inv_h,
            img_asp_ratio, options->console_ch_ratio,
            x*options->aa_coef+dx - options->aa_coef/2,
            y*options->aa_coef + dy - options->aa_coef/2, &prime_ray);
          cur_color = sum_v3(
            cur_color,
            cast_ray(&prime_ray, objects, obj_size,
              lights, lights_size, options, 0));
        }
      }

      *(pix++) = mul_v3_f(cur_color, 1 / (float)(options->aa_coef * options->aa_coef));
    }
  }
}




