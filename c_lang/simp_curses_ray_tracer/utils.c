#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "utils.h"



/* Math functions */
float mix(float a, float b, float mix) {
	return b*mix + a*(1-mix);
}

/* V3 class */
V3f_t v3f(float x, float y, float z) { return (V3f_t) {x, y, z}; }
V3f_t sum_v3(V3f_t a, V3f_t b) { return (V3f_t){a.x+b.x, a.y+b.y, a.z+b.z}; }
V3f_t diff_v3(V3f_t a, V3f_t b) { return (V3f_t){a.x-b.x, a.y-b.y, a.z-b.z}; }
V3f_t mul_v3_f(V3f_t a, float f) { return (V3f_t){a.x*f, a.y*f, a.z*f}; }
V3f_t mul_v3_v(V3f_t a, V3f_t b) { return (V3f_t){a.x*b.x, a.y*b.y, a.z*b.z}; }
V3f_t inv_v3(V3f_t a) { return (V3f_t){1.0f/a.x, 1.0f/a.y, 1.0f/a.z}; }
V3f_t neg_v3(V3f_t a) { return (V3f_t){-a.x, -a.y, -a.z}; }
V3f_t normalize_v3(V3f_t a) { return mul_v3_f(a, 1/len_v3(a)); }
V3f_t cross_v3(V3f_t a, V3f_t b) {
    return (V3f_t){a.y*b.z-a.z*b.y, a.y*b.x-a.x*b.z, a.x*b.y-a.y*b.z};
}
V3f_t clamp_v3(V3f_t a, float dw, float hi) {
  return (V3f_t) {CLAMP(a.x, dw, hi), CLAMP(a.y, dw, hi), CLAMP(a.z, dw, hi)};
}
float dot_v3(V3f_t a, V3f_t b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
float len_sq_v3(V3f_t a) { return a.x*a.x + a.y*a.y + a.z*a.z; }
float len_v3(V3f_t a) { return sqrt(len_sq_v3(a)); }

V3d_t v3d(double x, double y, double z) { return (V3d_t) {x, y, z}; }
V3d_t sum_v3d(V3d_t a, V3d_t b) { return (V3d_t){a.x+b.x, a.y+b.y, a.z+b.z}; }
V3d_t diff_v3d(V3d_t a, V3d_t b) { return (V3d_t){a.x-b.x, a.y-b.y, a.z-b.z}; }
V3d_t mul_v3d_d(V3d_t a, double f) { return (V3d_t){a.x*f, a.y*f, a.z*f}; }
V3d_t mul_v3d_v(V3d_t a, V3d_t b) { return (V3d_t){a.x*b.x, a.y*b.y, a.z*b.z}; }
V3d_t inv_v3d(V3d_t a) { return (V3d_t){1.0/a.x, 1.0/a.y, 1.0/a.z}; }
V3d_t neg_v3d(V3d_t a) { return (V3d_t){-a.x, -a.y, -a.z}; }
V3d_t normalize_v3d(V3d_t a) { return mul_v3d_d(a, 1/len_v3d(a)); }
V3d_t cross_v3d(V3d_t a, V3d_t b) { return (V3d_t){a.y*b.z-a.z*b.y, a.y*b.x-a.x*b.z, a.x*b.y-a.y*b.z}; }
V3d_t clamp_v3d(V3d_t a, double dw, double hi) {
  return (V3d_t) {CLAMP(a.x, dw, hi), CLAMP(a.y, dw, hi), CLAMP(a.z, dw, hi)};
}
double dot_v3d(V3d_t a, V3d_t b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
double len_sq_v3d(V3d_t a) { return a.x*a.x + a.y*a.y + a.z*a.z; }
double len_v3d(V3d_t a) { return sqrt(len_sq_v3d(a)); }

char repr_res[50];
char *repr_v3(V3f_t a) {
	sprintf(repr_res, "%.6f %.6f %.6f", a.x, a.y, a.z);
	return repr_res;
}
char *repr_v3d(V3d_t a) {
	sprintf(repr_res, "%.6f %.6f %.6f", a.x, a.y, a.z);
	return repr_res;
}
void sv(V3f_t *a) {
	printf("%s\n", repr_v3(*a));
}
void sv_d(V3d_t *a) {
	printf("%s\n", repr_v3d(*a));
}



/* Matrix operations */
M44f_t m44f_unit(void) {
  M44f_t res = (M44f_t){0};
  res.mat[0][0] = 1.0f;
  res.mat[1][1] = 1.0f;
  res.mat[2][2] = 1.0f;
  res.mat[3][3] = 1.0f;
  return res;
}

M44d_t m44d_unit(void) {
  M44d_t res = (M44d_t){0};
  res.mat[0][0] = 1.0;
  res.mat[1][1] = 1.0;
  res.mat[2][2] = 1.0;
  res.mat[3][3] = 1.0;
  return res;
}


void show_m44f(M44f_t *a) {
  for (int i=0; i<4; i++) {
    printf("%-7.3f %-7.3f %-7.3f %-7.3f\n",
        a->mat[i][0],
        a->mat[i][1],
        a->mat[i][2],
        a->mat[i][3]);
  }
  return;
}
void show_m44d(M44d_t *a) {
  for (int i=0; i<4; i++) {
    printf("%-7.3f %-7.3f %-7.3f %-7.3f\n",
        a->mat[i][0],
        a->mat[i][1],
        a->mat[i][2],
        a->mat[i][3]);
  }
  return;
}

M44f_t m44f(float a, float b,
	float c, float d,
	float e, float f,
	float g, float h,
  float i, float j,
	float k, float l,
	float m, float n,
	float o, float p) {

  M44f_t r;
  r.mat[0][0] = a;
  r.mat[0][1] = b;
  r.mat[0][2] = c;
  r.mat[0][3] = d;
  r.mat[1][0] = e;
  r.mat[1][1] = f;
  r.mat[1][2] = g;
  r.mat[1][3] = h;
  r.mat[2][0] = i;
  r.mat[2][1] = j;
  r.mat[2][2] = k;
  r.mat[2][3] = l;
  r.mat[3][0] = m;
  r.mat[3][1] = n;
  r.mat[3][2] = o;
  r.mat[3][3] = p;

  return r;
}
M44d_t m44d(double a, double b,
	double c, double d,
	double e, double f,
	double g, double h,
  double i, double j,
	double k, double l,
	double m, double n,
	double o, double p) {

  M44d_t r;
  r.mat[0][0] = a;
  r.mat[0][1] = b;
  r.mat[0][2] = c;
  r.mat[0][3] = d;
  r.mat[1][0] = e;
  r.mat[1][1] = f;
  r.mat[1][2] = g;
  r.mat[1][3] = h;
  r.mat[2][0] = i;
  r.mat[2][1] = j;
  r.mat[2][2] = k;
  r.mat[2][3] = l;
  r.mat[3][0] = m;
  r.mat[3][1] = n;
  r.mat[3][2] = o;
  r.mat[3][3] = p;

  return r;
}
void mul_mat44f(M44f_t *a, M44f_t *b, M44f_t *c) {
#if 0
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                c->mat[i][j] =
                  a->mat[i][0] * b->mat[0][j]
                  + a->mat[i][1] * b->mat[1][j]
                  + a->mat[i][2] * b->mat[2][j]
                  + a->mat[i][3] * b->mat[3][j];
            }
        }
#else
        const float* restrict ap = &a->mat[0][0];
        const float* restrict bp = &b->mat[0][0];
              float* restrict cp = &c->mat[0][0];

        float a0, a1, a2, a3;

        a0 = ap[0];
        a1 = ap[1];
        a2 = ap[2];
        a3 = ap[3];

        cp[0]  = a0 * bp[0]  + a1 * bp[4]  + a2 * bp[8]  + a3 * bp[12];
        cp[1]  = a0 * bp[1]  + a1 * bp[5]  + a2 * bp[9]  + a3 * bp[13];
        cp[2]  = a0 * bp[2]  + a1 * bp[6]  + a2 * bp[10] + a3 * bp[14];
        cp[3]  = a0 * bp[3]  + a1 * bp[7]  + a2 * bp[11] + a3 * bp[15];

        a0 = ap[4];
        a1 = ap[5];
        a2 = ap[6];
        a3 = ap[7];

        cp[4]  = a0 * bp[0]  + a1 * bp[4]  + a2 * bp[8]  + a3 * bp[12];
        cp[5]  = a0 * bp[1]  + a1 * bp[5]  + a2 * bp[9]  + a3 * bp[13];
        cp[6]  = a0 * bp[2]  + a1 * bp[6]  + a2 * bp[10] + a3 * bp[14];
        cp[7]  = a0 * bp[3]  + a1 * bp[7]  + a2 * bp[11] + a3 * bp[15];

        a0 = ap[8];
        a1 = ap[9];
        a2 = ap[10];
        a3 = ap[11];

        cp[8]  = a0 * bp[0]  + a1 * bp[4]  + a2 * bp[8]  + a3 * bp[12];
        cp[9]  = a0 * bp[1]  + a1 * bp[5]  + a2 * bp[9]  + a3 * bp[13];
        cp[10] = a0 * bp[2]  + a1 * bp[6]  + a2 * bp[10] + a3 * bp[14];
        cp[11] = a0 * bp[3]  + a1 * bp[7]  + a2 * bp[11] + a3 * bp[15];

        a0 = ap[12];
        a1 = ap[13];
        a2 = ap[14];
        a3 = ap[15];

        cp[12] = a0 * bp[0]  + a1 * bp[4]  + a2 * bp[8]  + a3 * bp[12];
        cp[13] = a0 * bp[1]  + a1 * bp[5]  + a2 * bp[9]  + a3 * bp[13];
        cp[14] = a0 * bp[2]  + a1 * bp[6]  + a2 * bp[10] + a3 * bp[14];
        cp[15] = a0 * bp[3]  + a1 * bp[7]  + a2 * bp[11] + a3 * bp[15];
#endif
}

