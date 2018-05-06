#include "Mirror.h"

#include "Level.h"

Hit Mirror::intersect(const Ray &R, const Level &L) const {
  Hit I = Rectangle::intersect(R, L);
  if (I.valid()) {
    I.setHitObject(this);

    auto D = R.getDirection();
    Vec3 ReflectionVec = D - 2 * (D.dot(I.getNormal())) * I.getNormal();

    Ray Reflect(I.getPos(), ReflectionVec.normalize(), R.getNext());
    return L.intersect(Reflect, this);
  }
  return I;
}
