#ifndef RAYTRACER_LEVEL_H
#define RAYTRACER_LEVEL_H

#include <vector>
#include <map>
#include <algorithm>
#include "Object.h"
#include "Light.h"

class Level {

  std::vector<const Object *> Objects;
  std::vector<const Light *> Lights;

public:
  Level() = default;

  void add(const Object *O) {
    Objects.push_back(O);
  }
  void add(const Light *L) {
    Lights.push_back(L);
  }

  Hit intersectWithLight(const Ray &R, const Object *Ignore = nullptr) {
    Hit H = intersect(R, Ignore);
    if (H.valid())
      lightHit(H, R);
    return H;
  }

  Hit intersect(const Ray &R, const Object *Ignore = nullptr) const {
    Hit Result;
    for (auto &O : Objects) {
      if (O == Ignore)
        continue;
      auto I = O->intersect(R, *this);
      Vec3::Unit NewDistance = I.getPos().distance(R.getStart());
      Vec3::Unit OldDistance = Result.getPos().distance(R.getStart());
      if (I.valid() && (!Result.valid() || NewDistance < OldDistance)) {
        Vec3 ToHit = I.getPos() - R.getStart();
        ToHit = ToHit.normalize();
        auto DotProduct = ToHit.dot(R.getDirection());
        if (DotProduct > 0)
          Result = I;
      }
    }
    return Result;
  }

  std::vector<Hit> intersectAll(const Ray &R) const {
    std::vector<std::pair<Vec3::Unit, Hit> > SortedResult;
    std::vector<Hit> Result;

    for (auto &O : Objects) {
      auto I = O->intersect(R, *this);
      Vec3::Unit NewDistance = I.getPos().distance(R.getStart());
      if (I.valid()) {
        SortedResult.emplace_back(NewDistance, I);
      }
    }
    std::sort(SortedResult.begin(), SortedResult.end(),
      [](const std::pair<Vec3::Unit, Hit> &A,
         const std::pair<Vec3::Unit, Hit> &B)
      {
        return A.first < B.first;
      }
    );
    for (auto &O : SortedResult)
      Result.push_back(O.second);
    return Result;
  }

  void lightHit(Hit &H, const Ray &View) const;

};


#endif //RAYTRACER_LEVEL_H
