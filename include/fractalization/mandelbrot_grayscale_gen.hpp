#ifndef FRACTALIZATION_MANDELBROT_GRAYSCALE_GEN_HPP
#define FRACTALIZATION_MANDELBROT_GRAYSCALE_GEN_HPP

#include "components/fractal/mandelbrot.hpp"
#include "fractalization/components/output/grayscale_rgba.hpp"
#include "generator.hpp"

#include <limits>

namespace fractalization {

namespace internal {

template <typename CmplxScalar, typename FrctlScalar>
using MdGray = Mandelbrot<CmplxScalar, FrctlScalar, std::numeric_limits<FrctlScalar>::max()>;

template <typename CmplxScalar, typename FrctlScalar, typename OutputScalar>
using MdGrayscaleGenerator =
    Generator<CmplxScalar, MdGray<CmplxScalar, FrctlScalar>, GrayscaleRGBA<FrctlScalar, OutputScalar>>;
}  // namespace internal

template <typename CmplxScalar, typename FrctlScalar, typename OutputScalar>
class MandelbrotGrayscaleGen : public internal::MdGrayscaleGenerator<CmplxScalar, FrctlScalar, OutputScalar> {
 public:
  MandelbrotGrayscaleGen(std::uint32_t w, std::uint32_t h, CmplxScalar center_r, CmplxScalar center_i,
                         CmplxScalar rotation_angle, CmplxScalar zoom)
      : internal::MdGrayscaleGenerator<CmplxScalar, FrctlScalar, OutputScalar>(
            Transformation(w, h, center_r, center_i, rotation_angle, zoom),
            internal::MdGray<CmplxScalar, FrctlScalar>(), GrayscaleRGBA<FrctlScalar, OutputScalar>()) {}
};

class MandelbrotGrayscaleGenD : public MandelbrotGrayscaleGen<double, std::uint8_t, std::uint8_t> {
 public:
  MandelbrotGrayscaleGenD(std::uint32_t w, std::uint32_t h, double center_r, double center_i, double rot_angle,
                          double zoom)
      : MandelbrotGrayscaleGen<double, std::uint8_t, std::uint8_t>(w, h, center_r, center_i, rot_angle, zoom) {}
};

}  // namespace fractalization

#endif  // FRACTALIZATION_MANDELBROT_GRAYSCALE_GEN_HPP
