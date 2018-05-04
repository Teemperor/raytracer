#ifndef RAYTRACER_OBJECT_H
#define RAYTRACER_OBJECT_H


#include "Ray.h"
#include "Hit.h"

class Level;

class Object {

public:
  virtual ~Object() = default;
  virtual Hit intersect(const Ray &R, const Level &L) const = 0;

};


#endif //RAYTRACER_OBJECT_H
