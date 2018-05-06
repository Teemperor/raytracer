#include "Raytracer.h"

Raytracer::Raytracer(Level &L) : L(L) {
#ifdef NDEBUG
  Jobs = std::thread::hardware_concurrency();
    --Jobs;
    if (Jobs <= 0)
      Jobs = 1;
#endif
}
