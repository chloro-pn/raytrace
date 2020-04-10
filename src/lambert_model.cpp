#include "../include/lambert_model.h"
#include "../include/director.h"
#include "../include/light.h"
#include "../include/color.h"
#include "../include/actor.h"
#include "../include/local_information.h"
#include <QDebug>

namespace pn_graphics {
color lambert_model::get_color_from_ray(const ray& ray_, director *director_) {
  return inner(ray_, director_, 0);
}

color lambert_model::inner(const ray& ray_, director* director_, int current) {
  local_information local = (director_->get_scene()).get_loinf_from_ray(ray_);
  //获取环境光
  const color& env_color_ = director_->get_light().get_ambient_light().get_color();

  if(local.valid() == false) {
    //射线ray_与场景没有交点,直接返回环境光。
    return env_color_;
  }
  else {
    int r = env_color_.r() * local.m.k_a_r_;
    int g = env_color_.g() * local.m.k_a_g_;
    int b = env_color_.b() * local.m.k_a_b_;
    color c1(r, g, b);

    //平行光输入，默认为没有输入
    color c2(color::black());

    double t = local.t;
    point3 xp = point3(ray_.origin.px() + ray_.direction.x_ * t, ray_.origin.py() + ray_.direction.y_ * t, ray_.origin.pz() + ray_.direction.z_ * t);

    const parallel_light& light = director_->get_light().get_parallel_lights("light1");
    assert(light.if_init() == true);
    ray new_ray(xp, -light.get_direction());
    local_information new_local = (director_->get_scene()).get_loinf_from_ray(new_ray);
    if(new_local.valid() == false) {
      //得到平行光输入
      c2 = light.get_color();
    }
    double cos_angle = get_cos_angle(new_ray.direction, local.normal);
    cos_angle = cos_angle >= 0 ? cos_angle : 0;

    r = c2.r() * local.m.k_d_r_ * cos_angle;
    b = c2.b() * local.m.k_d_b_ * cos_angle;
    g = c2.g() * local.m.k_d_g_ * cos_angle;
    //漫反射模型计算平行光的输出。
    c2.set_red(r);
    c2.set_blue(b);
    c2.set_green(g);

    //点光源输入，默认为没有输入
    color c3(color::black());
    const point_light& light2 = director_->get_light().get_point_lights("light2");
    assert(light2.if_init() == true);
    new_ray = ray(xp, normalize(vec3(xp, light2.get_origin())));
    new_local = (director_->get_scene()).get_loinf_from_ray(new_ray);
    if(new_local.valid() == false) {
      c3 = light2.get_color();
    }
    cos_angle = get_cos_angle(new_ray.direction, local.normal);
    cos_angle = cos_angle >= 0 ? cos_angle : 0;

    r = c3.r() * local.m.k_d_r_ * cos_angle;
    b = c3.b() * local.m.k_d_b_ * cos_angle;
    g = c3.g() * local.m.k_d_g_ * cos_angle;
    //漫反射模型计算平行光的输出。
    c3.set_red(r);
    c3.set_blue(b);
    c3.set_green(g);

    return c1 + c2 + c3 + local.texture_color;
  }
}

lambert_model::lambert_model(int depth) : max_depth_(depth) {
  assert(max_depth_ >= 0);
}
}
