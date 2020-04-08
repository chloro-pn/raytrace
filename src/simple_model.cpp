#include "../include/simple_model.h"
#include "../include/director.h"
#include "../include/light.h"
#include "../include/color.h"
#include "../include/actor.h"
#include "../include/local_information.h"

color simple_model::get_color_from_ray(ray ray_, director *director_) {
  local_information local = (director_->get_scene()).get_loinf_from_ray(ray_);
  if(local.valid() == false) {
    return background_color_;
  }
  else {
    return color(int(env_color_.r() * local.m.k_a_r_), int(env_color_.g() * local.m.k_a_g_), int(env_color_.b() * local.m.k_a_b_));
  }
}

simple_model::simple_model(color env):background_color_(color::black()), env_color_(env) {

}
