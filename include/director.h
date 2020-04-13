#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "camera.h"
#include "light.h"
#include "screen.h"
#include "scene.h"
#include "lighting_model.h"
#include "thread_pool.h"
#include <memory>

namespace pn_graphics {
//导演类是掌管整个渲染空间的类
class director {
public:
  director(screen* scr, std::unique_ptr<lighting_model> lm):camera_(),
                                                            scr_(scr),
                                                            scene_(),
                                                            lm_(std::move(lm)),
                                                            pool_(4){
    pool_.start();
  }

  void render() {
    camera_.render_before();
    int w = scr_->width();
    int h = scr_->height();
    for(int i = 0; i < w; ++i) {
      pool_.push_task([i, this, h]()->void {
        for(int j = 0; j < h; ++j) {
          //每个像素分为5个视点进行抗锯齿处理。
          double r1 = scr_->get_w_ratio(double(i));
          double r2 = scr_->get_h_ratio(double(j));
          point3 origin = camera_.get_view_point_from_ratio(r1, r2);
          vec3 direction = camera_.lookat();
          //将代表视线的射线交给光照模型，获取颜色。
          color c0 = lm_->get_color_from_ray(ray(origin, direction), this);

          r1 = scr_->get_w_ratio(double(i) - 0.5);
          r2 = scr_->get_h_ratio(double(j) - 0.5);
          origin = camera_.get_view_point_from_ratio(r1, r2);
          direction = camera_.lookat();
          //将代表视线的射线交给光照模型，获取颜色。
          color c1 = lm_->get_color_from_ray(ray(origin, direction), this);

          r1 = scr_->get_w_ratio(double(i) - 0.5);
          r2 = scr_->get_h_ratio(double(j) + 0.5);
          origin = camera_.get_view_point_from_ratio(r1, r2);
          direction = camera_.lookat();
          //将代表视线的射线交给光照模型，获取颜色。
          color c2 = lm_->get_color_from_ray(ray(origin, direction), this);

          r1 = scr_->get_w_ratio(double(i) + 0.5);
          r2 = scr_->get_h_ratio(double(j) - 0.5);
          origin = camera_.get_view_point_from_ratio(r1, r2);
          direction = camera_.lookat();
          //将代表视线的射线交给光照模型，获取颜色。
          color c3 = lm_->get_color_from_ray(ray(origin, direction), this);

          r1 = scr_->get_w_ratio(double(i) + 0.5);
          r2 = scr_->get_h_ratio(double(j) + 0.5);
          origin = camera_.get_view_point_from_ratio(r1, r2);
          direction = camera_.lookat();
          //将代表视线的射线交给光照模型，获取颜色。
          color c4 = lm_->get_color_from_ray(ray(origin, direction), this);

          //对4个颜色做均值处理。
          int r = (c0.r() + c1.r() + c2.r() + c3.r() + c4.r()) / 5.0;
          int g = (c0.g() + c1.g() + c2.g() + c3.g() + c4.g()) / 5.0;
          int b = (c0.b() + c1.b() + c2.b() + c3.b() + c4.b()) / 5.0;
          scr_->set_color(i, j, color(r, g, b));
        }
        this->update();
      });
    }
    update();
  }

  void set_update(const std::function<void()>& func) {
    update_func_ = func;
  }

  void update() {
    if(update_func_) {
      update_func_();
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

  ~director() {
    pool_.stop();
  }

private:
  camera camera_;
  light light_;
  screen* scr_;
  scene scene_;
  std::unique_ptr<lighting_model> lm_;
  ThreadPool pool_;
  std::function<void()> update_func_;
};
}
#endif // DIRECTOR_H
