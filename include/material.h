#ifndef MATERIAL_H
#define MATERIAL_H

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
  double n_ = 1; // 镜面高光指数
};

#endif // MATERIAL_H
