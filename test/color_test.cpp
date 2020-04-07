#include "../third_party/catch.hpp"
#include "../include/color.h"

TEST_CASE("color test") {
  color c(100, 100, 100);
  c.set_red(512);
  c.set_blue(-400);
  c.set_green(128);
  REQUIRE(c.r() == 255);
  REQUIRE(c.b() == 0);
  REQUIRE(c.g() == 128);
}
