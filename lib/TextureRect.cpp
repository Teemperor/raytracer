#include "TextureRect.h"

#include "Level.h"

Hit TextureRect::intersect(const Ray &R, const Level &L) const {
  Hit I = Rectangle::intersect(R, L);
  if (I.valid()) {
    const Vec3 FromCenter = I.getPos() - getCenter();

    const Vec3 Up(0, 0, 1);
    const Vec3 XAxis(1, 0, 0);

    const Vec3::Unit RotationToUp = getNormal().angleBetween(Up);
    const Vec3 RotationUpAxis = getNormal().crossProduct(Up);

    const Vec3 RotatedUpwards = FromCenter.rotateAround(RotationUpAxis, RotationToUp);

    Vec3::Unit RotationToX = RotationUpAxis.angleBetween(XAxis);
    const Vec3 TextureVec = RotatedUpwards.rotateAround(Up, RotationToX);

    int x = static_cast<int>(TextureVec.getX()) + getWidth() / 2;
    int y = static_cast<int>(TextureVec.getY()) + getHeight() / 2;
    I.setColor(getColor(x / Scale, y / Scale));

    I.setHitObject(this);
    if (I.getColor().getAlpha() <= 0) {
      return Hit::missed();
    } else if (I.getColor().getAlpha() != 255) {
      if (R.wantsColor()) {
        Ray Background(I.getPos(), R.getDirection());
        Hit BackgroundHit = L.intersectWithLight(Background, this);

        I.setColor(BackgroundHit.getFinalColor().drawOver(I.getColor()));
        return I;
      }
    }
  }
  return I;
}
