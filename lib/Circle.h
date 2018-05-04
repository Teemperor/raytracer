#ifndef RAYTRACER_CIRCLE_H
#define RAYTRACER_CIRCLE_H


#include <iostream>
#include "Object.h"
#include "Plane.h"

class Circle : public Object {
  Plane P;
  Vec3::Unit Radius;
public:
  Circle(Vec3 Center, Vec3 Normal, Color C, Vec3::Unit Radius)
      : P(Center, Normal, C), Radius(Radius) {
  }

  Hit intersect(const Ray &R) const override {
    Hit I = P.intersect(R);
    if (I.valid()) {
      I.setHitObject(this);
      Vec3::Unit Distance = P.getCoord().distance(I.getPos());
      if (Distance > Radius) {
        I = Hit::missed();
      } else {
        return I;
      }
    }
    return I;
  }

  void setPos(Vec3 V) {
    P.setCoord(V);
  }

  Vec3 getPos() const {
    return P.getCoord();
  }
};


#endif //RAYTRACER_CIRCLE_H
