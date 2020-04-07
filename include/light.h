#ifndef LIGHT_H
#define LIGHT_H

#include "color.h"
#include "mymath.h"
#include <vector>
#include <string>
#include <map>

class ambient_light {
public:
  ambient_light(color c):color_(c) {

  }

  color get_color() const {
    return color_;
  }

private:
  color color_;
};

class parallel_light {
public:
  parallel_light(color c , vec3 dir):color_(c), direction_(dir), init_(true) {

  }

  parallel_light():color_(color::white()), direction_(vec3::zero()), init_(false) {

  }

  color get_color() const {
    return color_;
  }

  vec3 get_direction() const {
    return direction_;
  }

  bool if_init() const {
    return init_;
  }

private:
  color color_;
  vec3 direction_;
  bool init_;
};

class point_light{
public:
  point_light(color c, vec3 dir, point3 p):color_(c), direction_(dir), origin_(p),init_(true) {

  }

  point_light():color_(color::white()), direction_(vec3::zero()), origin_(point3::zero()), init_(false) {

  }

  color get_color() const {
    return color_;
  }

  vec3 get_direction() const {
    return direction_;
  }

  point3 get_origin() const {
    return origin_;
  }

  bool if_init() const {
    return init_;
  }

private:
  color color_;
  vec3 direction_;
  point3 origin_;
  bool init_;
};

class light {
public:
  light(const ambient_light& al = ambient_light(color(255, 255, 255))):al_(al) {

  }

  void push_parallel_light(std::string id, const parallel_light& pal) {
    pals_[id] = pal;
  }

  void push_point_light(std::string id, const point_light& pol) {
    pols_[id] = pol;
  }

  const parallel_light& get_parallel_lights(std::string id){
    return pals_[id];
  }

  const point_light& get_point_lights(std::string id) {
    return pols_[id];
  }

  const ambient_light& get_ambient_light() const {
    return al_;
  }

private:
  ambient_light al_;
  std::map<std::string, parallel_light> pals_;
  std::map<std::string, point_light> pols_;
};

struct ray {
  point3 origin;
  vec3 direction;
  ray(point3 p, vec3 d):origin(p), direction(d) {

  }
};

#endif // LIGHT_H
