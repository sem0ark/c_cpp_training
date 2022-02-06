#include <math.h>

#ifndef UTILS_H
#define UTILS_H



#ifndef INFINITY
#define INFINITY 1e8
#endif

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

/* Vector 3d struct float type */
typedef struct {
	float x, y, z;
} V3f_t;

/* compound struct type Ray */
typedef struct {
	V3f_t origin;
	V3f_t direction;
} ray_t;

/* create vector*/
V3f_t v3f(float x, float y, float z);
/* Sum of two vectors (a+b) */
V3f_t sum_v3(V3f_t a, V3f_t b);
/* Substraction between two vectors (a-b) */
V3f_t diff_v3(V3f_t a, V3f_t b);

/* Mult vector by scalar (a*f) */
V3f_t mul_v3_f(V3f_t a, float f);
/* Mult vector coord by diff values <ax*bx, ay*by, az*bz> */
V3f_t mul_v3_v(V3f_t a, V3f_t b);
/* Mult vector by -1 (-a) */
V3f_t neg_v3(V3f_t a);
/* Changes length of vector to 1 */
V3f_t normalize_v3(V3f_t a);
/* Mixes to values */
float mix(float a, float b, float mix);

/* Dot product of two vectors (a . b) */
float dot_v3(V3f_t a, V3f_t b);
/* Sqare length of vector (|a|^2) */
float len_sq_v3(V3f_t a);
/* Length of vector (|a|) */
float len_v3(V3f_t a);
/* Return string repr of vector (for debug) */
char *repr_v3(V3f_t a);
/* Calculate direction vector of reflection */
V3f_t reflect(V3f_t ray_dir, V3f_t norm);
/* Calculate direction vector of refraction */
V3f_t refract(V3f_t ray_dir, V3f_t norm, float eta);

void sv(V3f_t *);

#endif /* UTILS_H */

