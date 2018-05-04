#ifndef RAYTRACER_TEXTURERECT_H
#define RAYTRACER_TEXTURERECT_H


#include <string>
#include <SFML/Graphics/Image.hpp>
#include <iostream>
#include "Vec3.h"
#include "Object.h"
#include "Plane.h"

class TextureRect : public Object {
  sf::Image Img;
  Plane P;

  int Width;
  int Height;
  float Scale;

  Color getColor(int x, int y) const {
    if (x < 0 || y < 0 || x >= Width|| y >= Height) {
      return Color(0, 0, 0, 0);
    }
    sf::Color C = Img.getPixel(x, y);
    return Color(C.r, C.g, C.b, C.a);
  }

public:
  TextureRect(Vec3 Center, Vec3 Normal, const std::string &Path, float Scale)
    : P(Center, Normal, Color()), Scale(Scale) {
    if (!Img.loadFromFile(Path)) {
      std::cerr << "Failed to load texture " << Path << "\n";
    }
    Width = Img.getSize().x;
    Height = Img.getSize().y;
  }

  Hit intersect(const Ray &R) const override {
    Hit I = P.intersect(R);
    if (I.valid()) {
      const Vec3 FromCenter = I.getPos() - P.getCoord();

      Vec3 RandomVec = P.getNormal().getRandomOther();

      Vec3 VecOnPlane = P.getNormal().crossProduct(RandomVec);

      const Vec3 Projection = FromCenter.projection(VecOnPlane);
      const Vec3 Rejection = FromCenter.rejection(VecOnPlane);

      int x = static_cast<int>(Projection.length()) + Width / 2;
      int y = static_cast<int>(Rejection.length()) + Height / 2;
      I.setColor(getColor(x / Scale, y / Scale));

      I.setHitObject(this);
      Vec3::Unit Distance = P.getCoord().distance(I.getPos());
      if (I.getColor().getAlpha() <= 30) {
        I = Hit::missed();
      } else {
        return I;
      }
    }
    return I;
  }
};


#endif //RAYTRACER_TEXTURERECT_H
