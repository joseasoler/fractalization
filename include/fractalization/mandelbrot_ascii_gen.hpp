#ifndef FRACTALIZATION_MANDELBROT_ASCII_GEN_HPP
#define FRACTALIZATION_MANDELBROT_ASCII_GEN_HPP

#include "components/fractal/mandelbrot.hpp"
#include "fractalization/components/output/ascii.hpp"
#include "generator.hpp"

#include <limits>

namespace fractalization {

namespace internal {
using MdAscii = Mandelbrot<double, std::uint8_t, std::numeric_limits<std::uint8_t>::max()>;
using MdAsciiGenerator = Generator<double, MdAscii, Ascii<std::uint8_t, char>>;
}  // namespace internal

class MandelbrotAsciiGen : public internal::MdAsciiGenerator {
 public:
  MandelbrotAsciiGen(std::uint32_t w, std::uint32_t h, double center_r, double center_i, double rot_angle, double zoom)
      : internal::MdAsciiGenerator(Transformation(w, h, center_r, center_i, rot_angle, zoom), internal::MdAscii(),
                                   Ascii<std::uint8_t, char>()) {}
};

}  // namespace fractalization

#endif  // FRACTALIZATION_MANDELBROT_ASCII_GEN_HPP
