#include "fractalization/components/output/grayscale_rgba.hpp"

#include "catch2/catch.hpp"

#include <array>
#include <cstdint>

SCENARIO("GrayscaleRGBA output class", "[output]") {
  GIVEN("A GrayscaleRGBA<std::uint8_t, std::uint8_t> output instance") {
    fractalization::GrayscaleRGBA<std::uint8_t, std::uint8_t> grayscale_output;
    std::array<std::uint8_t, 4> pixel{};
    WHEN("Calculating grayscale") {
      constexpr std::array<std::uint8_t, 3> INPUT_ARRAY{42, 0, 255};
      for (const std::uint8_t &input : INPUT_ARRAY) {
        grayscale_output.Process(input, pixel.data());
        THEN("The result is always equal to the input") {
          REQUIRE(pixel[0] == input);
          REQUIRE(pixel[1] == input);
          REQUIRE(pixel[2] == input);
        }
        THEN("Alpha is always the maximum value possible") {
          REQUIRE(pixel[3] == std::numeric_limits<std::uint8_t>::max());
        }
      }
    }
  }

  GIVEN("A GrayscaleRGBA<std::uint8_t, std::uint16_t> output instance") {
    fractalization::GrayscaleRGBA<std::uint8_t, std::uint16_t> grayscale_output;
    std::array<std::uint16_t, 4> pixel{};
    WHEN("Calculating grayscale") {
      constexpr std::array<std::uint8_t, 3> INPUT_ARRAY{42, 0, 255};
      for (const std::uint8_t &input : INPUT_ARRAY) {
        grayscale_output.Process(input, pixel.data());
        THEN("The result is always equal to the input") {
          REQUIRE(pixel[0] == input);
          REQUIRE(pixel[1] == input);
          REQUIRE(pixel[2] == input);
        }
        THEN("Alpha is always the maximum value possible") {
          REQUIRE(pixel[3] == std::numeric_limits<std::uint16_t>::max());
        }
      }
    }
  }

  GIVEN("A Grayscale<std::uint16_t, std::uint8_t> pixelization instance") {
    fractalization::GrayscaleRGBA<std::uint16_t, std::uint8_t> pixel_output;
    std::array<std::uint8_t, 4> pixel{};
    WHEN("Calculating grayscale") {
      constexpr std::array<std::uint16_t, 3> INPUT_ARRAY{4232, 0, 65535};
      for (const std::uint16_t &input : INPUT_ARRAY) {
        pixel_output.Process(input, pixel.data());
        const auto input_scaled = static_cast<std::uint8_t>(input >> 8u);
        THEN(
            "The result is scaled in order to fit into the smaller pixel "
            "type") {
          REQUIRE(pixel[0] == input_scaled);
          REQUIRE(pixel[1] == input_scaled);
          REQUIRE(pixel[2] == input_scaled);
        }
        THEN("Alpha is always the maximum value possible") {
          REQUIRE(pixel[3] == std::numeric_limits<std::uint8_t>::max());
        }
      }
    }
  }
}
