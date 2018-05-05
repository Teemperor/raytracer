#include "PointLight.h"
#include "Ray.h"
#include "Level.h"

void PointLight::processHit(Hit &H, const Level& L) const {
  Ray R(getCenter(), H.getPos() - getCenter());

  Hit BH = L.intersect(R);
  bool HitSamePoint = H.getPos().distance(BH.getPos()) < 2;
  if (BH.valid() && !HitSamePoint) {
    //H.setColor(Color());
    return;
  }

  Vec3::Unit DotAngle = H.getNormal().dot((getCenter() - H.getPos()).normalize());



  Vec3::Unit Distance = H.getPos().distance(Center);
  auto Strength = 1 - Distance / Radius;
  if (Strength > 0 && Strength < 1) {
    Color UsedColor = C * Strength * DotAngle;
    H.addLight(UsedColor);
  }
}
