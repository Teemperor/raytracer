#ifndef RAYTRACER_TEXTURERECT_H
#define RAYTRACER_TEXTURERECT_H


#include <string>
#include <SFML/Graphics/Image.hpp>
#include <iostream>
#include "Vec3.h"
#include "Object.h"
#include "Plane.h"
#include "Rectangle.h"

class TextureRect : public Rectangle {
  sf::Image Img;
  float Scale;

  Color getColor(int x, int y) const {
    if (x < 0 || y < 0 || x >= getWidth()|| y >= getHeight()) {
      return Color(0, 0, 0, 0);
    }
    sf::Color C = Img.getPixel(x, y);
    return Color(C.r, C.g, C.b, C.a);
  }

  std::pair<int, int> loadImage(const std::string &Path) {
    if (!Img.loadFromFile(Path)) {
      std::cerr << "Failed to load texture " << Path << "\n";
    }
    return {Img.getSize().x, Img.getSize().y};
  };

public:
  TextureRect(Vec3 Center, Vec3 Normal, const std::string &Path, float Scale)
    : Rectangle(Center, Normal, Color(), {0, 0}), Scale(Scale) {
    setSize(loadImage(Path));
  }

  Hit intersect(const Ray &R) const override {
    Hit I = Rectangle::intersect(R);
    if (I.valid()) {
      const Vec3 FromCenter = I.getPos() - getCenter();

      Vec3 RandomVec = getNormal().getRandomOther();

      Vec3 VecOnPlane = getNormal().crossProduct(RandomVec);

      const Vec3 Projection = FromCenter.projection(VecOnPlane);
      const Vec3 Rejection = FromCenter.rejection(VecOnPlane);

      int x = static_cast<int>(Projection.length()) + getWidth() / 2;
      int y = static_cast<int>(Rejection.length()) + getHeight() / 2;
      I.setColor(getColor(x / Scale, y / Scale));

      I.setHitObject(this);
      Vec3::Unit Distance = getCenter().distance(I.getPos());
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
