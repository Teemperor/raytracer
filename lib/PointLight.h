#ifndef RAYTRACER_POINTLIGHT_H
#define RAYTRACER_POINTLIGHT_H


#include "Light.h"
#include "Ray.h"

class PointLight : public Light {
  Vec3 Center;
  Vec3::Unit Radius;
  Color C = Color(255, 255, 255);
public:
  PointLight(Vec3 Center, Vec3::Unit Radius) : Center(Center), Radius(Radius) {
  }
  void processHit(Hit &H, const Ray& View, const Level& L) const override;

  const Vec3 &getCenter() const {
    return Center;
  }

  void setCenter(const Vec3 &Center) {
    PointLight::Center = Center;
  }

  Vec3::Unit getRadius() const {
    return Radius;
  }

  void setRadius(Vec3::Unit Radius) {
    PointLight::Radius = Radius;
  }

  const Color &getColor() const {
    return C;
  }

  void setColor(const Color &C) {
    PointLight::C = C;
  }
};


#endif //RAYTRACER_POINTLIGHT_H
