#ifndef SIMPLE_MODEL_H
#define SIMPLE_MODEL_H

#include "lighting_model.h"
#include "color.h"

namespace pn_graphics {
class simple_model : public lighting_model {
public:
  color get_color_from_ray(ray, director*) override;

  explicit simple_model(color env);

private:
  color background_color_;
  color env_color_;
};
}
#endif // SIMPLE_MODEL_H
