#include "fractalization/mandelbrot_ascii_gen.hpp"
#include "fractalization/components/output/ascii.hpp"

#include "catch2/catch.hpp"

#include <cstddef>
#include <cstdint>
#include <iterator>
#include <sstream>
#include <string>

SCENARIO("Mandelbrot and ASCII generator", "[generator]") {
  constexpr std::uint32_t OUTPUT_SIZE = fractalization::MandelbrotAsciiGen::OUTPUT_SIZE;
  static constexpr char MIN_LEVEL_CHAR = (*std::cbegin(fractalization::ASCII_LEVELS));
  static constexpr char MAX_LEVEL_CHAR = (*std::crbegin(fractalization::ASCII_LEVELS));
  GIVEN("A generator centered on [0.0 and 0.0] and a string.") {
    constexpr std::uint32_t OUTPUT_SIDE = 25;
    std::ostringstream os;
    fractalization::MandelbrotAsciiGen gen_small{OUTPUT_SIDE, OUTPUT_SIDE, 0.0, 0.0, 0.0, OUTPUT_SIDE * 0.25};
    WHEN("The string is generated.") {
      std::ostreambuf_iterator<char> it{os};
      gen_small.Generate(it);
      std::string s{os.str()};
      THEN(
          "The central character of the string ([0.0, 0.0] in the complex plane) "
          "has the character assigned to the maximum number of iterations.") {
        const std::uint32_t center_idx = OUTPUT_SIDE * OUTPUT_SIDE / 2;
        REQUIRE(s[center_idx * OUTPUT_SIZE] == MAX_LEVEL_CHAR);
      }
      THEN(
          "The first character of the string (top left corner of the image) has the character assigned to the minimum "
          "number of iterations.") {
        const std::uint32_t top_left_idx = 0;
        REQUIRE(s[top_left_idx * OUTPUT_SIZE] == MIN_LEVEL_CHAR);
      }
    }
  }
}
