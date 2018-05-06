#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H


#include <cstdint>
#include <algorithm>

class Color {
  uint8_t R, G, B, A;

  template<typename T>
  uint8_t clamp(T V) const {
    if (V <= 0)
      return 0u;
    if (V >= 255)
      return 255;
    return static_cast<uint8_t >(V);
  }

public:
  Color() = default;
  Color(uint8_t R, uint8_t G, uint8_t B, uint8_t A = 255)
    : R(R), G(G), B(B), A(A) {
  }

  Color operator*(double F) const {
    return Color(clamp(R * F),
                 clamp(G * F),
                 clamp(B * F), A);
  }

  Color operator+(const Color& C) const {
    return Color(clamp((int)R + (int)C.R),
                 clamp((int)G + (int)C.G),
                 clamp((int)B + (int)C.B), A);
  }

  float asFactor() const {
    return R / 255.0f;
  }

  uint8_t getAlpha() const {
    return A;
  }

  double getAlphaPercentage() const {
    return A / 255.0;
  }

  Color drawOver(const Color &Other) const {
    const int DR = Other.R - (int) R;
    const int DG = Other.G - (int) G;
    const int DB = Other.B - (int) B;

    double Strength = Other.getAlphaPercentage();

    return Color(static_cast<uint8_t>(clamp(R + DR * Strength)),
                 static_cast<uint8_t>(clamp(G + DG * Strength)),
                 static_cast<uint8_t>(clamp(B + DB * Strength)),
                 std::max(A, Other.A));
  }
};


#endif //RAYTRACER_COLOR_H
