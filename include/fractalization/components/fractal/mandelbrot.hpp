#ifndef FRACTALIZATION_COMPONENTS_FRACTAL_MANDELBROT_HPP
#define FRACTALIZATION_COMPONENTS_FRACTAL_MANDELBROT_HPP

#include <cmath>
#include <utility>

namespace fractalization {

template <typename CmplxScalar, typename FrctlScalar, FrctlScalar MaxIterations>
class Mandelbrot {
 public:
  FrctlScalar Evaluate(std::pair<CmplxScalar, CmplxScalar> cp) const {
    const auto& [c_r, c_i] = cp;
    FrctlScalar iterations{static_cast<FrctlScalar>(0)};
    CmplxScalar z_r{static_cast<CmplxScalar>(0.0)};
    CmplxScalar z_i{static_cast<CmplxScalar>(0.0)};
    CmplxScalar z_r_squared{static_cast<CmplxScalar>(0.0)};
    CmplxScalar z_i_squared{static_cast<CmplxScalar>(0.0)};

    while ((z_r_squared + z_i_squared) <= static_cast<CmplxScalar>(4.0) && iterations < MaxIterations) {
      z_i = 2 * z_r * z_i + c_i;
      z_r = z_r_squared - z_i_squared + c_r;
      z_r_squared = std::pow(z_r, 2);
      z_i_squared = std::pow(z_i, 2);
      ++iterations;
    }
    return iterations;
  }
};
}  // namespace fractalization

#endif  // FRACTALIZATION_COMPONENTS_FRACTAL_MANDELBROT_HPP
