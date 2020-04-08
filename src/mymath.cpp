#include "../include/mymath.h"

namespace pn_graphics {
//以下是工具函数
bool vertical(const vec3& v1, const vec3& v2) {
  return value_equal(0.0, v1.dot(v2));
}

vec3 normalize(const vec3& v) {
  double length = v.x_ * v.x_ + v.y_ * v.y_ + v.z_ * v.z_;
  length = std::sqrt(length);
  return vec3(v.x_ / length, v.y_ / length, v.z_ / length);
}

double get_angle(const vec3& v1, const vec3& v2) {
  double tmp = v1.dot(v2) / (get_second_norm(v1) * get_second_norm(v2));
  return std::acos(tmp);
}

double get_cos_angle(const vec3& v1, const vec3& v2) {
  double tmp = v1.dot(v2) / (get_second_norm(v1) * get_second_norm(v2));
  return tmp;
}

double get_second_norm(const vec3& v) {
  return std::sqrt(v.x_ * v.x_ + v.y_ * v.y_ + v.z_ * v.z_);
}
}
