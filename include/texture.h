#ifndef TEXTURE_H
#define TEXTURE_H

#include <QImage>
#include <string>
#include "color.h"

namespace pn_graphics {
class texture {
private:
  QImage image_;

public:
  texture() = default;

  void load(const char* filename) {
    image_.load(filename);
  }

  int height() const {
    return image_.height();
  }

  int width() const {
    return image_.width();
  }

  color pixel(int w, int h) const {
    QRgb rgb = image_.pixel(w, h);
    color result(qRed(rgb), qGreen(rgb), qBlue(rgb));
    return result;
  }

  bool valid(int w, int h) const {
    return (w >= 0 && w < width() && h >= 0 && h < height());
  }
};
}

#endif // TEXTURE_H
