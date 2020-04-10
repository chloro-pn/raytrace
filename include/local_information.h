#ifndef LOCAL_INFORMATION_H
#define LOCAL_INFORMATION_H

#include "material.h"
#include "mymath.h"
#include "color.h"

namespace pn_graphics {
struct local_information {
  material m; // 材质
  vec3 normal = vec3::zero();  // 相交处的表面法向
  double t = -1.0; // 射线参数

  color texture_color = color::black();

  enum class valid {yes, no};
  valid valid_ = valid::no; //当前局部信息是否合法，不合法的局部信息用来表示没有相交。

  bool valid() const {
    return valid_ == valid::yes;
  }
};
}
#endif // LOCAL_INFORMATION_H
