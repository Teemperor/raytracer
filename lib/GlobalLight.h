#ifndef RAYTRACER_GLOBALLIGHT_H
#define RAYTRACER_GLOBALLIGHT_H


#include "Light.h"

class GlobalLight : public Light {

  Color C;
public:
  GlobalLight(Color C) : C(C) {
  }

  void processHit(Hit &H, const Level& L) const override {
    H.addLight(C);
  }
};


#endif //RAYTRACER_GLOBALLIGHT_H
