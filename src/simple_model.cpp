#include "../include/simple_model.h"
#include "../include/director.h"
#include "../include/light.h"
#include "../include/color.h"
#include "../include/actor.h"
#include "../include/local_information.h"

namespace pn_graphics {
color simple_model::get_color_from_ray(ray ray_, director *director_) {
  local_information local = (director_->get_scene()).get_loinf_from_ray(ray_);
  if(local.valid() == false) {
    return director_->get_scene().background_color();
  }
  else {
    double cos_angle = get_cos_angle(-ray_.direction, local.normal);
    cos_angle = cos_angle >= 0 ? cos_angle : 0;
    const color& env_color_ = director_->get_light().get_ambient_light().get_color();
    int r = env_color_.r() * local.m.k_a_r_ * cos_angle;
    int g = env_color_.g() * local.m.k_a_g_ * cos_angle;
    int b = env_color_.b() * local.m.k_a_b_ * cos_angle;
    return color(r, g, b);
  }
}

simple_model::simple_model() {

}
}
