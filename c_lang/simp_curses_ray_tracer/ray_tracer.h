#ifndef RAY_CASTER
#define RAY_CASTER
#include <stdlib.h>

#include "utils.h"
#include "object.h"
#include "camera.h"

V3f_t trace(ray_t *ray, int depth);
V3f_t* render(const int image_width,
              const int image_height,
              camera_t* camera,
              V3f_t* pixels,
              object_t** objs,
              const int objs_size);

#endif /* RAY_CASTER */
