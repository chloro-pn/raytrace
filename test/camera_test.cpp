#include "../include/camera.h"
#include "../include/mymath.h"
#include "../third_party/catch.hpp"

TEST_CASE("camera right test") {
  camera cam(800, 600);
  REQUIRE(cam.right() == normalize(vec3(1, 0, 0)));
  cam.set_lookat(vec3(-1, 0, -1));
  REQUIRE(cam.right() == normalize(vec3(1, 0, -1)));
}

TEST_CASE("camera ratio test") {
  camera cam(800, 600);
  point3 location = cam.get_view_point_from_ratio(0.5, 0.5);
  REQUIRE(location == point3(0, 0, 0));
  cam.set_location(point3(100, 200, 300));
  location = cam.get_view_point_from_ratio(0.8, 0.6);
  REQUIRE(location == point3(100 + 800 * 0.3, 200 + 600 * 0.1, 300));
}
