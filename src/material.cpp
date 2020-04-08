#include "raytrace/include/material.h"

namespace pn_graphics {
material material::material_sample() {
  material m;
  m.k_a_r_ = 0.8;
  m.k_a_g_ = 0.75;
  m.k_a_b_ = 0.33;
  return m;
}
}
