#ifndef ACTOR_H
#define ACTOR_H

#include "geometry.h"
#include "local_information.h"
#include "light.h"

//actor属于场景scene，拥有材质熟悉，几何信息（顶点和法向量），可以被移动，缩放和旋转。
class actor {
public:
  std::vector<local_information> penetrated_by_ray(ray ray_light) {
    auto results = geo_.get_loinf_from_ray(ray_light);
    for(auto& each : results) {
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

#endif // ACTOR_H
