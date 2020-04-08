#ifndef LIGHTING_MODEL_H
#define LIGHTING_MODEL_H

namespace pn_graphics {
class color;
class director;
class ray;

class lighting_model {
public:
  virtual color get_color_from_ray(ray, director*) = 0;

  virtual ~lighting_model() {

  }
};
}
#endif // LIGHTING_MODEL_H
