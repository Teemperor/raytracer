#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include <algorithm>
#include "Object.h"

class Sphere : public Object {

  Vec3 Center;
  Vec3::Unit Radius;
  Color C;

public:
  Sphere(Vec3 Center, Vec3::Unit Radius, Color C)
      : Center(Center), Radius(Radius), C(C) {
  }

  bool collides(const Sphere &S) const {
    return Center.distance(S.Center) <= S.Radius + Radius;
  }

  Hit intersect(const Ray &R, const Level &) const override {
    const Vec3 L = R.getDirection();
    const Vec3 O = R.getStart();

    Vec3::Unit OMinusC = (O - Center).length();

    const Vec3::Unit LDotOC = L.dot((O - Center));

    Vec3::Unit S = LDotOC * LDotOC - OMinusC * OMinusC + Radius * Radius;

    if (S < 0) {
      return Hit::missed();
    }

    S = std::sqrt(S);

    Vec3::Unit D1 = -LDotOC + S;
    Vec3::Unit D2 = -LDotOC - S;

    auto HitPoint1 = D1 * L + O;
    auto HitPoint2 = D2 * L + O;

    Vec3 HitPoint;
    if (HitPoint1.distance(R.getStart()) < HitPoint2.distance(R.getStart()))
      HitPoint = HitPoint1;
    else
      HitPoint = HitPoint2;

    auto Normal = HitPoint - Center;
    return Hit(HitPoint, Normal.normalize(), C, this);
  }
};


#endif //RAYTRACER_SPHERE_H
