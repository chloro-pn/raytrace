#ifndef SCREEN_H
#define SCREEN_H

#include "color.h"
#include <cassert>

namespace pn_graphics {
class screen {
private:
  int width_;
  int height_;

public:
  screen(int w, int h):width_(w), height_(h) {
    assert(width_ > 0);
    assert(height_ > 0);
  }

  virtual void set_color(int dw, int dh, color c) = 0;

  int width() const {
    return width_;
  }

  int height() const {
    return height_;
  }

  double get_w_ratio(double w) const {
    return w / width_;
  }

  double get_h_ratio(double h) const {
    return h / height_;
  }

  void resize(int w, int h) {
    width_ = w;
    height_ = h;
    assert(width_ > 0);
    assert(height_ > 0);
  }

  virtual ~screen() {

  }
};
}
#endif // SCREEN_H
