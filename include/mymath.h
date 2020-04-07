#ifndef MYMATH_H
#define MYMATH_H

#include "value_compare.h"
#include <cmath>

struct vec3;

struct point3 {
  float px_;
  float py_;
  float pz_;

  static point3 zero() {
    return point3(0, 0, 0);
  }

  point3(float x, float y, float z):px_(x), py_(y), pz_(z) {

  }

  point3 operator+(const vec3& v) const;

  bool operator==(const point3& v) const {
    return value_equal(px_, v.px()) && value_equal(py_, v.py()) && value_equal(pz_, v.pz());
  }

  float px() const {
    return px_;
  }

  float py() const {
    return py_;
  }

  float pz() const {
    return pz_;
  }
};

struct vec3 {
  float x_;
  float y_;
  float z_;

  static vec3 zero() {
    return vec3(0, 0, 0);
  }

  vec3() = default;

  vec3(float x, float y, float z):x_(x), y_(y), z_(z) {

  }

  float dot(const vec3& other) const {
    return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
  }

  vec3 cross(const vec3& other) const {
    vec3 result;
    result.x_ = y_ * other.z_ - other.y_ * z_;
    result.y_ = z_ * other.x_ - other.z_ * x_;
    result.z_ = x_ * other.y_ - other.x_ * y_;
    return result;
  }

  bool operator==(const vec3& other) const {
    return value_equal(x_, other.x_) && value_equal(y_, other.y_) && value_equal(z_, other.z_);
  }

  vec3 operator+(const vec3& other) const {
    vec3 result;
    result.x_ = x_ + other.x_;
    result.y_ = y_ + other.y_;
    result.z_ = z_ + other.z_;
    return result;
  }

  vec3 operator*(double n) const {
    return vec3(x_ * n, y_ * n, z_ * n);
  }
};

inline
point3 point3::operator+(const vec3& v) const {
  return point3(px_ + v.x_, py_ + v.y_, pz_ + v.z_);
}

//以下是工具函数
bool vertical(const vec3& v1, const vec3& v2);

vec3 normalize(const vec3& v);

#endif // MATH_H
