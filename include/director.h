#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "camera.h"
#include "light.h"
#include "screen.h"
#include "scene.h"
#include "lighting_model.h"
#include <memory>

namespace pn_graphics {
//导演类是掌管整个渲染空间的类
class director {
public:
  director(screen* scr, std::unique_ptr<lighting_model> lm):camera_(),
                                                            scr_(scr),
                                                            scene_(),
                                                            lm_(std::move(lm)) {

  }

  void render() {
    camera_.render_before();
    int w = scr_->width();
    int h = scr_->height();
    for(int i = 0; i < w; ++i) {
      for(int j = 0; j < h; ++j) {
        //光线追踪计算每个像素点的颜色。
        double r1 = scr_->get_w_ratio(i);
        double r2 = scr_->get_h_ratio(j);
        point3 origin = camera_.get_view_point_from_ratio(r1, r2);
        vec3 direction = camera_.lookat();
        //将代表视线的射线交给光照模型，获取颜色。
        color result = lm_->get_color_from_ray(ray(origin, direction), this);
        scr_->set_color(i, j, result);
      }
    }
  }

  camera& get_camera() {
    return camera_;
  }

  light& get_light() {
    return light_;
  }

  scene& get_scene() {
    return scene_;
  }

  screen* get_screen() {
    return scr_;
  }

private:
  camera camera_;
  light light_;
  screen* scr_;
  scene scene_;
  std::unique_ptr<lighting_model> lm_;
};
}
#endif // DIRECTOR_H
