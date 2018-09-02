#include "fractalization_sprite.hpp"

#include "SFML/Graphics/RenderTarget.hpp"
#include "fractalization/mandelbrot_grayscale_gen.hpp"

namespace fractalization_sfml {

FractalizationSprite::FractalizationSprite(unsigned int width, unsigned int height)
    : dirty{true}, c_r{0.0}, c_i{0.0}, rot_angle{0.0}, zoom{1.0} {
  gen_ = std::make_unique<fractalization::MandelbrotGrayscaleGenD>(width, height, c_r, c_i, rot_angle, width * zoom);
  texture_.create(width, height);
  texture_.setSmooth(true);
  sprite_.setPosition(0.f, 0.f);
  sprite_.setTexture(texture_);
  image_data_.resize(width * height * 4);
  dirty = true;
}

FractalizationSprite::~FractalizationSprite() = default;

void FractalizationSprite::Update() {
  if (!dirty) {
    return;
  }
  gen_->Generate(fractalization::PARALLEL, image_data_.begin());
  texture_.update(image_data_.data());
  dirty = false;
}

void FractalizationSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(sprite_, states);
}

void FractalizationSprite::ApplyTransformChanges() {
  gen_->GetTransformation().Update(c_r, c_i, rot_angle, texture_.getSize().x * zoom);
  dirty = true;
}

void FractalizationSprite::MoveTo(unsigned int x, unsigned int y) {
  const auto &[center_r, center_i] = gen_->GetTransformation().Transform(x, y);
  c_r = center_r;
  c_i = center_i;
  ApplyTransformChanges();
}

void FractalizationSprite::Zoom(double zoom_factor) {
  zoom *= zoom_factor;
  ApplyTransformChanges();
}

}  // namespace fractalization_sfml
