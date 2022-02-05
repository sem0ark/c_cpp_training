#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"

typedef struct {
	t_vec3f positon;
	t_vec3f rotation;
	float fov;
} t_camera;

t_ray get_ray(t_camera *cam, float inv_w, float inv_h, int x, int y);

#endif
