#include "utils.h"
#include "camera.h"
#include "object.h"

#include <stdio.h>

void sv(V3f_t *a) {
	printf("%s\n", repr_v3(*a));
}

void test_vectors(void) {
	// testing vectors
	V3f_t a = v3f(1, 2, 3);
	V3f_t b = v3f(3, -4, 0.5);
	printf("%s\n", repr_v3(mul_v3_f(a, 10)));
	printf("%s\n", repr_v3(mul_v3_f(a, 0.1)));
	printf("%s\n", repr_v3(mul_v3_f(a, -1)));

	printf("%s\n", repr_v3(mul_v3_v(a, b)));

	printf("%s\n", repr_v3(sum_v3(a, b)));
	printf("%s\n", repr_v3(diff_v3(a, b)));

	printf("%f\n", dot_v3(a, b));
	printf("%f\n", len_sq_v3(a));
	printf("%f\n", len_v3(a));
}

void test_camera(void) {
	int w=5, h=3;
	camera_t cam = {
		v3f(1, 4, 3),
		v3f(0,0,0),
		30
	};

	ray_t cur_ray;

	sv(&cam.positon);
	sv(&cam.rotation);
	printf("%f\n", cam.fov);

	for (int j=0; j<h; j++){
		for (int i=0; i<w; i++) {
			get_ray(&cam, 1/(float)w, 1/(float)h, i, j, &cur_ray);
			printf("%d %d | %s \n", i, j, repr_v3(cur_ray.direction));
		}
	}
}

void test_object() {
	ray_t ray = {
		v3f(10,0,0),
		v3f(-1,0,0)
	};
	object_t sphere = {
		.o_sphr = {
			SPHERE,
			v3f(1,1,1),
			v3f(0.1,0.1,0.1),
			v3f(0,0,0),
			0.1,
			0.1,
			1
		}
	};
}


int main(void) {
	test_vectors();
//	test_camera();
	return 0;
}
