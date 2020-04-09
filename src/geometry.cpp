#include "../include/geometry.h"
#include "../include/value_compare.h"
#include "../include/mymath.h"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <vector>
#include <fstream>
#include <QDebug>

namespace pn_graphics {

geometry::geometry(std::string filename) {
  std::ifstream in(filename, std::ios::binary);
  if (!in.good()) {
    fprintf(stderr, "file %s open error.", filename.c_str());
    std::abort();
  }
  char information[128] = {0};
  uint32_t numbers = 0;
  in.read(information, 80);
  in.read((char*)&numbers, 4);

  triangle_ tmp;
  triangle tri;
  for (size_t i = 0; i < numbers; ++i) {
    in.read((char*)&tmp, sizeof(tmp));
    if (in.good() == false) {
      fprintf(stderr, "file error when reading.");
      std::abort();
    }
    tri = tmp;
    triangles_.push_back(tri);
  }
  in.close();
}

static std::vector<double> get_coeff_from_points(const geometry::triangle& tri) {
  std::vector<double> result;
  result.push_back(tri.normal.x_);
  result.push_back(tri.normal.y_);
  result.push_back(tri.normal.z_);
  double tmp = tri.first.px() * tri.normal.x_ + tri.first.py() * tri.normal.y_ + tri.first.pz() * tri.normal.z_;
  result.push_back(-tmp);
  return result;
}

static double get_t_from_ray_and_triangle(const ray& ray_, const geometry::triangle& tri_) {
  auto coeffs = get_coeff_from_points(tri_);
  assert(coeffs.size() == 4);
  double A = coeffs[0];
  double B = coeffs[1];
  double C = coeffs[2];
  double D = coeffs[3];

  double tmp1 = A * ray_.origin.px() + B * ray_.origin.py() + C * ray_.origin.pz() + D;
  tmp1 = -tmp1;
  double tmp2 = A * ray_.direction.x_ + B * ray_.direction.y_ + C * ray_.direction.z_;
  if(value_equal(tmp2, 0.0)) {
    return -1.0;
  }
  return tmp1 / tmp2;
}

/*
 * 依次遍历每一个三角形
 * 对射线和三角形进行求交点运算，得到t，如果t <= 0，跳过本三角形
 * 根据t计算得到面上交点，判断交点是否在三角形内，如果不在，跳过本三角形
 * 将三角形的法向量和交点构造local_information并放入result中
 * 循环结束，返回。
 */
std::vector<local_information> geometry::get_loinf_from_ray(const ray& ray_) {
  std::vector<local_information> result;
  for(auto& each : triangles_) {
    double t = get_t_from_ray_and_triangle(ray_, each);
    if(value_se(t, 0.0) == true) {
      continue;
    }
    //判断点是不是在三角形内部
    point3 p(ray_.origin.px() + t * ray_.direction.x_, ray_.origin.py() + t * ray_.direction.y_, ray_.origin.pz() + t * ray_.direction.z_);
    vec3 v1(p, each.first);
    vec3 v2(p, each.second);
    vec3 v3(p, each.third);
    if(v1 != vec3::zero() && v2 != vec3::zero() && v3 != vec3::zero()) {
      double angle_total = get_angle(v1, v2) + get_angle(v1, v3) + get_angle(v2, v3);
      if(!value_equal(angle_total, 2 * M_PI)) {
        continue;
      }
    }

    local_information tmp;
    tmp.t = t;
    tmp.normal = each.normal;
    tmp.valid_ = local_information::valid::yes;
    result.push_back(tmp);
  }
  return result;
}

geometry geometry::tetrahedron() {
  geometry geo;
  point3 p1(0, 0, 0);
  point3 p2(-100, 0, -100);
  point3 p3(150, 0, -100);
  point3 p4(0, 50, 0);

  geometry::triangle tri;
  tri.first = p1;
  tri.second = p2;
  tri.third = p3;
  vec3 n1(normalize(vec3(p1, p2).cross(vec3(p1, p3))));
  tri.normal = n1;
  geo.push(tri);

  tri.third = p4;
  vec3 n2(normalize(vec3(p2, p1).cross(vec3(p2, p4))));
  tri.normal = n2;
  geo.push(tri);

  tri.second = p3;
  vec3 n3(normalize(vec3(p1, p3).cross(vec3(p1, p4))));
  tri.normal = n3;
  geo.push(tri);

  tri.first = p2;
  vec3 n4(normalize(vec3(p4, p3).cross(vec3(p4, p2))));
  tri.normal = n4;
  geo.push(tri);

  return geo;
}

}
