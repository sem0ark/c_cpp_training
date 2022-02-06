#include "utils.h"
#include "camera.h"
#include "object.h"
#include "ray_tracer.h"

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
}

void makeppm(V3f_t* pixels, int w, int h){
	FILE *fp;
	char *ppm = (char*)malloc(sizeof(char) * w * h);
	fp = fopen("test1.ppm", "w");
	fprintf(fp, "P6 %d %d %d\n",  w, h, 255);
	for (int c=0; c<w*h; c++) {
	fprintf(fp, "%c%c%c", (char)(pixels[c].x*255.0),
			(char)(pixels[c].y*255.0), (char)(pixels[c].z*255.0));
	}
	fclose(fp);
	free(ppm);
}

void test_print(int w, int h, V3f_t* pixels) {
	makeppm(pixels, w, h);
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
void test_raytracer(void) {
	int w=320, h=240;
	camera_t cam = {
		v3f(0, 0, 9),
		v3f(0,0,0),
		30
	};
	int N = 4;
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
			0.9,
			1
		}
	};
	*objects[1] = (object_t){
		.o_sphr = {
			SPHERE,
			v3f(1,1,1),
			v3f(0,0,0),
			v3f(0.8,0,2),
			1,
			0.2,
			1
		}
	};

	*objects[2] = (object_t){
		.o_sphr = {
			SPHERE,
			v3f(1,0.6,1),
			v3f(0,0,0),
			v3f(-1.5,0.5,1.5),
			0,
			0.2,
			1
		}
	};

	*objects[3] = (object_t){
		.o_sphr = {
			SPHERE,
			v3f(1,1,1),
			v3f(1,1,1),
			v3f(0,-110,0),
			0,
			0,
			100
		}
	};

	V3f_t *pixels = (V3f_t *)malloc(h * w * sizeof(V3f_t));
	render(w, h, &cam, pixels, objects, N);
	printf("Picture\n");
	/*for (int i=0; i<w*h; i++) {
		sv(&pixels[i]);
	}*/

	test_print(w, h, pixels);

	for (int i=0; i<N; i++) {
		free(objects[i]);
	}
	free(objects);
	free(pixels);

	return;
}

int main(void) {
//	test_vectors();
//	test_camera();
//	test_object();
	test_raytracer();
	return 0;
}
