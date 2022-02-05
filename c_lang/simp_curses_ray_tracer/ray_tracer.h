#ifndef RAY_CASTER
#define RAY_CASTER
#include <stdlib.h>

#include "utils.h"
#include "object.h"
#include "camera.h"

t_vec3f trace(t_ray *ray, int depth);
t_vec3f** render(const int image_width,
								 const int image_height,
								 t_camera camera,
								 t_object** objs,
								 const size_t objs_size);

#endif /* RAY_CASTER */
