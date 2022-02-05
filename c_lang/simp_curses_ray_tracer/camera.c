#include <math.h>

#include "camera.h"
#include "utils.h"
#include "ray_tracer.h"

t_ray get_ray(t_camera *cam, float inv_w, float inv_h, int x, int y) {
	float asp_ratio = inv_h / inv_w;
	float angle = tan(M_PI * 0.5 * cam->fov / 180.0);
	float xx = (2*((x+0.5)*inv_w)-1)*angle*asp_ratio;
	float yy = (1 - 2*((y+0.5)*inv_h)) * angle;
	t_vec3f ray_dir = (t_vec3f) {xx, yy, -1};
	return (t_ray) {cam->positon, normalize_vec3f(ray_dir)};
}