M44f_t tran_mat44f(M44f_t *a) {
#if 0
        M44f_t t;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                t.mat[i][j] = a->mat[j][i];
            }
        }

        return t;
#else
        return m44f(a->mat[0][0],
                    a->mat[1][0],
                    a->mat[2][0],
                    a->mat[3][0],
                    a->mat[0][1],
                    a->mat[1][1],
                    a->mat[2][1],
                    a->mat[3][1],
                    a->mat[0][2],
                    a->mat[1][2],
                    a->mat[2][2],
                    a->mat[3][2],
                    a->mat[0][3],
                    a->mat[1][3],
                    a->mat[2][3],
                    a->mat[3][3]);
#endif
}

M44d_t tran_mat44d(M44d_t *a) {
#if 0
        M44d_t t;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                t.mat[i][j] = a->mat[j][i];
            }
        }

        return t;
#else
        return m44d(a->mat[0][0],
                    a->mat[1][0],
                    a->mat[2][0],
                    a->mat[3][0],
                    a->mat[0][1],
                    a->mat[1][1],
                    a->mat[2][1],
                    a->mat[3][1],
                    a->mat[0][2],
                    a->mat[1][2],
                    a->mat[2][2],
                    a->mat[3][2],
                    a->mat[0][3],
                    a->mat[1][3],
                    a->mat[2][3],
                    a->mat[3][3]);
