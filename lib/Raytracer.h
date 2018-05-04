#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H


#include <iostream>
#include "Level.h"

class Raytracer {
  Level &L;

  Vec3 Pos;
  Vec3 Direction = Vec3(1, 0, 0);
  double FOV = 90;

public:
  explicit Raytracer(Level &L) : L(L) {
  }

  void setPos(const Vec3 &P) {
    Pos = P;
  }

  void setViewDirection(Vec3 D) {
    Direction = D;
  }

  void trace(std::vector<Color> &Buffer, int W, int H) {
    for (int x = 0; x < W; ++x) {
      for (int y = 0; y < H; ++y) {
        const Vec3 TargetCenter = Pos + Direction.normalize() * 100;

        const Vec3 ToTargetCenter = TargetCenter - Pos;
        const Vec3 Up(0, 0, 1);

        double XP = (x / (float) W - 0.5f) * 20;
        double YP = (y / (float) W - 0.5f) * 20;

        const Vec3 LeftFromTarget = Up.crossProduct(ToTargetCenter).normalize();
        const Vec3 UpFromTarget = LeftFromTarget.crossProduct(ToTargetCenter).normalize();

        const Vec3 DirectionToPixel = ToTargetCenter + LeftFromTarget * XP + UpFromTarget * YP;

        Ray R(Pos, DirectionToPixel.normalize());
        Hit H = L.intersect(R);
        if (H.valid()) {
          L.lightHit(H);
          Buffer[x + y * W] = H.getColor();
        }
      }
    }
  }
};


#endif //RAYTRACER_RAYTRACER_H
