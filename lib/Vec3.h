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

  Unit angleBetween(const Vec3 &Other) const {
    return std::acos(normalize().dot(Other.normalize()));
  }

  Vec3 getRandomOther() const {
    if (std::abs(normalize().getX() - 1) < 0.1f) {
      return Vec3(0, 1, 0);
    } else {
      return Vec3(1, 0, 0);
    }
  }

  Vec3 rotateAround(const Vec3 &K, Vec3::Unit Angle) const {
    // Rodrigues' rotation formula
    return *this * std::cos(Angle) + (K.crossProduct(*this)) * std::sin(Angle)
        + K * (K.dot(*this)) * (1 - std::cos(Angle));
  }

  Vec3 mirrorAt(const Vec3& N) const {
    return *this - N * 2.0 * (this->dot(N));
  }

  Vec3 crossProduct(const Vec3 &B) const {
    return Vec3(Y * B.Z - Z * B.Y,
                Z * B.X - X * B.Z,
                X * B.Y - Y * B.X);
  }

  Vec3 projection(const Vec3 &B) const {
    Vec3::Unit a1 = dot(B.normalize());
    return B.normalize() * a1;
  }

  Vec3 rejection(const Vec3 &B) const {
    return *this - projection(B);
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

  Vec3 operator/(const Unit& F) const {
    return Vec3(X / F, Y / F, Z / F);
  }

  Vec3 operator+(const Vec3& O) const {
    return Vec3(X + O.X, Y + O.Y, Z + O.Z);
  }

  Vec3 operator-(const Vec3& O) const {
    return Vec3(X - O.X, Y - O.Y, Z - O.Z);
  }

  Vec3 operator-() const {
    return Vec3(-X, -Y, -Z);
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

inline Vec3 operator*(Vec3::Unit F, const Vec3 &A) {
  return A * F;
}

inline Vec3 operator/(Vec3::Unit F, const Vec3 &A) {
  return A / F;
}

#endif //RAYTRACER_VEC3_H
