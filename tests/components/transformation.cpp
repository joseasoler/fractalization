#include "fractalization/components/transformation.hpp"

#include "catch2/catch.hpp"

SCENARIO("Transformation class", "[Transformation]") {
  using TransfTest = fractalization::Transformation<double>;
  GIVEN("The coordinates of an square image") {
    const std::uint32_t image_size = 101;
    std::uint32_t top_left_idx = 0;
    // Coordinates when the center of the image is at (0.0, 0.0).
    const std::uint32_t image_size_half = image_size / 2;
    double top_left_pos = -static_cast<double>(image_size_half);
    WHEN("A transform without any changes is applied") {
      TransfTest translate(image_size, image_size, 0.0, 0.0, 0.0, 1.0);
      THEN(
          "The translated coordinates of the top-left point of the image are "
          "the same.") {
        const auto& [cp_r, cp_i] = translate.Transform(top_left_idx);
        REQUIRE(cp_r == Approx(top_left_pos));
        REQUIRE(cp_i == Approx(top_left_pos));
      }
    }
    WHEN("A 180 degrees rotation transform is applied") {
      TransfTest translate(image_size, image_size, 0.0, 0.0, 3.14159265358979323846, 1.0);
      THEN(
          "The translated coordinates of the top-left point of the image are "
          "rotated") {
        const auto& [cp_r, cp_i] = translate.Transform(top_left_idx);
        REQUIRE(cp_r == Approx(-top_left_pos));
        REQUIRE(cp_i == Approx(-top_left_pos));
      }
    }
    WHEN("A transform increasing the zoom factor is applied") {
      double zoom_factor = 5.0;
      TransfTest translate(image_size, image_size, 0.0, 0.0, 0.0, zoom_factor);
      THEN("The translated coordinates are scaled as expected") {
        const auto& [cp_r, cp_i] = translate.Transform(top_left_idx);
        REQUIRE(cp_r == Approx(top_left_pos / zoom_factor));
        REQUIRE(cp_i == Approx(top_left_pos / zoom_factor));
      }
    }
    WHEN("A transform reducing the zoom factor is applied") {
      double zoom_factor = 0.1;
      TransfTest translate(image_size, image_size, 0.0, 0.0, 0.0, zoom_factor);
      THEN("The translated coordinates are scaled as expected") {
        const auto& [cp_r, cp_i] = translate.Transform(top_left_idx);
        REQUIRE(cp_r == Approx(top_left_pos / zoom_factor));
        REQUIRE(cp_i == Approx(top_left_pos / zoom_factor));
      }
    }
    std::uint32_t center_idx = image_size * image_size / 2;
    double center_r = 3498.0;
    double center_i = -123435.0;
    WHEN("A translation-only transform is applied") {
      TransfTest translate(image_size, image_size, center_r, center_i, 0.0, 1.0);
      THEN(
          "The translated coordinates of the center point of the image are "
          "equal to the center of the transform") {
        const auto& [cp_r, cp_i] = translate.Transform(center_idx);
        REQUIRE(cp_r == Approx(center_r));
        REQUIRE(cp_i == Approx(center_i));
      }
    }
    WHEN("A transform with translation, rotation and scale is applied") {
      TransfTest translate(image_size, image_size, center_r, center_i, 1.1, 8.9);
      THEN(
          "The translated coordinates of the center point of the image are "
          "equal to the center of the transform") {
        const auto& [cp_r, cp_i] = translate.Transform(center_idx);
        REQUIRE(cp_r == Approx(center_r));
        REQUIRE(cp_i == Approx(center_i));
      }
    }
  }
}
