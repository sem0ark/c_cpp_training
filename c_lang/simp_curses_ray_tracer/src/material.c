#include "utils.h"
#include "material.h"

V3f_t get_checker(V2f_t *st) {
  if ((st->x > 0.5f) ^ (st->y > 0.5f)) return v3f_s(1.0f);
  else return v3f_s(0.1f);
}


V3f_t get_texture(V2f_t *st) {
  return v3f(1,1,1);
}

V3f_t eval_texture_color(Material_t *material, V2f_t *st) {
  switch (material->pattern_type) {
    case PLAIN: return v3f(1,1,1);
    case CHECKER: return get_checker(st);
    case TEXTURE: return get_texture(st);
    default: return v3f(1,0,1);
  }
}

