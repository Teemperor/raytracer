#ifndef RAYTRACER_RECTANGLE_H
#define RAYTRACER_RECTANGLE_H


#include <utility>
#include "Object.h"
#include "Plane.h"

class Rectangle : public Object {
  Plane P;

  int Width;
  int Height;

public:
  Rectangle(Vec3 Center, Vec3 Normal, Color C, std::pair<int, int> Size)
  : P(Center, Normal, C), Width(Size.first), Height(Size.second) {
  }

  void setSize(std::pair<int, int> Size) {
    Width = Size.first;
    Height = Size.second;
  }

  Hit intersect(const Ray &R) const override {
    Hit I = P.intersect(R);
    if (I.valid()) {
      I.setHitObject(this);

      const Vec3 FromCenter = I.getPos() - P.getCoord();

      Vec3 RandomVec = P.getNormal().getRandomOther();

      Vec3 VecOnPlane = P.getNormal().crossProduct(RandomVec);

      const Vec3 Projection = FromCenter.projection(VecOnPlane);
      const Vec3 Rejection = FromCenter.rejection(VecOnPlane);

      int x = static_cast<int>(Projection.length()) + Width / 2;
      int y = static_cast<int>(Rejection.length()) + Height / 2;
      if (x > 0 && y > 0 && x < Width && y < Height) {
        return I;
      } else {
        return Hit::missed();
      }
    }
    return I;
  }

  Vec3 getNormal() const {
    return P.getNormal();
  }

  Vec3 getCenter() const {
    return P.getCoord();
  }

  int getWidth() const {
    return Width;
  }

  int getHeight() const {
    return Height;
  }
};


#endif //RAYTRACER_RECTANGLE_H
