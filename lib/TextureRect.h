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
    if (x < 0 || y < 0 || x >= getWidth() / Scale || y >= getHeight() / Scale) {
      return Color(0, 0, 0, 0);
    }
    sf::Color C = Img.getPixel(x, y);
    return Color(C.r, C.g, C.b, C.a);
  }

  std::pair<int, int> loadImage(const std::string &Path) {
    if (!Img.loadFromFile(Path)) {
      std::cerr << "Failed to load texture " << Path << "\n";
    }
    return {static_cast<int>(Img.getSize().x * Scale),
            static_cast<int>(Img.getSize().y * Scale)};
  };

public:
  TextureRect(Vec3 Center, Vec3 Normal, const std::string &Path, float Scale)
    : Rectangle(Center, Normal, Color(), {0, 0}), Scale(Scale) {
    setSize(loadImage(Path));
  }

  Hit intersect(const Ray &R, const Level &L) const override;
};


#endif //RAYTRACER_TEXTURERECT_H