#endif
}

void mult_vec_v3_mat44_f(V3f_t* src, M44f_t *m, V3f_t *dst) {
  float a, b, c, w;

  a = src->x * m->mat[0][0] + src->y * m->mat[1][0] + src->z * m->mat[2][0] + m->mat[3][0];
  b = src->x * m->mat[0][1] + src->y * m->mat[1][1] + src->z * m->mat[2][1] + m->mat[3][1];
  c = src->x * m->mat[0][2] + src->y * m->mat[1][2] + src->z * m->mat[2][2] + m->mat[3][2];
  w = src->x * m->mat[0][3] + src->y * m->mat[1][3] + src->z * m->mat[2][3] + m->mat[3][3];

  dst->x = a / w;
  dst->y = b / w;
  dst->z = c / w;
  return;
}

void mult_dir_v3_mat44_f(V3f_t* src, M44f_t *m, V3f_t *dst) {
  float a, b, c;

  a = src->x * m->mat[0][0] + src->y * m->mat[1][0] + src->z * m->mat[2][0] + m->mat[3][0];
  b = src->x * m->mat[0][1] + src->y * m->mat[1][1] + src->z * m->mat[2][1] + m->mat[3][1];
  c = src->x * m->mat[0][2] + src->y * m->mat[1][2] + src->z * m->mat[2][2] + m->mat[3][2];

  dst->x = a;
  dst->y = b;
  dst->z = c;
  return;
}

void mult_vec_v3_mat44_d(V3d_t* src, M44d_t *m, V3d_t *dst) {
  double a, b, c, w;

  a = src->x * m->mat[0][0] + src->y * m->mat[1][0] + src->z * m->mat[2][0] + m->mat[3][0];
  b = src->x * m->mat[0][1] + src->y * m->mat[1][1] + src->z * m->mat[2][1] + m->mat[3][1];
  c = src->x * m->mat[0][2] + src->y * m->mat[1][2] + src->z * m->mat[2][2] + m->mat[3][2];
  w = src->x * m->mat[0][3] + src->y * m->mat[1][3] + src->z * m->mat[2][3] + m->mat[3][3];

  dst->x = a / w;
  dst->y = b / w;
  dst->z = c / w;
  return;
}

