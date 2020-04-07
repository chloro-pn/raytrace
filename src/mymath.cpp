#include "../include/mymath.h"

//以下是工具函数
bool vertical(const vec3& v1, const vec3& v2) {
  return value_equal(0.0f, v1.dot(v2));
}

vec3 normalize(const vec3& v) {
  double length = v.x_ * v.x_ + v.y_ * v.y_ + v.z_ * v.z_;
  length = std::sqrt(length);
  return vec3(v.x_ / length, v.y_ / length, v.z_ / length);
}
