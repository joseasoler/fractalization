#ifndef FRACTALIZATION_COMPONENTS_TRANSFORMATION_HPP
#define FRACTALIZATION_COMPONENTS_TRANSFORMATION_HPP

#include <cstdint>
#include <utility>

#include "Eigen/Geometry"

namespace fractalization {
template <typename CmplxScalar>
class Transformation {
 private:
  using Vector2 = Eigen::Matrix<CmplxScalar, 2, 1>;
  using Translation2 = Eigen::Translation<CmplxScalar, 2>;
  using Rotation2 = Eigen::Rotation2D<CmplxScalar>;
  using Scaling = Eigen::UniformScaling<CmplxScalar>;
  using Transform2 = Eigen::Transform<CmplxScalar, 2, Eigen::Affine>;
  Transform2 t_;

  static Transform2 CreateTransform(std::uint32_t w, std::uint32_t h, CmplxScalar center_r, CmplxScalar center_i,
                                    CmplxScalar rotation_angle, CmplxScalar zoom) {
    return Translation2{center_r, center_i} * Rotation2{rotation_angle} * Scaling{1 / zoom} *
           Translation2{-static_cast<CmplxScalar>(w >> 1u), -static_cast<CmplxScalar>(h >> 1u)};
  }

 public:
  Transformation(std::uint32_t w, std::uint32_t h, CmplxScalar center_r, CmplxScalar center_i, CmplxScalar rot_angle,
                 CmplxScalar zoom);
  const std::uint32_t width;
  const std::uint32_t height;
  std::pair<CmplxScalar, CmplxScalar> Transform(std::uint32_t x, std::uint32_t y) const;
  std::pair<CmplxScalar, CmplxScalar> Transform(std::uint32_t output_index) const;
  void Update(CmplxScalar center_r, CmplxScalar center_i, CmplxScalar rot_angle, CmplxScalar zoom);
};

template <typename CmplxScalar>
Transformation<CmplxScalar>::Transformation(std::uint32_t w, std::uint32_t h, CmplxScalar center_r,
                                            CmplxScalar center_i, CmplxScalar rot_angle, CmplxScalar zoom)
    : t_{CreateTransform(w, h, center_r, center_i, rot_angle, zoom)}, width{w}, height{h} {}

template <typename CmplxScalar>
std::pair<CmplxScalar, CmplxScalar> Transformation<CmplxScalar>::Transform(std::uint32_t x, std::uint32_t y) const {
  // Generate Eigen3 vector using the screen coordinates of output_index.
  Vector2 cv{static_cast<CmplxScalar>(x), static_cast<CmplxScalar>(y)};
  // Apply the transformation to the vector.
  cv = t_ * cv;
  return {cv[0], cv[1]};
}

template <typename CmplxScalar>
std::pair<CmplxScalar, CmplxScalar> Transformation<CmplxScalar>::Transform(std::uint32_t output_index) const {
  return Transform(output_index % width, static_cast<std::uint32_t>(output_index / width));
}

template <typename CmplxScalar>
void Transformation<CmplxScalar>::Update(CmplxScalar center_r, CmplxScalar center_i, CmplxScalar rot_angle,
                                         CmplxScalar zoom) {
  Transform2 new_transform = CreateTransform(width, height, center_r, center_i, rot_angle, zoom);
  t_ = new_transform;
}

}  // namespace fractalization

#endif  // FRACTALIZATION_COMPONENTS_TRANSFORMATION_HPP
