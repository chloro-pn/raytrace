#ifndef PHONG_MODEL_H
#define PHONG_MODEL_H

#include "lighting_model.h"
#include "local_information.h"
#include "color.h"

namespace pn_graphics {
class phong_model : public lighting_model {
public:
  color get_color_from_ray(const ray&, director*) override;

  phong_model(int depth = 0);

private:
  int max_depth_;

  color inner(const ray& ray_, director* director_, int current);

  color get_reflected_light(const ray&, const local_information&, director*, int);
};
}

#endif // PHONG_MODEL_H
