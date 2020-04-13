#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <array>
#include <vector>
#include <string>
#include "value_compare.h"
#include "mymath.h"
#include "ray.h"
#include "local_information.h"
#include "texture.h"

namespace pn_graphics {
//图元的集合，包括顶点坐标，拓扑关系，法向坐标。
class geometry {
private:
#pragma pack(1)
  struct triangle_ {
    float normal[3];
    float first[3];
    float second[3];
    float third[3];
    char buf[2];

    triangle_& operator=(const triangle_& other) {
      normal[0] = other.normal[0];
      normal[1] = other.normal[1];
      normal[2] = other.normal[2];
      first[0] = other.first[0];
      first[1] = other.first[1];
      first[2] = other.first[2];
      second[0] = other.second[0];
      second[1] = other.second[1];
      second[2] = other.second[2];
      third[0] = other.third[0];
      third[1] = other.third[1];
      third[2] = other.third[2];
      return *this;
    }
  };
#pragma pack()

  static_assert (sizeof(triangle_) == 50, "inner error.");

public:
  struct triangle {
    vec3 normal;
    point3 first;
    double first_x = 0;
    double first_y = 0;
    point3 second;
    double second_x = 0;
    double second_y = 0;
    point3 third;
    double third_x = 0;
    double third_y = 0;

    triangle():normal(vec3::zero()), first(point3::zero()), second(point3::zero()), third(point3::zero()) {

    }

    triangle& operator=(const triangle_& other) {
      normal.x_ = other.normal[0];
      normal.y_ = other.normal[1];
      normal.z_ = other.normal[2];
      first.px_ = other.first[0];
      first.py_ = other.first[1];
      first.pz_ = other.first[2];
      second.px_ = other.second[0];
      second.py_ = other.second[1];
      second.pz_ = other.second[2];
      third.px_ = other.third[0];
      third.py_ = other.third[1];
      third.pz_ = other.third[2];
      return *this;
    }
  };

  geometry() = default;

  explicit geometry(std::string filename);

  geometry(const geometry&) = default;

  geometry& operator=(const geometry&) = default;

  std::vector<local_information> get_loinf_from_ray(const ray& ray_);

  void push(const triangle& tri) {
    triangles_.push_back(tri);
  }

  std::pair<double, double> get_texture_coor_from_tri(const triangle& tri, const point3& point);

  static geometry tetrahedron();

private:
  std::vector<triangle> triangles_;
  texture texture_;
};
}
#endif // GEOMETRY_H
