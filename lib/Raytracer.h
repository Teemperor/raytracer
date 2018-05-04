#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H


#include <iostream>
#include <thread>
#include "Level.h"

class Raytracer {
  Level &L;

  Vec3 Pos;
  Vec3 Direction = Vec3(1, 0, 0);
  double FOV = 90;

  int Jobs;
  int Width = 1;
  int Height = 1;

public:
  explicit Raytracer(Level &L) : L(L) {
    Jobs = std::thread::hardware_concurrency();
    --Jobs;
    if (Jobs <= 0)
      Jobs = 1;
  }

  void setRenderSize(int W, int H) {
    Width = W;
    Height = H;
  }

  void setPos(const Vec3 &P) {
    Pos = P;
  }

  void setViewDirection(Vec3 D) {
    Direction = D;
  }

  void trace(std::vector<Color> &Buffer) {
    auto DataPerJob = Buffer.size() / Jobs;
    std::vector<std::thread *> Threads;

    for (std::size_t Start = 0; Start < Buffer.size(); Start += DataPerJob) {
      std::thread *T = new std::thread([this, Start, DataPerJob, &Buffer](){
        for (std::size_t I = Start; I < Start + DataPerJob; ++I) {
          int x = I % Width;
          int y = I / Width;
          const Vec3 TargetCenter = Pos + Direction.normalize() * 100;

          const Vec3 ToTargetCenter = TargetCenter - Pos;
          const Vec3 Up(0, 0, 1);

          double XP = (x / (float) Width - 0.5f) * 20;
          double YP = (y / (float) Height - 0.5f) * 20;

          const Vec3 LeftFromTarget = Up.crossProduct(ToTargetCenter).normalize();
          const Vec3 UpFromTarget = LeftFromTarget.crossProduct(ToTargetCenter).normalize();

          const Vec3 DirectionToPixel = ToTargetCenter + LeftFromTarget * XP + UpFromTarget * YP;

          Ray R(Pos, DirectionToPixel.normalize());
          Hit H = L.intersect(R);
          if (H.valid()) {
            L.lightHit(H);
            Buffer[x + y * Width] = H.getColor();
          }
        }
      });
      Threads.push_back(T);
    }
    for (auto &T : Threads)
      T->join();
  }
};


#endif //RAYTRACER_RAYTRACER_H
