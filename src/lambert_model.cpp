#include "../include/lambert_model.h"
#include "../include/director.h"
#include "../include/light.h"
#include "../include/color.h"
#include "../include/actor.h"
#include "../include/local_information.h"
#include <QDebug>

namespace pn_graphics {
color lambert_model::get_color_from_ray(ray ray_, director *director_) {
  local_information local = (director_->get_scene()).get_loinf_from_ray(ray_);
  double t = local.t;
  point3 xp = point3(ray_.origin.px() + ray_.direction.x_ * t, ray_.origin.py() + ray_.direction.y_ * t, ray_.origin.pz() + ray_.direction.z_ * t);
  if(local.valid() == false) {
    return director_->get_scene().background_color();
  }
  else {
    const color& env_color_ = director_->get_light().get_ambient_light().get_color();
    int r = env_color_.r() * local.m.k_a_r_;
    int g = env_color_.g() * local.m.k_a_g_;
    int b = env_color_.b() * local.m.k_a_b_;
    color c1(r, g, b);

    color c2(color::black());
    const parallel_light& light = director_->get_light().get_parallel_lights("light1");
    assert(light.if_init() == true);
    ray new_ray(xp, -light.get_direction());

    local_information new_local = (director_->get_scene()).get_loinf_from_ray(new_ray);
    if(new_local.valid() == false) {
      c2 = light.get_color();
    }
    double cos_angle = get_cos_angle(new_ray.direction, local.normal);
    cos_angle = cos_angle >= 0 ? cos_angle : 0;

    r = c2.r() * local.m.k_d_r_ * cos_angle;
    b = c2.b() * local.m.k_d_b_ * cos_angle;
    g = c2.g() * local.m.k_d_g_ * cos_angle;
    c2.set_red(r);
    c2.set_blue(b);
    c2.set_green(g);
    return c1 + c2;
  }
}

lambert_model::lambert_model() {

}
}
