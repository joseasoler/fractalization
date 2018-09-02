#ifndef FRACTALIZATION_COMPONENTS_OUTPUT_GRAYSCALE_RGBA_HPP
#define FRACTALIZATION_COMPONENTS_OUTPUT_GRAYSCALE_RGBA_HPP

#include <cstdint>
#include <limits>

namespace fractalization {
template <typename FrctlScalar, typename OutputScalar>
class GrayscaleRGBA {
 private:
  static constexpr std::uint32_t SIZE_DIFF = sizeof(FrctlScalar) > sizeof(OutputScalar)
                                                 ? sizeof(FrctlScalar) - sizeof(OutputScalar)
                                                 : 0;

 public:
  static constexpr std::uint32_t OUTPUT_SIZE = 4;

  template <class RndmIt>
  RndmIt Process(FrctlScalar fractal_scalar, RndmIt output_start) const {
    // If OutputScalar is smaller than FrctlScalar, then the value needs to be scaled to fit.
    auto output_value = static_cast<OutputScalar>(fractal_scalar >> (8 * SIZE_DIFF));

    *output_start++ = output_value;
    *output_start++ = output_value;
    *output_start++ = output_value;
    *output_start++ = std::numeric_limits<OutputScalar>::max();
    return output_start;
  }
};
}  // namespace fractalization

#endif  // FRACTALIZATION_COMPONENTS_OUTPUT_GRAYSCALE_RGBA_HPP
