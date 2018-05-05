#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H


#include "Hit.h"

class Level;
class Ray;

class Light {

public:
  virtual ~Light() = default;
  virtual void processHit(Hit &H, const Ray& View, const Level& L) const = 0;
};


#endif //RAYTRACER_LIGHT_H
