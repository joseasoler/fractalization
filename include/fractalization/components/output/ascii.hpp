#ifndef FRACTALIZATION_COMPONENTS_OUTPUT_ASCII_HPP
#define FRACTALIZATION_COMPONENTS_OUTPUT_ASCII_HPP

#include <array>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>

namespace fractalization {

// http://paulbourke.net/dataformats/asciiart/
static constexpr std::array<char, 70> ASCII_LEVELS{
    '$', '@', 'B', '%', '8', '&',  'W', 'M', '#', '*', 'o', 'a', 'h', 'k',  'b', 'd', 'p', 'q',
    'w', 'm', 'Z', 'O', '0', 'Q',  'L', 'C', 'J', 'U', 'Y', 'X', 'z', 'c',  'v', 'u', 'n', 'x',
    'r', 'j', 'f', 't', '/', '\\', '|', '(', ')', '1', '{', '}', '[', ']',  '?', '-', '_', '+',
    '~', '<', '>', 'i', '!', 'l',  'I', ';', ':', ',', '"', '^', '`', '\'', '.', ' '};

template <typename FrctlScalar, typename CharScalar>
class Ascii {
 private:
  static_assert(std::is_same<CharScalar, char>::value, "ASCII output only supports char.");
  static_assert(sizeof(FrctlScalar) < sizeof(std::uint64_t));

 public:
  static constexpr std::uint32_t OUTPUT_SIZE = 1;

  template <class RndmIt>
  RndmIt Process(FrctlScalar fractal_scalar, RndmIt output_start) const {
    auto scale_idx = static_cast<std::uint64_t>(fractal_scalar);
    scale_idx *= (ASCII_LEVELS.size() - 1);
    scale_idx /= std::numeric_limits<FrctlScalar>::max();
    auto idx = static_cast<std::array<char, 70>::size_type>(scale_idx);

    *output_start = ASCII_LEVELS.at(idx);
    output_start++;
    return output_start;
  }
};
}  // namespace fractalization

#endif  // FRACTALIZATION_COMPONENTS_OUTPUT_ASCII_HPP
