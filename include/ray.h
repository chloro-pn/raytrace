#ifndef RAY_H
#define RAY_H
#include "mymath.h"

namespace pn_graphics {
struct ray {
  point3 origin;
  vec3 direction;
  ray(point3 p, vec3 d):origin(p), direction(d) {

  }
};
}

#endif // RAY_H
