#include "../third_party/catch.hpp"
#include "../include/light.h"

TEST_CASE("light ambient test") {
  light l;
  color c = l.get_ambient_light().get_color();
  REQUIRE(c.r() == 255);
}

TEST_CASE("light parallel test") {
  light l;
  l.push_parallel_light("light1", parallel_light(color::black(), vec3(0, 0, 1)));
  const parallel_light& tmp = l.get_parallel_lights("light1");
  REQUIRE(tmp.if_init() == true);
  REQUIRE(tmp.get_color() == color(0, 0, 0));
  const point_light& tmp2 = l.get_point_lights("name");
  REQUIRE(tmp2.if_init() == false);
}
