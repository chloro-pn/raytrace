#include "raytrace/include/material.h"

namespace pn_graphics {
material material::material_sample() {
  material m;
  m.k_a_r_ = 0.4;
  m.k_a_g_ = 0.4;
  m.k_a_b_ = 0.4;
  m.k_d_r_ = 0.6;
  m.k_d_g_ = 0.6;
  m.k_d_b_ = 0.6;
  m.k_s_r_ = 0;
  m.k_s_g_ = 0;
  m.k_s_b_ = 0;
  m.n_ = 20;
  return m;
}
}
