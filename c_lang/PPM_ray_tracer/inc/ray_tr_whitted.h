#ifndef RAY_TRACER_WHITTED_ALGO
#define RAY_TRACER_WHITTED_ALGO

#include "light_utils.h"
#include "utils.h"
#include "object.h"
#include "camera.h"

void render(options_t *options, camera_t *camera, V3f_t *pixels,
            object_t **objects, int obj_size,
            light_t **lights, int lights_size);

#endif
