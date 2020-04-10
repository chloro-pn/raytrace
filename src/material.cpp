#include "raytrace/include/material.h"

namespace pn_graphics {
material material::material_sample() {
  material m;
  m.k_a_r_ = 0.5;
  m.k_a_g_ = 0.5;
  m.k_a_b_ = 0.5;
  m.k_d_r_ = 0.9;
  m.k_d_g_ = 0.85;
  m.k_d_b_ = 0.35;
  return m;
}
}
