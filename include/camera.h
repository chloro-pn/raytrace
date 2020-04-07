#ifndef CAMERA_H
#define CAMERA_H

#include "mymath.h"
#include <cassert>

class camera {
private:
  vec3 lookat_ = vec3(0, 0, -1);
  vec3 up_ = vec3(0, 1, 0);
  vec3 right_;
  point3 location_ = point3(0, 0, 0);
  double width_;
  double height_;

public:
  camera(double w, double h):width_(w), height_(h) {
    assert(vertical(lookat_, up_));
    right_ = normalize(lookat_.cross(up_));
  }

  void resize(double w, double h) {
    width_= w;
    height_ = h;
  }

  void set_location(const point3& p) {
    location_ = p;
  }

  void set_lookat(const vec3& v) {
    lookat_ = normalize(v);
    assert(vertical(lookat_, up_));
    right_ = normalize(lookat_.cross(up_));
  }

  void set_up(const vec3& v) {
    up_ = normalize(v);
    assert(vertical(lookat_, up_));
    right_ = normalize(lookat_.cross(up_));
  }

  void set(const vec3& lookat, const vec3& up) {
    lookat_ = normalize(lookat);
    up_ = normalize(up);
    assert(vertical(lookat_, up_));
    right_ = normalize(lookat_.cross(up_));
  }

  //0 <= r1 <= 1, 0 <= r2 <= 1.
  point3 get_view_point_from_ratio(double r1, double r2) {
    assert(value_be(r1, 0.0) && value_se(r1, 1.0));
    assert(value_be(r2, 0.0) && value_se(r2, 1.0));
    r1 = r1 - 0.5;
    r2 = r2 - 0.5;
    point3 point_location = location_ + (right_ * r1 * width_ + up_ * r2 * height_);
    return point_location;
  }

  const vec3& lookat() const {
    return lookat_;
  }

  const vec3& up() const {
    return up_;
  }

  const vec3& right() const {
    return right_;
  }
};

#endif // CAMERA_H
