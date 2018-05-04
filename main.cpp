#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "lib/Color.h"
#include "lib/Level.h"
#include "lib/Circle.h"
#include "lib/Raytracer.h"
#include "lib/PointLight.h"
#include "lib/TextureRect.h"
#include "lib/Mirror.h"

int main()
{

  // Create the main window
  sf::RenderWindow window(sf::VideoMode(800, 600), "Ray tracer");

  Level L;

  Circle C1(Vec3(50, 50, 0), Vec3(0, 0, 1), Color(111, 0, 0), 50);
  L.add(&C1);
  Circle C2(Vec3(0, 50, 50), Vec3(1, 0, 0), Color(0, 111, 0), 50);
  L.add(&C2);
  Circle C3(Vec3(50, 0, 50), Vec3(0, 1, 0), Color(0, 0, 111), 50);
  L.add(&C3);
  Circle C4(Vec3(50, 20, 50), Vec3(0, 1, 0), Color(0, 22, 181), 20);
  L.add(&C4);
  //Circle C5(Vec3(20, 50, 50), Vec3(1, 0, 0), Color(111, 22, 181), 10);
  //L.add(&C5);
  TextureRect R1(Vec3(20, 50, 50), Vec3(1, 0, 0), "test.png", 0.8f);
  L.add(&R1);

  L.add(new Mirror(Vec3(50, 10, 50), Vec3(0, 1, 0), {60, 60}));

  //Plane P1(, Color(0, 0, 22));
  //L.add(&P1);

  PointLight *Light;
  L.add(Light = new PointLight(Vec3(50, 50, 50), 88));

  Raytracer Tracer(L);
  Tracer.setPos(Vec3(800, 800, 800));

  Vec3 ViewDirection(-1, -1, -1);

  double Counter = 0;

  auto OrigLightX = Light->getCenter().getX();

  while (window.isOpen())
  {
    Counter += 0.1f;
    const int Width = window.getSize().x;
    const int Height = window.getSize().y;

    {
      auto P = Light->getCenter();
      P.setX(OrigLightX + std::cos(Counter) * 40);
      Light->setCenter(P);
    }

    //ViewDirection.setZ(std::cos(ViewAngle -= 0.05));

    Tracer.setViewDirection(ViewDirection);

    std::vector<Color> Buffer;

    Buffer.resize(Width * Height, Color(0, 0, 0));
    Tracer.setRenderSize(Width, Height);
    Tracer.trace(Buffer);

    sf::Image Img;
    Img.create(Width, Height, reinterpret_cast<uint8_t *>(Buffer.data()));

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