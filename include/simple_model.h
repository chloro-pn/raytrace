#ifndef SIMPLE_MODEL_H
#define SIMPLE_MODEL_H

#include "lighting_model.h"
#include "color.h"

namespace pn_graphics {
class simple_model : public lighting_model {
public:
  color get_color_from_ray(const ray&, director*) override;

  simple_model();
};
}
#endif // SIMPLE_MODEL_H
