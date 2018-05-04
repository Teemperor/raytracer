#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "Vec3.h"
#include "Color.h"

class Ray {
  Vec3 Start;
  Vec3 Direction;
public:
  Ray(Vec3 Start, Vec3 Direction) : Start(Start),
                                    Direction(Direction.normalize()) {
  }

  const Vec3 &getStart() const {
    return Start;
  }

  const Vec3 &getDirection() const {
    return Direction;
  }
};


#endif //RAYTRACER_RAY_H
