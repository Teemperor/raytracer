#include "PointLight.h"
#include "Ray.h"
#include "Level.h"

void PointLight::processHit(Hit &H, const Ray& View, const Level& L) const {
  const Ray LightTrace(getCenter(), H.getPos() - getCenter());

  const Hit BH = L.intersect(LightTrace);
  bool HitSamePoint = H.getPos().distance(BH.getPos()) < 2;
  if (BH.valid() && !HitSamePoint) {
    return;
  }

  Vec3::Unit DotAngle = H.getNormal().dot(-LightTrace.getDirection());

  Vec3::Unit Distance = H.getPos().distance(Center);
  auto Strength = 1 - Distance / Radius;
  if (Strength > 0 && Strength < 1) {
    Color UsedColor = C * Strength * DotAngle;
    H.addLight(UsedColor);
  }

  Vec3 Reflection = LightTrace.getDirection().mirrorAt(H.getNormal());
  Vec3::Unit Specular = View.getDirection().dot(-Reflection.normalize());
  Specular = std::pow(Specular, 332.0);

  // Disabled for now, doesn't seem to produce the right effect.
  //H.addLight(Color(255, 255, 255) * std::max(Specular, 0.0));
}
