#include "Raytracer.h"

Raytracer::Raytracer(Level &L) : L(L) {
#ifdef NDEBUG
  Jobs = std::thread::hardware_concurrency();
    --Jobs;
    if (Jobs <= 0)
      Jobs = 1;
#endif
}

void Raytracer::sampleToBuffer() {
  auto DataPerJob = Buffer.size() / Jobs;
  std::vector<std::thread *> Threads;

  for (std::size_t Start = 0; Start < Buffer.size(); Start += DataPerJob) {
    std::thread *T = new std::thread([this, Start, DataPerJob](){
      for (std::size_t I = Start; I < Start + DataPerJob; ++I) {
        int x = static_cast<int>(I % Width);
        int y = static_cast<int>(I / Width);
        double XP = x / (double) Width;
        double YP = y / (double) Height;

        int SSX = static_cast<int>(XP * SSWidth);
        int SSY = static_cast<int>(YP * SSHeight);

        int SSD = SSWidth / Width / 2;

        int RightX = SSX + SSD;
        int LowerY = SSY + SSD;

        std::vector<Color> Samples;
        for (int IX = SSX - SSD; IX <= RightX; ++IX) {
          for (int IY = SSY - SSD; IY <= LowerY; ++IY) {
            Samples.push_back(getSSPixel(IX, IY));
          }
        }

        Buffer[x + y * Width] = computeAverage(Samples);
      }
    });
    Threads.push_back(T);
  }
  for (auto &T : Threads)
    T->join();
}

void Raytracer::renderSS() {
  auto DataPerJob = SSBuffer.size() / Jobs;
  std::vector<std::thread *> Threads;

  for (std::size_t Start = 0; Start < SSBuffer.size(); Start += DataPerJob) {
    std::thread *T = new std::thread([this, Start, DataPerJob](){
      for (std::size_t I = Start; I < Start + DataPerJob; ++I) {
        int x = I % SSWidth;
        int y = I / SSWidth;
        const Vec3 TargetCenter = Pos + Direction.normalize() * 100;

        const Vec3 ToTargetCenter = TargetCenter - Pos;
        const Vec3 Up(0, 0, 1);

        double XP = (x / (float) SSWidth - 0.5f) * 20;
        double YP = (y / (float) SSHeight - 0.5f) * 20;

        const Vec3 LeftFromTarget = Up.crossProduct(ToTargetCenter).normalize();
        const Vec3 UpFromTarget = LeftFromTarget.crossProduct(ToTargetCenter).normalize();

        const Vec3 DirectionToPixel = ToTargetCenter + LeftFromTarget * XP + UpFromTarget * YP;

        Ray R(Pos, DirectionToPixel.normalize(), RayLimit);
        Hit H = L.intersectWithLight(R);
        if (H.valid()) {
          SSBuffer[x + y * SSWidth] = H.getFinalColor();
        }
      }
    });
    Threads.push_back(T);
  }
  for (auto &T : Threads)
    T->join();
}
