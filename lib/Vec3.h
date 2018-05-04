#ifndef RAYTRACER_VEC3_H
#define RAYTRACER_VEC3_H


#include <cmath>

class Vec3 {
public:
  typedef double Unit;
private:
  Unit X, Y, Z;
public:
  Vec3() = default;
  Vec3(Unit X, Unit Y, Unit Z) : X(X), Y(Y), Z(Z) {
  }

  Unit dot(const Vec3 &Other) const {
    return X * Other.X + Y * Other.Y + Z * Other.Z;
  }

  Vec3 crossProduct(const Vec3 &B) const {
    return Vec3(Y * B.Z - Z * B.Y,
                Z * B.X - X * B.Z,
                X * B.Y - Y * B.X);
  }

  Unit distance(const Vec3 &O) const {
    return (O - *this).length();
  }

  Unit length() const {
    return std::sqrt(X * X + Y * Y + Z * Z);
  }

  Vec3 operator*(const Unit& F) const {
    return Vec3(X * F, Y * F, Z * F);
  }

  Vec3 operator+(const Vec3& O) const {
    return Vec3(X + O.X, Y + O.Y, Z + O.Z);
  }

  Vec3 operator-(const Vec3& O) const {
    return Vec3(X - O.X, Y - O.Y, Z - O.Z);
  }


  Vec3 normalize() const {
    auto L = length();
    return Vec3(X / L, Y / L, Z / L);
  }

  Unit getX() const {
    return X;
  }

  void setX(Unit X) {
    Vec3::X = X;
  }

  Unit getY() const {
    return Y;
  }

  void setY(Unit Y) {
    Vec3::Y = Y;
  }

  Unit getZ() const {
    return Z;
  }

  void setZ(Unit Z) {
    Vec3::Z = Z;
  }

};


#endif //RAYTRACER_VEC3_H
