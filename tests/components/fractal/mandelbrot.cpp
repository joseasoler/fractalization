#include "fractalization/components/fractal/mandelbrot.hpp"

#include "catch2/catch.hpp"

#include <cstdint>
#include <limits>

SCENARIO("Mandelbrot fractal class", "[fractal]") {
  GIVEN("A Mandelbrot fractal instance") {
    constexpr std::uint8_t MAX_ITS = std::numeric_limits<std::uint8_t>::max();
    fractalization::Mandelbrot<double, std::uint8_t, MAX_ITS> fractal;
    WHEN("Calculating the number of iterations at (0, 0)") {
      std::uint8_t fractal_its = fractal.Evaluate({0.0, 0.0});
      THEN("Reaches the maximum number of iterations.") { REQUIRE(fractal_its == MAX_ITS); }
    }
    WHEN("Calculating the number of iterations at (10, 10)") {
      std::uint8_t fractal_its = fractal.Evaluate({10.0, 10.0});
      THEN("Does not reach the maximum number of iterations.") { REQUIRE(fractal_its == 1); }
    }
  }
}
