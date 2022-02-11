#ifndef MATERIAL_H
#define MATERIAL_H

#include "utils.h"

enum MATERIAL_TYPE {
	DIFF_GLOSSY = 1,
	REFLECT = 2,
	REFRACT = 4,
};

enum PATTERN {
	PLAIN = 1,
	CHECKER = 2,
	TEXTURE = 3
};

typedef struct Material {
	enum MATERIAL_TYPE type;
	enum PATTERN pattern_type;
	float ior; 										// refraction coef
	V3f_t d_col; 									// diffusion color
	V3f_t s_col; 									// specular color
	V3f_t e_col; 									// emission color
	float specular_exp;
	char *texture_filename;
} Material_t;

V3f_t eval_diffuse_color(Material_t *material, V2f_t *st);

#endif
