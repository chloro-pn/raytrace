#ifndef SCENE_H
#define SCENE_H

#include "actor.h"
#include "color.h"
#include "light.h"
#include "local_information.h"
#include <list>
#include <memory>

namespace pn_graphics {
class scene {
public:
  scene(color background_c):background_color_(background_c) {

  }

  void push(std::shared_ptr<actor> act) {
    std::weak_ptr<actor> actor = act;
    actors_.push_back(actor);
  }

  const color& background_color() const {
    return background_color_;
  }

  local_information get_loinf_from_ray(const ray& ray_) {
    std::vector<local_information> locals;
    for(auto it = actors_.begin(); it!= actors_.end();) {
      std::shared_ptr<actor> act = it->lock();
      if(act) {
        auto results = act->penetrated_by_ray(ray_);
        for(auto& each: results) {
          locals.push_back(each);
        }
        ++it;
      }
      else {
        it = actors_.erase(it);
      }
    }
    std::sort(locals.begin(), locals.end(), [](const local_information& li1, const local_information& li2)-> bool {
      return li1.t < li2.t;
    });
    for(auto& each : locals) {
      //返回第一个与射线相交的局部信息
      if(value_b(each.t, 0.0) == true) {
        return each;
      }
    }

    //没有合法的相交或者locals根本为空
    local_information li;
    li.valid_ = local_information::valid::no;
    return li;
  }

private:
  std::list<std::weak_ptr<actor>> actors_;
  color background_color_;
};
}
#endif // SCENE_H
