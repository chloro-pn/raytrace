#include "raytrace/include/material.h"

namespace pn_graphics {
material material::material_sample() {
  material m;
  m.k_a_r_ = 0.3;
  m.k_a_g_ = 0.3;
  m.k_a_b_ = 0.3;
  m.k_d_r_ = 0.4;
  m.k_d_g_ = 0.35;
  m.k_d_b_ = 0.1;
  return m;
}
}
