#include "material.h"
#include "utils.h"
#include "camera.h"
#include "object.h"
#include "ray_tr_whitted.h"
#include "light_utils.h"
#include "screen.h"

#include <stdio.h>
#include <stdlib.h>



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
/*
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
	return;
}

void test_object(void) {
	ray_t ray = {
		v3f(10,0.9999,0),
		normalize_v3(v3f(-1,0,0))
	};
	object_t sphere = {
		.o_sphr = {
			.type = SPHERE,
			.surface_color = v3f(1.0f,0.0f,1.0f),
			.emission_color = v3f(0.1f,0.1f,0.1f),
			.center = v3f(0.0f,0.1f,0.0f),
			.transparency = 0.1f,
			.reflection = 0.1f,
			.radius = 1.0f
		}
	};
	float coef = 0;
	int res = intersect(&sphere, &ray, &coef);
	printf("%d %f\n", res, coef);
	V3f_t p_hit = sum_v3(ray.origin, mul_v3_f(ray.direction, coef));
	sv(&p_hit);
	V3f_t norm = compute_normal(&sphere, &p_hit);
	sv(&norm);
	V3f_t refl = reflect(ray.direction, norm);
	sv(&refl);
	return;
} */

void test_print(int w, int h, V3f_t* pixels) {
//	pixels2file(pixels, w, h);
	/*for (int j=0; j<h; j++) {
		for (int i=0; i<w; i++) {
			float t = len_v3(pixels[w*j+i]);
			if (t >= 0.4) {
				printf("0");
			} else if (t > 0){
				printf(".");
			} else {
				printf(" ");
			}
		}
		printf("\n");
		fflush(stdout);
	}*/
}

void test_raytracer(void) {/*
	int w=600, h=600;
	camera_t cam = {
		v3f(-0.25, 0, 12),
		v3f(0,0,0),
		30
	};
	int N = 5;
	object_t** objects = (object_t **) malloc(sizeof(object_t*)*N);
	for (int i=0; i<N; i++) {
		objects[i] = (object_t *) malloc(sizeof(object_t));
	}

	*objects[0] = (object_t){
		.o_sphr = {
			SPHERE,
			v3f(0.3,0.9,0.7),
			v3f(0,0,0),
			v3f(0,0,0),
			0,
			0.5,
			1
		}
	};

	*objects[1] = (object_t){
		.o_sphr = {
			SPHERE,
			v3f(0.9,0.9,1),
			v3f(0,0,0),
			v3f(1,-2,2),
			0.6,
			0.4,
			1
		}
	};

	*objects[2] = (object_t){
		.o_sphr = {
			SPHERE,
			v3f(1,0.6,1),
			v3f(0,0,0),
			v3f(-1.3,0.5,2),
			0.1,
			0.8,
			0.5
		}
	};

	*objects[3] = (object_t){
		.o_sphr = {
			SPHERE,
			v3f(0,0,0),
			v3f(0.5,0.5,0.5),
			v3f(9,10,4),
			0,
			0,
			3
		}
	};

	*objects[4] = (object_t){
		.o_sphr = {
			SPHERE,
			v3f(0,0,0),
			v3f(1,1,1),
			v3f(-9,10,4),
			0,
			0,
			3
		}
	};
	V3f_t *pixels = (V3f_t *)malloc(h * w * sizeof(V3f_t));
	render(w, h, &cam, pixels, objects, N);
	printf("Picture\n");
	for (int i=0; i<w*h; i++) {
		sv(&pixels[i]);
	}

	test_print(w, h, pixels);

	for (int i=0; i<N; i++) {
		free(objects[i]);
	}
	free(objects);
	free(pixels);
	*/
	return;
}

void test_whitted(void) {
	fflush(stdout);
	options_t options = (options_t) {
		.width = 200,
		.height = 200,
		.fov = 40.0f,
		.max_depth = 9,
		.background_color = v3f(0.3f, 0.7f, 0.9f),
		.bias = 1e-4,
	};

	camera_t cam = {
		v3f(0, 0, 20),
		v3f(0,0,0),
		30
	};

	Material_t m1 = (Material_t){0};
	m1.type = DIFF_GLOSSY;
	m1.pattern_type = PLAIN;
	m1.ior = 1.52f;
	m1.specular_exp = 15.0f;
	m1.d_col = m1.s_col = v3f(0.7,0.3,0.6);

	Material_t m2 = (Material_t){0};
	m2.type = DIFF_GLOSSY;
	m2.pattern_type = PLAIN;
	m2.ior = 1.9f;
	m2.specular_exp = 5.0f;
	m1.d_col = m1.s_col = v3f(0.3,0.7,0.6);

	int Nl = 1;
	light_t **lights = (light_t **)malloc(sizeof(light_t *)*Nl);
	for (int i=0; i<Nl; i++) lights[i] = (light_t *)malloc(sizeof(light_t) * 1);

	*lights[0] = (light_t){
		v3f(0, 0, -20),
		v3f(1,1,1)
	};

	int No = 1;
	object_t **objects = (object_t **)malloc(sizeof(object_t *)*No);
	for (int i=0; i<No; i++) objects[i] = (object_t *)malloc(sizeof(object_t) * 1);
/*
	*objects[1] = (object_t) {
		.o_sphr = (sphere_t) {
			.type = SPHERE,
			.material = &m1,
			.center = v3f(0,0,0),
			.radius = 1.0f,
		}
	};*/

	*objects[0] = (object_t) {
		.o_plane = (plane_t) {
			.type = PLANE,
			.material = &m2,
			.center = v3f(0,0,-10),
			.direction = v3f(0,0,-1),
		}
	};
/*
	*objects[1] = (object_t) {
		.o_sphr = (sphere_t) {
			.type = SPHERE,
			.material = &m2,
			.center = v3f(-2,1,0),
			.radius = 1.0f,
		}
	};*/
	V3f_t *pixels = (V3f_t *)malloc(options.width
								* options.height * sizeof(V3f_t));
	render(&options, &cam, pixels, objects, No, lights, Nl);
	pixels2file(&options, pixels);

	for (int i=0; i<Nl; i++) free(lights[i]);
	free(lights);

	for (int i=0; i<No; i++) free(objects[i]);
	free(objects);

	return;
}

void test_matrix(void) {
M44d_t s = m44d(    0.707107,  0,        -0.707107, 0,
									  -0.331295, 0.883452, -0.331295, 0,
									  0.624695,  0.468521, 0.624695,  0,
									  4.000574,  3.00043,  4.000574,  1);
	show_m44d(&s);
	M44d_t res = inv_mat44d(s);
	show_m44d(&res);
	return;
}

int main(void) {
//	test_vectors();
//	test_camera();
//	test_object();
//  test_raytracer();
//	test_matrix();
	test_whitted();
	return 0;
}
