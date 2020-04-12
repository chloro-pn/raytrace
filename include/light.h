#ifndef LIGHT_H
#define LIGHT_H

#include "color.h"
#include "mymath.h"
#include "scene.h"
#include <vector>
#include <string>
#include <map>

namespace pn_graphics {

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
  point_light(color c, point3 p):color_(c), origin_(p),init_(true) {

  }

  point_light():color_(color::white()), origin_(point3::zero()), init_(false) {

  }

  color get_color() const {
    return color_;
  }

  point3 get_origin() const {
    return origin_;
  }

  bool if_init() const {
    return init_;
  }

private:
  color color_;
  point3 origin_;
  bool init_;
};

class light {
public:
  light(const ambient_light& al = ambient_light(color(25, 25, 25))):al_(al) {

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

  struct light_source_information {
    color color_;
    vec3 direction_;
    light_source_information(color c, vec3 v) : color_(c), direction_(v) {

    }
  };

  std::vector<light_source_information> get_visiable_light_source(const point3& xp, scene& scene_) const {
    std::vector<light_source_information> results;
    for(auto& pal : pals_) {
      ray new_ray(xp, -pal.second.get_direction());
      local_information local = scene_.get_loinf_from_ray(new_ray);
      if(local.valid() == false) {
        light_source_information tmp(pal.second.get_color(), normalize(new_ray.direction));
        results.push_back(tmp);
      }
    }

    for(auto& pol : pols_) {
      ray new_ray(xp, normalize(vec3(xp, pol.second.get_origin())));
      local_information local = scene_.get_loinf_from_ray(new_ray);
      if(local.valid() == false) {
        light_source_information tmp(pol.second.get_color(), new_ray.direction);
        results.push_back(tmp);
      }
    }
    return results;
  }

private:
  ambient_light al_;
  std::map<std::string, parallel_light> pals_;
  std::map<std::string, point_light> pols_;
};
}

#endif // LIGHT_H
