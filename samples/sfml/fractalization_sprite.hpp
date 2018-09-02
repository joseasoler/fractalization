#ifndef FRACTALIZATIONSFML_FRACTALIZATIONSPRITE_HPP
#define FRACTALIZATIONSFML_FRACTALIZATIONSPRITE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <memory>
#include <utility>
#include <vector>

namespace fractalization {
class MandelbrotGrayscaleGenD;
}

namespace fractalization_sfml {

class FractalizationSprite : public sf::Drawable {
 private:
  bool dirty;
  double c_r;
  double c_i;
  double rot_angle;
  double zoom;
  std::unique_ptr<fractalization::MandelbrotGrayscaleGenD> gen_;
  sf::Texture texture_;
  sf::Sprite sprite_;
  std::vector<sf::Uint8> image_data_;
  void ApplyTransformChanges();

 public:
  FractalizationSprite(unsigned int width, unsigned int height);
  ~FractalizationSprite();
  void Update();
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
  void MoveTo(unsigned int x, unsigned int y);
  void Zoom(double zoom_factor);
};

}  // namespace fractalization_sfml

#endif  // FRACTALIZATIONSFML_FRACTALIZATIONSPRITE_HPP
