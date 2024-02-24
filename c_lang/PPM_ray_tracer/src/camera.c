#include <math.h>

#include "camera.h"
#include "utils.h"
#include "light_utils.h"

void get_ray(camera_t *cam, float inv_w, float inv_h, float asp_ratio, float char_ratio, int x, int y, ray_t *ray) {
	float angle = tan(M_PI * 0.5 * cam->fov / 180.0);
	float xx = (2*((x+0.5)*inv_w)-1)*angle*asp_ratio * char_ratio;
	float yy = (1 - 2*((y+0.5)*inv_h)) * angle;

  ray->direction = normalize_v3(sum_v3(cam->fwd,
                      sum_v3(mul_v3_f(cam->rgt, -xx),
                          mul_v3_f(cam->up, yy))));

//  mult_dir_v3_mat44_f(&ray->direction, &cam->c2w, &ray->direction);

//  ray->direction = normalize_v3(ray->direction);
	ray->origin = cam->position;
	return;
}

void set_direction(camera_t *cam) {
  float sa = sin(cam->rotation.x);
  float ca = cos(cam->rotation.x);
  float sb = sin(cam->rotation.y);
  float cb = cos(cam->rotation.y);

  cam->fwd = v3f(ca*cb, cb*sa, sb);
  cam->rgt = v3f(-sa, ca, 0.0);
  cam->up = cross_v3(cam->fwd, cam->rgt);

  return;
}

M44f_t get_cam2w_mat44f(camera_t *cam) {
  double sa = sin(cam->rotation.x);
  double ca = cos(cam->rotation.x);
  double sb = sin(cam->rotation.y);
  double cb = cos(cam->rotation.y);

  V3d_t forward = v3d(ca*cb, cb*sa, sb);
  V3d_t right = v3d(-sa, ca, 0.0);
  V3d_t up = cross_v3d(forward, right);

  sv_d(&forward);
  sv_d(&right);
  sv_d(&up);

  M44f_t cam_to_world = (M44f_t){0};
  cam_to_world.mat[0][0] = right.x;
  cam_to_world.mat[0][1] = right.y;
  cam_to_world.mat[0][2] = right.z;
  cam_to_world.mat[1][0] = up.x;
  cam_to_world.mat[1][1] = up.y;
  cam_to_world.mat[1][2] = up.z;
  cam_to_world.mat[2][0] = forward.x;
  cam_to_world.mat[2][1] = forward.y;
  cam_to_world.mat[2][2] = forward.z;
  cam_to_world.mat[3][0] = cam->position.x;
  cam_to_world.mat[3][1] = cam->position.y;
  cam_to_world.mat[3][2] = cam->position.z;
	cam_to_world.mat[3][3] = 1.0f;

  return cam_to_world;
}

M44f_t get_lookat_mat44f(V3f_t *from, V3f_t *to) {
	V3f_t tmp = normalize_v3(v3f(1.1267f, 3.26876f, 2.72291f));
	V3f_t forward = normalize_v3(diff_v3(*from, *to));
	V3f_t right = cross_v3(tmp, forward);
	V3f_t up = cross_v3(forward, right);

	M44f_t cam_to_world = (M44f_t){0};
  cam_to_world.mat[0][0] = right.x;
  cam_to_world.mat[0][1] = right.y;
  cam_to_world.mat[0][2] = right.z;
  cam_to_world.mat[1][0] = up.x;
  cam_to_world.mat[1][1] = up.y;
  cam_to_world.mat[1][2] = up.z;
  cam_to_world.mat[2][0] = forward.x;
  cam_to_world.mat[2][1] = forward.y;
  cam_to_world.mat[2][2] = forward.z;
  cam_to_world.mat[3][0] = from->x;
  cam_to_world.mat[3][1] = from->y;
  cam_to_world.mat[3][2] = from->z;
	cam_to_world.mat[3][3] = 1.0f;
	return cam_to_world;
}

M44d_t get_lookat_mat44d(V3d_t *from, V3d_t *to) {
	V3d_t tmp = normalize_v3d(v3d(1.1267, 3.26876, 2.72291));
	V3d_t forward = normalize_v3d(diff_v3d(*from, *to));
	V3d_t right = cross_v3d(tmp, forward);
	V3d_t up = cross_v3d(forward, right);

	M44d_t cam_to_world = (M44d_t){0};
  cam_to_world.mat[0][0] = right.x;
  cam_to_world.mat[0][1] = right.y;
  cam_to_world.mat[0][2] = right.z;
  cam_to_world.mat[1][0] = up.x;
  cam_to_world.mat[1][1] = up.y;
  cam_to_world.mat[1][2] = up.z;
  cam_to_world.mat[2][0] = forward.x;
  cam_to_world.mat[2][1] = forward.y;
  cam_to_world.mat[2][2] = forward.z;
  cam_to_world.mat[3][0] = from->x;
  cam_to_world.mat[3][1] = from->y;
  cam_to_world.mat[3][2] = from->z;
	cam_to_world.mat[3][3] = 1.0;
	return cam_to_world;
}


