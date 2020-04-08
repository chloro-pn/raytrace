#ifndef MYMATH_H
#define MYMATH_H

#include "value_compare.h"
#include <cmath>

struct vec3;

struct point3 {
  double px_;
  double py_;
  double pz_;

  static point3 zero() {
    return point3(0, 0, 0);
  }

  point3(double x, double y, double z):px_(x), py_(y), pz_(z) {

  }

  point3 operator+(const vec3& v) const;

  bool operator==(const point3& v) const {
    return value_equal(px_, v.px()) && value_equal(py_, v.py()) && value_equal(pz_, v.pz());
  }

  double px() const {
    return px_;
  }

  double py() const {
    return py_;
  }

  double pz() const {
    return pz_;
  }
};

struct vec3 {
  double x_;
  double y_;
  double z_;

  static vec3 zero() {
    return vec3(0, 0, 0);
  }

  vec3() = default;

  vec3(const point3& p1, const point3& p2) {
    x_ = p2.px() - p1.px();
    y_ = p2.py() - p1.py();
    z_ = p2.pz() - p1.pz();
  }

  vec3(double x, double y, double z):x_(x), y_(y), z_(z) {

  }

  double dot(const vec3& other) const {
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

  bool operator!=(const vec3& other) const {
    return !(*this == other);
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

  vec3 operator-() const {
    return vec3(-x_, -y_, -z_);
  }
};

inline
point3 point3::operator+(const vec3& v) const {
  return point3(px_ + v.x_, py_ + v.y_, pz_ + v.z_);
}

//以下是工具函数
bool vertical(const vec3& v1, const vec3& v2);

vec3 normalize(const vec3& v);

double get_second_norm(const vec3& v);

double get_angle(const vec3& v1, const vec3& v2);

double get_cos_angle(const vec3& v1, const vec3& v2);

#endif // MATH_H
