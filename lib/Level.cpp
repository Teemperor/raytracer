#include "Level.h"

void Level::lightHit(Hit &H, const Ray &View) const {
  for (auto &L : Lights) {
    L->processHit(H, View, *this);
  }
}
