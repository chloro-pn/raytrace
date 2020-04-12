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
  //获取环境光提供的光强
  const color& env_color_ = director_->get_light().get_ambient_light().get_color();
  int r = env_color_.r() * local.m.k_a_r_;
  int g = env_color_.g() * local.m.k_a_g_;
  int b = env_color_.b() * local.m.k_a_b_;
  color c0(r, g, b);

  if(local.valid() == false) {
    //环境光只计算一次
    if(current == 0) {
      return c0;
    }
    else {
      return color::black();
    }
  }
  else {
    //出射光颜色等于反射光颜色+自发光（纹理）颜色。
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

lambert_model::lambert_model(int depth) : max_depth_(depth) {
  assert(max_depth_ >= 0);
}

color lambert_model::get_reflected_light(const ray& ray_, const local_information& local, director* director_, int current) {
  double t = local.t;
  point3 xp = point3(ray_.origin.px() + ray_.direction.x_ * t, ray_.origin.py() + ray_.direction.y_ * t, ray_.origin.pz() + ray_.direction.z_ * t);

  //light类接受交点，返回所有可见光源在此处的入射初始颜色。
  std::vector<light::light_source_information> lights = director_->get_light().get_visiable_light_source(xp, director_->get_scene());

  //材质处理，漫反射模型
  for(auto& each : lights) {
    double cos_angle = get_cos_angle(each.direction_, local.normal);
    cos_angle = cos_angle >= 0 ? cos_angle : 0;

    int r = each.color_.r() * local.m.k_d_r_ * cos_angle;
    int b = each.color_.b() * local.m.k_d_b_ * cos_angle;
    int g = each.color_.g() * local.m.k_d_g_ * cos_angle;
    //漫反射模型计算平行光的输出。
    each.color_.set_red(r);
    each.color_.set_blue(b);
    each.color_.set_green(g);
  }

  //蒙塔卡洛积分，随机生成100个方向的光线进行追踪，与光源信息合并然后材料系数处理。
  if(current < max_depth_) {
    //稍微偏移起始点，防止找到自己这个点。
    /*
    vec3 normal = normalize(local.normal);
    point3 tiny_xp(xp.px() + normal.x_ * 0.1, xp.py() + normal.y_ * 0.1, xp.pz() + normal.z_ * 0.1);
    new_ray = ray(tiny_xp, normal);
    c4 = inner(new_ray, director_, ++current);
    c4.set_red(c4.r() * local.m.k_d_r_);
    c4.set_green(c4.g() * local.m.k_d_g_);
    c4.set_blue(c4.b() * local.m.k_d_b_);
    */
  }

  //光源和间接反射分开计算。
  int r = 0;
  int b = 0;
  int g = 0;
  for(auto& each : lights) {
    r += each.color_.r();
    b += each.color_.b();
    g += each.color_.g();
  }
  return color(r, g, b);
}
}
