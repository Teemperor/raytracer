#ifndef RAYTRACER_MIRROR_H
#define RAYTRACER_MIRROR_H


#include "Rectangle.h"

class Mirror : public Rectangle {
public:
  Mirror(Vec3 Center, Vec3 Normal, std::pair<int, int> Size)
  : Rectangle(Center, Normal, Color(), Size) {
  }

  Hit intersect(const Ray &R, const Level &L) const override;
};


#endif //RAYTRACER_MIRROR_H