void mult_dir_v3_mat44_d(V3d_t* src, M44d_t *m, V3d_t *dst) {
  double a, b, c;

  a = src->x * m->mat[0][0] + src->y * m->mat[1][0] + src->z * m->mat[2][0] + m->mat[3][0];
  b = src->x * m->mat[0][1] + src->y * m->mat[1][1] + src->z * m->mat[2][1] + m->mat[3][1];
  c = src->x * m->mat[0][2] + src->y * m->mat[1][2] + src->z * m->mat[2][2] + m->mat[3][2];

  dst->x = a;
  dst->y = b;
  dst->z = c;
  return;
}

M44f_t inv_mat44f(M44f_t t) {
  int i, j, k, pivot=0;
  float pivotsize=0, tmp=0, f=0;
  M44f_t s = m44f_unit();

  for (i=0; i<3; i++) {
    pivot = i;
    pivotsize = t.mat[i][i];

    if (pivotsize < 0) pivotsize = -pivotsize;

    for (j=i+1; j<4; j++) {
      tmp = t.mat[j][i];
      if (tmp < 0) tmp = -tmp;
      if (tmp > pivotsize) {
        pivot = j;
        pivotsize = tmp;
      }
    }

    if (pivotsize == 0) {
      return m44f_unit();
    }
    tmp = 0;
    if (pivot != i) {
      for (j=0; j<4; j++) {
        tmp = t.mat[i][j];
        t.mat[i][j] = t.mat[pivot][j];
        t.mat[pivot][j] = tmp;

        tmp = s.mat[i][j];
        s.mat[i][j] = s.mat[pivot][j];
        s.mat[pivot][j] = tmp;
      }
    }

    for (j=i+1; j<4; j++) {
      f = t.mat[j][i] / t.mat[i][i];
      for (k=0; k<4; k++) {
        t.mat[j][k] -= f * t.mat[i][k];
        s.mat[j][k]  -= f * s.mat[i][k];
      }
    }
  }

  for (i=3; i>=0; --i) {
      if ((f=t.mat[i][i])==0) {
        return m44f_unit();
      }

      for (j=0; j<4; j++) {
        t.mat[i][j] /= f;
        s.mat[i][j]  /= f;
      }

      for (j=0; j<i; j++) {
        f = t.mat[j][i];
        for (k=0; k<4; k++) {
          t.mat[j][k] -= f * t.mat[i][k];
          s.mat[j][k] -= f * s.mat[i][k];
        }
      }
    }

  return s;
}

M44d_t inv_mat44d(M44d_t t) {
  int i, j, k, pivot=0;
  double pivotsize=0, tmp=0, f=0;
  M44d_t s = m44d_unit();

  for (i=0; i<3; i++) {
    pivot = i;
    pivotsize = t.mat[i][i];

    if (pivotsize < 0) pivotsize = -pivotsize;

    for (j=i+1; j<4; j++) {
      tmp = t.mat[j][i];
      if (tmp < 0) tmp = -tmp;
      if (tmp > pivotsize) {
        pivot = j;
        pivotsize = tmp;
      }
    }

    if (pivotsize == 0) {
      return m44d_unit();
    }
    tmp = 0;
    if (pivot != i) {
      for (j=0; j<4; j++) {
        tmp = t.mat[i][j];
        t.mat[i][j] = t.mat[pivot][j];
        t.mat[pivot][j] = tmp;

        tmp = s.mat[i][j];
        s.mat[i][j] = s.mat[pivot][j];
        s.mat[pivot][j] = tmp;
      }
    }

    for (j=i+1; j<4; j++) {
      f = t.mat[j][i] / t.mat[i][i];
      for (k=0; k<4; k++) {
        t.mat[j][k] -= f * t.mat[i][k];
        s.mat[j][k]  -= f * s.mat[i][k];
      }
    }
  }

  for (i=3; i>=0; --i) {
      if ((f=t.mat[i][i])==0) {
        return m44d_unit();
      }

      for (j=0; j<4; j++) {
        t.mat[i][j] /= f;
        s.mat[i][j]  /= f;
      }

      for (j=0; j<i; j++) {
        f = t.mat[j][i];
        for (k=0; k<4; k++) {
          t.mat[j][k] -= f * t.mat[i][k];
          s.mat[j][k] -= f * s.mat[i][k];
        }
      }
    }

  return s;
}
