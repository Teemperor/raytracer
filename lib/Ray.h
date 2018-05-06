#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include <cassert>
#include "Vec3.h"
#include "Color.h"

class Ray {
  Vec3 Start;
  Vec3 Direction;
  unsigned Limit;
public:
  Ray(Vec3 Start, Vec3 Direction, unsigned Limit)
      : Start(Start), Direction(Direction.normalize()), Limit(Limit) {
  }

  bool reachedRayLimit() const {
    return Limit == 0;
  }

  unsigned getNext() const {
    assert(!reachedRayLimit());
    return Limit - 1;
  }

  const Vec3 &getStart() const {
    return Start;
  }

  const Vec3 &getDirection() const {
    return Direction;
  }
};


#endif //RAYTRACER_RAY_H
