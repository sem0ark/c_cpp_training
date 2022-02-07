#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"
#include "light_utils.h"

typedef struct {
	V3f_t positon;
	V3f_t rotation;
	float fov;
} camera_t;
/* returns ray from camera */
void get_ray(camera_t *cam, float inv_w, float inv_h, int x, int y, ray_t *ray);

#endif
