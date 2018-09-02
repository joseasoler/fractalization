#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "fractalization_sprite.hpp"

int main() {
  unsigned int width = 640;
  unsigned int height = 480;
  sf::RenderWindow window(sf::VideoMode(width, height), "FractalizationSFML", sf::Style::Default);
  window.setFramerateLimit(30);

  fractalization_sfml::FractalizationSprite s(width, height);

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::MouseButtonPressed:
          if (event.mouseButton.button == sf::Mouse::Left) {
            s.MoveTo(static_cast<unsigned int>(event.mouseButton.x), static_cast<unsigned int>(event.mouseButton.y));
          }
          break;
        case sf::Event::MouseWheelScrolled:
          s.Zoom(event.mouseWheelScroll.delta > 0 ? 1.1 : 0.9);
          break;
        default:
          break;
      }
    }
    s.Update();
    window.draw(s);
    window.display();
  }
  return 0;
}
