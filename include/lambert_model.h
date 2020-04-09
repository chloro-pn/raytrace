#ifndef LAMBERT_MODEL_H
#define LAMBERT_MODEL_H

#include "lighting_model.h"
#include "color.h"

namespace pn_graphics {
class lambert_model : public lighting_model {
public:
  color get_color_from_ray(ray, director*) override;

  lambert_model();
};
}

#endif // LAMBERT_MODEL_H
