#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "lib/Color.h"
#include "lib/Level.h"
#include "lib/Circle.h"
#include "lib/Raytracer.h"
#include "lib/PointLight.h"
#include "lib/TextureRect.h"
#include "lib/Mirror.h"
#include "lib/Sphere.h"
#include "lib/GlobalLight.h"

int main()
{

  // Create the main window
  sf::RenderWindow window(sf::VideoMode(800, 600), "Ray tracer");

  Level L;

//  L.add(new Circle(Vec3(50, 50, 0), Vec3(0, 0, 1), Color(111, 0, 0), 50));
//  L.add(new Circle(Vec3(0, 50, 50), Vec3(1, 0, 0), Color(0, 111, 0), 50));
//  L.add(new Circle(Vec3(50, 0, 50), Vec3(0, 1, 0), Color(0, 0, 111), 50));
  L.add(new TextureRect(Vec3(20, 50, 440), Vec3(1, 0, 0), "test.png", 0.3));

  L.add(new Mirror(Vec3(20, 50, 440), Vec3(0, 1, 0), {360, 360}));
  //L.add(new Rectangle(Vec3(50, 10.5f, 50), Vec3(0, 1, 0), Color(0, 0, 0), {62, 62}));


  std::vector<Sphere *> Spheres;

  const int Field = 1900;
  for (int i = 0; i < 52; ++i) {
    int X = rand() % Field - Field/2;
    int Y = rand() % Field - Field/2;
    int Rad = rand() % 100;
    Sphere *S = new Sphere(Vec3(X, Y, Rad), Rad, Color(rand() % 255, rand() % 255, rand() % 255)) ;
    bool Collides = false;
    for (auto &OS : Spheres) {
      if (OS->collides(*S)) {
        Collides = true;
        break;
      }
    }
    if (!Collides) {
      Spheres.push_back(S);
      L.add(S);
    }
  }


  L.add(new Plane(Vec3(0, 0, 0), Vec3(0, 0, 1), Color(200, 20, 0)));

  PointLight *Light;
  L.add(Light = new PointLight(Vec3(370, 70, 722), 1888));
  L.add(new GlobalLight(Color(77, 77, 77)));

  Raytracer Tracer(L);
  Tracer.setPos(Vec3(3000, 3000, 3000));
  Tracer.setViewDirection(Vec3(-1, -1, -1));

  double Counter = 0;

  while (window.isOpen())
  {
    Counter += 0.1f;
    const int Width = window.getSize().x;
    const int Height = window.getSize().y;

    Vec3 V = Vec3(std::cos(Counter) * 3800,
                  std::sin(Counter) * 3800,
                  3800);
    Tracer.setPos(V);
    Vec3 ViewDirection = (-V).normalize();
    Tracer.setViewDirection(ViewDirection);

    //Light->setCenter(Vec3(Counter * 300, 500, 1000));

    Tracer.setRenderSize(Width, Height);
    Tracer.setSuperSamplingSize(Width * 1, Height * 1);
    Tracer.render();

    sf::Image Img;
    Img.create(Width, Height, reinterpret_cast<const uint8_t *>(Tracer.getBuffer().data()));

    sf::Texture texture;
    texture.loadFromImage(Img);
    sf::Sprite sprite;
    sprite.setTexture(texture, true);

    // Process events
    sf::Event event;
    while (window.pollEvent(event))
    {
      // Close window: exit
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        window.close();
    }
    // Clear screen
    window.clear();
    // Draw the sprite
    window.draw(sprite);
    // Update the window
    window.display();
  }
  return EXIT_SUCCESS;
}