#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <array>
#include <vector>
#include "value_compare.h"
#include "mymath.h"
#include "light.h"
#include "local_information.h"

//图元的集合，包括顶点坐标，拓扑关系，法向坐标。
class geometry {
public:

  /*
   * 外部三角面片信息输入。
   */
  struct triangle {
    vec3 normal;
    point3 first;
    point3 second;
    point3 third;

    triangle():normal(vec3::zero()), first(point3::zero()), second(point3::zero()), third(point3::zero()) {

    }
  };

  geometry() = default;

  geometry(const geometry&) = default;

  geometry& operator=(const geometry&) = default;

  std::vector<local_information> get_loinf_from_ray(ray ray_);

  void push(const triangle& tri) {
    triangles_.push_back(tri);
  }

  static geometry tetrahedron();

private:
  std::vector<triangle> triangles_;
};

#endif // GEOMETRY_H
