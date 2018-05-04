#ifndef RAYTRACER_HIT_H
#define RAYTRACER_HIT_H

#include "Vec3.h"
#include "Color.h"

class Object;

class Hit {
  Vec3 Pos;
  Vec3 Normal;
  Color C;
  const Object *Obj;
  bool Valid = false;

public:
  Hit() = default;
  Hit(Vec3 Pos, Vec3 Normal, Color C, const Object *Obj)
      : Pos(Pos), Normal(Normal), C(C), Obj(Obj) {
    Valid = true;
  }
  static Hit missed() {
    return Hit();
  }

  void setColor(const Color &C) {
    this->C = C;
  }

  const Color &getColor() const {
    return C;
  }

  const Vec3 &getPos() const {
    return Pos;
  }

  const Vec3 &getNormal() const {
    return Normal;
  }

  const Object *getHitObject() const {
    return Obj;
  }

  void setHitObject(const Object *Obj) {
    Hit::Obj = Obj;
  }

  bool valid() const {
    return Valid;
  }
};

#endif //RAYTRACER_HIT_H
