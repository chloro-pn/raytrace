#ifndef CAMERA_H
#define CAMERA_H

#include "mymath.h"
#include <cassert>
#include <cmath>

namespace pn_graphics {
class camera {
private:
  //以下四个成员变量表示初始位置，不变。
  const vec3 lookat_ = vec3(0, 0, -1);
  const vec3 up_ = vec3(0, 1, 0);
  const vec3 right_ = vec3(1, 0, 0);
  const point3 location_ = point3(0, 0, 0);

  vec3 tmp_lookat_ = vec3::zero();
  vec3 tmp_up_ = vec3::zero();
  vec3 tmp_right_ = vec3::zero();
  point3 tmp_location_ = point3::zero();

  double width_;
  double height_;
  double rotate_by_x_ = 0; //抬头，低头
  double rotate_by_y_ = 0; //左看，右看

public:
  camera(double w = 800, double h = 600):width_(w), height_(h) {

  }

  void resize(double w, double h) {
    width_= w;
    height_ = h;
  }

  void move_to(const point3& p) {
    tmp_location_ = p;
  }

  void set_rotate_by_y(double r) {
    rotate_by_y_ = r;
  }

  void set_rotate_by_x(double r) {
    rotate_by_x_ = r;
  }

  void render_before() {
    //这里计算tmp值.
    double cos_a1 = std::cos(rotate_by_x_);
    double sin_a1 = std::sin(rotate_by_x_);
    double cos_a2 = std::cos(rotate_by_y_);
    double sin_a2 = std::sin(rotate_by_y_);

    tmp_up_.y_ = up_.y_ * cos_a1 - up_.z_ * sin_a1;
    tmp_up_.x_ = up_.x_;
    tmp_up_.z_ = up_.y_ * sin_a1 + up_.z_ * cos_a1;

    tmp_lookat_.y_ = lookat_.y_ * cos_a1 - lookat_.z_ * sin_a1;
    tmp_lookat_.x_ = lookat_.x_;
    tmp_lookat_.z_ = lookat_.y_ * sin_a1 + lookat_.z_ * cos_a1;

    tmp_right_.y_ = right_.y_ * cos_a1 - right_.z_ * sin_a1;
    tmp_right_.x_ = right_.x_;
    tmp_right_.z_ = right_.y_ * sin_a1 + right_.z_ * cos_a1;

    tmp_up_.x_ = tmp_up_.x_ * cos_a2 - tmp_up_.z_ * sin_a2;
    tmp_up_.y_ = tmp_up_.y_;
    tmp_up_.z_ = tmp_up_.x_ * sin_a2 + tmp_up_.z_ * cos_a2;

    tmp_lookat_.x_ = tmp_lookat_.x_ * cos_a2 - tmp_lookat_.z_ * sin_a2;
    tmp_lookat_.y_ = tmp_lookat_.y_;
    tmp_lookat_.z_ = tmp_lookat_.x_ * sin_a2 + tmp_lookat_.z_ * cos_a2;

    tmp_right_.x_ = tmp_right_.x_ * cos_a2 - tmp_right_.z_ * sin_a2;
    tmp_right_.y_ = tmp_right_.y_;
    tmp_right_.z_ = tmp_right_.x_ * sin_a2 + tmp_right_.z_ * cos_a2;

    tmp_up_ = normalize(tmp_up_);
    tmp_right_ = normalize(tmp_right_);
    tmp_lookat_ = normalize(tmp_lookat_);
  }

  //0 <= r1 <= 1, 0 <= r2 <= 1.
  point3 get_view_point_from_ratio(double r1, double r2) {
    assert(value_be(r1, 0.0) && value_se(r1, 1.0));
    assert(value_be(r2, 0.0) && value_se(r2, 1.0));
    r1 = r1 - 0.5;
    r2 = r2 - 0.5;
    point3 point_location = location() + (right() * r1 * width_ + up() * r2 * height_);
    return point_location;
  }

  const vec3& lookat() const {
    return tmp_lookat_;
  }

  const vec3& up() const {
    return tmp_up_;
  }

  const vec3& right() const {
    return tmp_right_;
  }

  const point3& location() const {
    return tmp_location_;
  }
};
}
#endif // CAMERA_H
