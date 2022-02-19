#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"
#include "light_utils.h"

/* Camera config structure */
typedef struct {
	V3f_t position;
	V3f_t rotation;
	M44f_t c2w;
	float fov;
} camera_t;

/* returns ray from camera */
void get_ray(camera_t *cam, float inv_w, float inv_h, float asp_ratio, float char_ratio, int x, int y, ray_t *ray);
/* Get camera to world transf matrix*/
M44f_t get_cam2w_mat44f(camera_t *cam);
#endif
