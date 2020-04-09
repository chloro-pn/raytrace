#ifndef LAMBERT_MODEL_H
#define LAMBERT_MODEL_H

#include "lighting_model.h"
#include "color.h"

namespace pn_graphics {
class lambert_model : public lighting_model {
public:
  color get_color_from_ray(const ray&, director*) override;

  lambert_model(int depth = 0);

private:
  int max_depth_;

  color inner(const ray& ray_, director* director_, int current);
};
}

#endif // LAMBERT_MODEL_H
