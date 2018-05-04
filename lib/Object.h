#ifndef RAYTRACER_OBJECT_H
#define RAYTRACER_OBJECT_H


#include "Ray.h"
#include "Hit.h"

class Object {

public:
  virtual ~Object() = default;
  virtual Hit intersect(const Ray &R) const = 0;

};


#endif //RAYTRACER_OBJECT_H
