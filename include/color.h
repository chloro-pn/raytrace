#ifndef COLOR_H
#define COLOR_H
namespace pn_graphics {
class color {
private:
  int r_;
  int g_;
  int b_;

public:

  static color white() {
    return color(255, 255, 255);
  }

  static color black() {
    return color(0, 0, 0);
  }

  color(int r,int g, int b):r_(r), g_(g), b_(b) {

  }

  bool operator==(const color& other) const {
    return r_ == other.r_ && g_ == other.g_ && b_ == other.b_;
  }

  color operator+(const color& other) const {
    color result(color::white());
    result.set_red( r_ + other.r_);
    result.set_green( g_ + other.g_);
    result.set_blue( b_ + other.b_);
    return result;
  }

  void set_red(int r) {
    if(r > 255) {
      r_ = 255;
    }
    else if(r < 0) {
      r_ = 0;
    }
    else {
      r_ = r;
    }
  }

  void set_green(int g) {
    if(g > 255) {
      g_ = 255;
    }
    else if(g < 0) {
      g_ = 0;
    }
    else {
      g_ = g;
    }
  }

  void set_blue(int b) {
    if(b > 255) {
      b_ = 255;
    }
    else if(b < 0) {
      b_ = 0;
    }
    else {
      b_ = b;
    }
  }

  int r() const {
    return r_;
  }

  int g() const {
    return g_;
  }

  int b() const {
    return b_;
  }
};
}
#endif // COLOR_H
