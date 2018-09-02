#include "fractalization/components/output/ascii.hpp"

#include "catch2/catch.hpp"

#include <iterator>

SCENARIO("Ascii output class", "[output]") {
  std::array<char, 1> output{};
  static constexpr char MIN_LEVEL_CHAR = (*std::cbegin(fractalization::ASCII_LEVELS));
  static constexpr char MAX_LEVEL_CHAR = (*std::crbegin(fractalization::ASCII_LEVELS));
  GIVEN("Ascii output instances with std::uint8_t as fractal value") {
    fractalization::Ascii<std::uint8_t, char> ascii_uint8_t;
    WHEN("Calculating output for the minimum scalar value") {
      ascii_uint8_t.Process(std::numeric_limits<std::uint8_t>::min(), std::begin(output));
      THEN("The result is scaled as expected.") { REQUIRE(output[0] == MIN_LEVEL_CHAR); }
    }
    WHEN("Calculating output for the maximum scalar value") {
      ascii_uint8_t.Process(std::numeric_limits<std::uint8_t>::max(), std::begin(output));
      THEN("The result is scaled as expected.") { REQUIRE(output[0] == MAX_LEVEL_CHAR); }
    }
  }
  GIVEN("Ascii output instances with std::uint16_t as fractal value") {
    fractalization::Ascii<std::uint16_t, char> ascii_uint16_t;
    WHEN("Calculating output for the minimum scalar value") {
      ascii_uint16_t.Process(std::numeric_limits<std::uint16_t>::min(), std::begin(output));
      THEN("The result is scaled as expected.") { REQUIRE(output[0] == MIN_LEVEL_CHAR); }
    }
    WHEN("Calculating output for the maximum scalar value") {
      ascii_uint16_t.Process(std::numeric_limits<std::uint16_t>::max(), std::begin(output));
      THEN("The result is scaled as expected.") { REQUIRE(output[0] == MAX_LEVEL_CHAR); }
    }
  }
  GIVEN("Ascii output instances with std::uint32_t as fractal value") {
    fractalization::Ascii<std::uint32_t, char> ascii_uint32_t;
    WHEN("Calculating output for the minimum scalar value") {
      ascii_uint32_t.Process(std::numeric_limits<std::uint32_t>::min(), std::begin(output));
      THEN("The result is scaled as expected.") { REQUIRE(output[0] == MIN_LEVEL_CHAR); }
    }
    WHEN("Calculating output for the maximum scalar value") {
      ascii_uint32_t.Process(std::numeric_limits<std::uint32_t>::max(), std::begin(output));
      THEN("The result is scaled as expected.") { REQUIRE(output[0] == MAX_LEVEL_CHAR); }
    }
  }
}
