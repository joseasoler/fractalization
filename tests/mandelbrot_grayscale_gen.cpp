#include "fractalization/mandelbrot_grayscale_gen.hpp"

#include "catch2/catch.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <list>
#include <vector>

SCENARIO("Mandelbrot and Grayscale generator", "[generator]") {
  constexpr std::uint32_t OUTPUT_SIZE = fractalization::MandelbrotGrayscaleGenD::OUTPUT_SIZE;
  GIVEN("A generator centered on [0.0 and 0.0] and an image.") {
    constexpr std::uint32_t SMALL_IMG_SIZE = 5;
    std::array<std::uint8_t, SMALL_IMG_SIZE * SMALL_IMG_SIZE * OUTPUT_SIZE> s_image{};
    fractalization::MandelbrotGrayscaleGenD gen_small{SMALL_IMG_SIZE,       SMALL_IMG_SIZE, 0.0, 0.0, 0.0,
                                                      SMALL_IMG_SIZE * 0.25};
    WHEN("The image is generated.") {
      gen_small.Generate(std::begin(s_image));
      THEN(
          "The central point of the image ([0.0, 0.0] in the complex plane) "
          "is white.") {
        const std::uint32_t center_idx = SMALL_IMG_SIZE * SMALL_IMG_SIZE / 2;
        REQUIRE(s_image[center_idx * OUTPUT_SIZE] == 255);
        REQUIRE(s_image[center_idx * OUTPUT_SIZE + 1] == 255);
        REQUIRE(s_image[center_idx * OUTPUT_SIZE + 2] == 255);
      }
      THEN("The top left point of the image is black.") {
        const std::uint32_t top_left_idx = 0;
        REQUIRE(s_image[top_left_idx * OUTPUT_SIZE] <= 1);
        REQUIRE(s_image[top_left_idx * OUTPUT_SIZE + 1] <= 1);
        REQUIRE(s_image[top_left_idx * OUTPUT_SIZE + 2] <= 1);
      }
      THEN("The bottom right point of the image is black.") {
        const auto bottom_right_idx = SMALL_IMG_SIZE * SMALL_IMG_SIZE - 1;
        REQUIRE(s_image[bottom_right_idx * OUTPUT_SIZE] <= 1);
        REQUIRE(s_image[bottom_right_idx * OUTPUT_SIZE + 1] <= 1);
        REQUIRE(s_image[bottom_right_idx * OUTPUT_SIZE + 2] <= 1);
      }
    }
  }
}
