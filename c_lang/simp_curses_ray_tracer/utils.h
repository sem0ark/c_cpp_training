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
} t_vec3f;

/* compound struct type Ray */
typedef struct {
	t_vec3f origin;
	t_vec3f direction;
	t_vec3f color;
} t_ray;



/* Sum of two vectors (a+b) */
t_vec3f sum_vec3f(t_vec3f a, t_vec3f b);
/* Substraction between two vectors (a-b) */
t_vec3f diff_vec3f(t_vec3f a, t_vec3f b);

/* Mult vector by scalar (a*f) */
t_vec3f mul_vec3f_f(t_vec3f a, float f);
/* Mult vector coord by diff values <ax*bx, ay*by, az*bz> */
t_vec3f mul_vec3f_v(t_vec3f a, t_vec3f b);
/* Mult vector by -1 (-a) */
t_vec3f neg_vec3f(t_vec3f a);
/* Changes length of vector to 1 */
t_vec3f normalize_vec3f(t_vec3f a);
/* Mixes to values */
float mix(float a, float b, float mix);

/* Dot product of two vectors (a . b) */
float dot_vec3f(t_vec3f a, t_vec3f b);
/* Sqare length of vector (|a|^2) */
float len_sq_vec3f(t_vec3f a);
/* Length of vector (|a|) */
float len_vec3f(t_vec3f a);
/* Return string repr of vector (for debug) */
char *repr_vec3f(t_vec3f a);
/* Calculate direction vector of reflection */
t_vec3f reflect(t_vec3f ray_dir, t_vec3f norm);
/* Calculate direction vector of refraction */
t_vec3f refract(t_vec3f ray_dir, t_vec3f norm, float eta);

#endif /* UTILS_H */

