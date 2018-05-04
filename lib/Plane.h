#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H


#include <cassert>
#include "Object.h"

class Plane : public Object {

  Vec3 Coordinate;
  Vec3 Normal;
  Color C;

public:
  Plane(Vec3 Start, Vec3 Normal, Color C)
      : Coordinate(Start), Normal(Normal), C(C) {

  }

  Vec3 getCoord() const {
    return Coordinate;
  }

  void setCoord(Vec3 V) {
    Coordinate = V;
  }

  Vec3 getNormal() const {
    return Normal;
  }


  Hit intersect(const Ray &R) const override {
    // get d value
    Vec3::Unit d = Normal.dot(Coordinate);

    if (Normal.dot(R.getDirection()) == 0) {
      return Hit::missed();
    }

    // Compute the X value for the directed line ray intersecting the plane
    Vec3::Unit x = (d - Normal.dot(R.getStart())) / Normal.dot(R.getDirection());

    Vec3 Point = R.getStart() + R.getDirection() * x;
    assert(!std::isnan(Point.getX()));
    assert(!(Point.getX() > 40 && Point.getY() > 40 && Point.getZ() > 40));
    return Hit(Point, Normal, C, this);
  }
};


#endif //RAYTRACER_PLANE_H
