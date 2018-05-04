#include "PointLight.h"
#include "Ray.h"
#include "Level.h"

void PointLight::processHit(Hit &H, const Level& L) const {
  Ray R(getCenter(), H.getPos() - getCenter());

  Hit BH = L.intersect(R);
  if (BH.valid() && H.getHitObject() != BH.getHitObject()) {
    H.setColor(Color(0, 0, 0));
    return;
  }

  Vec3::Unit Distance = H.getPos().distance(Center);
  auto Strength = 1 - Distance / Radius;
  if (Strength > 0 && Strength < 1) {
    Color UsedColor = C * Strength;
    H.addLight(UsedColor);
  }
}
