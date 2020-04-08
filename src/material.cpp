#include "raytrace/include/material.h"

material material::material_sample() {
  material m;
  m.k_a_r_ = 0.5;
  m.k_a_g_ = 0.45;
  m.k_a_b_ = 0.33;
  return m;
}
