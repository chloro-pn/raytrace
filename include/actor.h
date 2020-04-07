#ifndef ACTOR_H
#define ACTOR_H

#include "geometry.h"
#include "material.h"
#include "mymath.h"
#include "light.h"

//actor属于场景scene，拥有材质熟悉，几何信息（顶点和法向量），可以被移动，缩放和旋转。
class actor {
public:
  struct local_information {
    material m; // 材质
    vec3 normal = vec3::zero();  // 相交处的表面法向
    point3 point = point3::zero(); // 射线与表面的交点
    double t = -1.0; // 射线参数

    enum class valid {yes, no};
    valid valid_ = valid::no; //当前局部信息是否合法，不合法的局部信息用来表示没有相交。

    bool valid() const {
      return valid_ == valid::yes;
    }
  };

  std::vector<local_information> penetrated_by_ray(ray ray_light) {
    return std::vector<local_information>();
  }

private:
  geometry geo_;
  material m_;
};

#endif // ACTOR_H
