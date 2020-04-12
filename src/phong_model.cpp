#include "../include/phong_model.h"
#include "../include/director.h"
#include "../include/light.h"
#include "../include/color.h"
#include "../include/actor.h"
#include "../include/local_information.h"
#include <QDebug>

namespace pn_graphics {
color phong_model::get_color_from_ray(const ray& ray_, director *director_) {
  return inner(ray_, director_, 0);
}



color phong_model::inner(const ray& ray_, director* director_, int current) {
  local_information local = (director_->get_scene()).get_loinf_from_ray(ray_);
  //获取环境光提供的光强
  const color& env_color_ = director_->get_light().get_ambient_light().get_color();

  if(local.valid() == false) {
    //环境光只计算一次
    if(current == 0) {
      return env_color_;
    }
    else {
      return color::black();
    }
  }
  else {
    //出射光颜色等于反射光颜色+自发光（纹理）颜色。
    int r = env_color_.r() * local.m.k_a_r_;
    int g = env_color_.g() * local.m.k_a_g_;
    int b = env_color_.b() * local.m.k_a_b_;
    color c0(r, g, b);
    color tmp = get_reflected_light(ray_, local, director_, current) + local.texture_color;
    //环境光只计算一次。
    if(current == 0) {
      return tmp + c0;
    }
    else {
      return tmp;
    }
  }
}

phong_model::phong_model(int depth) : max_depth_(depth) {
  assert(max_depth_ >= 0);
}

color phong_model::get_reflected_light(const ray& ray_, const local_information& local, director* director_, int current) {
  double t = local.t;
  point3 xp = point3(ray_.origin.px() + ray_.direction.x_ * t, ray_.origin.py() + ray_.direction.y_ * t, ray_.origin.pz() + ray_.direction.z_ * t);

  //light类接受交点，返回所有可见光源在此处的入射初始颜色。
  std::vector<light::light_source_information> lights = director_->get_light().get_visiable_light_source(xp, director_->get_scene());

  std::vector<color> result;

  //材质处理，漫反射+镜面反射
  for(auto& each : lights) {
    double cos_angle = get_cos_angle(each.direction_, local.normal);
    cos_angle = cos_angle >= 0 ? cos_angle : 0;

    int r = each.color_.r() * local.m.k_d_r_ * cos_angle;
    int b = each.color_.b() * local.m.k_d_b_ * cos_angle;
    int g = each.color_.g() * local.m.k_d_g_ * cos_angle;
    //漫反射模型计算光源的输出。
    result.push_back(color(r, g, b));

    vec3 normal = normalize(local.normal);
    vec3 tmp = normal * normal.dot(each.direction_) * 2 - each.direction_;
    vec3 tmp2 = - ray_.direction;
    cos_angle = get_cos_angle(tmp, tmp2);
    double n = local.m.n_;
    double tmp3 = std::pow(cos_angle, n);
    tmp3 = tmp3 >= 0 ? tmp3 : 0;
    r = each.color_.r() * local.m.k_s_r_ * tmp3;
    g = each.color_.g() * local.m.k_s_g_ * tmp3;
    b = each.color_.b() * local.m.k_s_b_ * tmp3;
    //镜面反射计算光源的输出。
    result.push_back(color(r, g, b));
  }

  int r = 0;
  int b = 0;
  int g = 0;
  for(auto& each : result) {
    r += each.r();
    b += each.b();
    g += each.g();
  }
  return color(r, g, b);
}
}
