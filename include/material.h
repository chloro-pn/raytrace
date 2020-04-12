#ifndef MATERIAL_H
#define MATERIAL_H

namespace pn_graphics {
struct material {
  double k_a_r_ = 0; // 环境光反射系数0 ~ 1
  double k_a_g_ = 0;
  double k_a_b_ = 0;
  double k_d_r_ = 0; // 漫射系数 0 ～ 1
  double k_d_g_ = 0;
  double k_d_b_ = 0;
  double k_s_r_ = 0; // 镜面反射系数 0 ～ 1
  double k_s_g_ = 0;
  double k_s_b_ = 0;
  int n_ = 1; // 镜面高光指数

  static material material_sample();
};
}
#endif // MATERIAL_H
