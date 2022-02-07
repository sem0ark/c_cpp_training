#include <math.h>

#ifndef UTILS_H
#define UTILS_H

/* Mth Macro */
#define MAX(a,b) \
  ({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b; })
#define MIN(a,b) \
   ({ __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#define CLAMP(a,lw,hi) \
  ({ MAX(lw, MIN(hi, a)); })

#ifndef INFINITY
#define INFINITY 1e8
#endif

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

/* Vector 3d struct float type */
typedef struct Vec3f {
	float x, y, z;
} V3f_t;

/* Vector 3d struct double type */
typedef struct Vec3d {
	double x, y, z;
} V3d_t;

/* 4x4 Matrix struct float type */
typedef struct Matrix44f {
	float mat[4][4];
} M44f_t;

/* 4x4 Matrix struct double type */
typedef struct Matrix44d {
	double mat[4][4];
} M44d_t;

/* Vector operations */

/* create vector*/
V3f_t v3f(float x, float y, float z);
V3d_t v3d(double x, double y, double z);
/* Sum of two vectors (a+b) */
V3f_t sum_v3(V3f_t a, V3f_t b);
V3d_t sum_v3d(V3d_t a, V3d_t b);
/* Substraction between two vectors (a-b) */
V3f_t diff_v3(V3f_t a, V3f_t b);
V3d_t diff_v3d(V3d_t a, V3d_t b);

/* Mult vector by scalar (a*f) */
V3f_t mul_v3_f(V3f_t a, float f);
V3d_t mul_v3d_d(V3d_t a, double f);
/* Mult vector coord by diff values <ax*bx, ay*by, az*bz> */
V3f_t mul_v3_v(V3f_t a, V3f_t b);
V3d_t mul_v3d_v(V3d_t a, V3d_t b);
/* Get vector with inverted values */
V3f_t inv_v3(V3f_t a);
V3d_t inv_v3d(V3d_t a);
/* Mult vector by -1 (-a) */
V3f_t neg_v3(V3f_t a);
V3d_t neg_v3d(V3d_t a);
/* Changes length of vector to 1 */
V3f_t normalize_v3(V3f_t a);
V3d_t normalize_v3d(V3d_t a);
/* Cross product of two vectors (a x b) */
V3f_t cross_v3(V3f_t a, V3f_t b);
V3d_t cross_v3d(V3d_t a, V3d_t b);
/* Clamps values of vector */
V3f_t clamp_v3(V3f_t a, float dw, float hi);
V3d_t clamp_v3d(V3d_t a, double dw, double hi);
/* Mixes to values */
float mix(float a, float b, float mix);

/* Dot product of two vectors (a . b) */
float dot_v3(V3f_t a, V3f_t b);
double dot_v3d(V3d_t a, V3d_t b);
/* Sqare length of vector (|a|^2) */
float len_sq_v3(V3f_t a);
double len_sq_v3d(V3d_t a);
/* Length of vector (|a|) */
float len_v3(V3f_t a);
double len_v3d(V3d_t a);
/* Return string repr of vector (for debug) */
char *repr_v3(V3f_t a);
char *repr_v3d(V3d_t a);
/* Print v3*/
void sv(V3f_t *);
void sv_d(V3d_t *);

/* Matrix operations */
/* Create Matrix 4x4 */
M44f_t m44f(float a, float b,
	float c, float d,
	float e, float f,
  float g, float h,
  float i, float j,
	float k, float l,
	float m, float n,
	float o, float p);
M44d_t m44d(double a, double b,
	double c, double d,
	double e, double f,
  double g, double h,
  double i, double j,
	double k, double l,
	double m, double n,
	double o, double p);

/* Create unit Matrix 4x4 */
M44f_t m44f_unit(void);
M44d_t m44d_unit(void);

/* Matrix 4x4 multiplication */
void mul_mat44f(M44f_t *a, M44f_t *b, M44f_t *out);
void mul_mat44d(M44d_t *a, M44d_t *b, M44d_t *out);
/* Matrix 4x4 transposition */
M44f_t tran_mat44f(M44f_t *a);
M44d_t tran_mat44d(M44d_t *a);
/* Matrix 4x4 vector multiplication with W projection */
void mult_vec_v3_mat44_f(V3f_t* src, M44f_t *m, V3f_t *dst);
void mult_vec_v3_mat44_d(V3d_t* src, M44d_t *m, V3d_t *dst);
/* Matrix 4x4 vector multiplication without W component */
void mult_dir_v3_mat44_f(V3f_t* src, M44f_t *m, V3f_t *dst);
void mult_dir_v3_mat44_d(V3d_t* src, M44d_t *m, V3d_t *dst);
/* compute inverse of matrix 4x4 */
M44f_t inv_mat44f(M44f_t t);
M44d_t inv_mat44d(M44d_t t);
/* Print out matrix 4x4 */
void show_m44f(M44f_t *a);
void show_m44d(M44d_t *a);
#endif /* UTILS_H */

