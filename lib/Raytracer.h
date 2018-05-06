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

  int Jobs = 1;
  unsigned Width = 1;
  unsigned Height = 1;

  unsigned SSWidth = 1;
  unsigned SSHeight = 1;

  std::vector<Color> Buffer;
  std::vector<Color> SSBuffer;

  void renderSS();

  Color computeAverage(const std::vector<Color> &Samples) {
    int RSum = 0;
    int GSum = 0;
    int BSum = 0;
    for (const Color &C : Samples) {
      RSum += C.getR();
      GSum += C.getG();
      BSum += C.getB();
    }
    return Color(static_cast<uint8_t>(RSum / Samples.size()),
                 static_cast<uint8_t>(GSum / Samples.size()),
                 static_cast<uint8_t>(BSum / Samples.size()));
  }

  Color getSSPixel(int x, int y) {
    x = std::max(0, std::min(x, (int) SSWidth - 1));
    y = std::max(0, std::min(y, (int) SSHeight - 1));
    return SSBuffer[x + y * SSWidth];
  }

  void sampleToBuffer();

public:
  explicit Raytracer(Level &L);

  void setRenderSize(unsigned W, unsigned H) {
    Width = W;
    Height = H;
    Buffer.resize(Width * Height, Color(0, 0, 0));
  }

  void setSuperSamplingSize(unsigned W, unsigned H) {
    SSWidth = W;
    SSHeight = H;
    SSBuffer.resize(SSWidth * SSHeight, Color(0, 0, 0));
  }

  const std::vector<Color> &getBuffer() const {
    return Buffer;
  }

  void setPos(const Vec3 &P) {
    Pos = P;
  }

  void setViewDirection(Vec3 D) {
    Direction = D;
  }

  void render() {
    renderSS();
    sampleToBuffer();
  }
};


#endif //RAYTRACER_RAYTRACER_H
