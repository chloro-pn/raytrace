#include "../third_party/catch.hpp"
#include "../include/mymath.h"
#include "../include/value_compare.h"
#include <cmath>

TEST_CASE("normalize test") {
  vec3 v1(2, 1, 0);
  vec3 v2 = normalize(v1);
  REQUIRE(value_equal((double)v2.x_, 2 / std::sqrt(double(5))));
  REQUIRE(value_equal(1.0, double(v2.x_ * v2.x_ + v2.y_ * v2.y_ + v2.z_ * v2.z_)));
}

TEST_CASE("vertical test") {
  vec3 v1(1, 0, 0);
  vec3 v2(0, 1, 0);
  REQUIRE(vertical(v1, v2) == true);
  vec3 v3(1, 1, 0);
  REQUIRE(vertical(v1, v3) == false);
}
