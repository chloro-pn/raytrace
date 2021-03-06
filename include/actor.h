#ifndef ACTOR_H
#define ACTOR_H

#include "geometry.h"
#include "local_information.h"
#include "ray.h"

//actor属于场景scene，拥有材质熟悉，几何信息（顶点和法向量），可以被移动，缩放和旋转。
namespace pn_graphics {
class actor {
public:
  std::vector<local_information> penetrated_by_ray(ray ray_) {
    auto results = geo_.get_loinf_from_ray(ray_);
    for(auto& each : results) {
      double t = each.t;
      point3 p(ray_.origin.px() + t * ray_.direction.x_, ray_.origin.py() + t * ray_.direction.y_, ray_.origin.pz() + t * ray_.direction.z_);
      each.m = m_;
    }
    return results;
  }

  actor(geometry geo, material m):geo_(geo), m_(m) {

  }

private:
  geometry geo_;
  material m_;
};
}
#endif // ACTOR_H
