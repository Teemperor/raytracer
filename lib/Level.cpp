#include "Level.h"

void Level::lightHit(Hit &H) const {
  for (auto &L : Lights) {
    L->processHit(H, *this);
  }
}
