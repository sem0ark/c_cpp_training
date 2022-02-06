#include <math.h>

#include "camera.h"
#include "utils.h"
#include "ray_tracer.h"


void get_ray(camera_t *cam, float inv_w, float inv_h, int x, int y, ray_t *ray) {
	float asp_ratio = inv_h / inv_w;
	float angle = tan(M_PI * 0.5 * cam->fov / 180.0);
	float xx = (2*((x+0.5)*inv_w)-1)*angle*asp_ratio;
	float yy = (1 - 2*((y+0.5)*inv_h)) * angle;
	V3f_t ray_dir = (V3f_t) {xx, yy, -1};
	ray->origin = cam->positon;
	ray->direction = normalize_v3(ray_dir);
	return;
}

