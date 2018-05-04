#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include "Object.h"

class Sphere : public Object {

public:
  Hit intersect(const Ray &R, const Level &L) const override {
    return Hit();
  }
};


#endif //RAYTRACER_SPHERE_H
