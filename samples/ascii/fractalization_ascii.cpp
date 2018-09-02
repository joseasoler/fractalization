#include "fractalization/mandelbrot_ascii_gen.hpp"

#include <iostream>
#include <iterator>

class FixedWidthOstreambufIterator {
 public:
  using char_type = char;
  using traits_type = std::char_traits<char>;
  using ostream_type = std::basic_ostream<char_type, traits_type>;
  using streambuf_type = std::basic_streambuf<char_type, traits_type>;
  using iterator_category = std::output_iterator_tag;
  using value_type = void;
  using difference_type = void;
  using pointer = void;
  using reference = void;

 private:
  std::ostreambuf_iterator<char> it_;
  std::uint32_t width_;
  std::uint32_t curr_width_;

 public:
  explicit FixedWidthOstreambufIterator(std::uint32_t width)
      : it_{std::ostreambuf_iterator<char>(std::cout)}, width_{width}, curr_width_{0} {}

  FixedWidthOstreambufIterator& operator=(const char& value) {
    it_ = value;
    curr_width_++;
    if (curr_width_ == width_) {
      it_ = '\n';
      curr_width_ = 0;
    }
    return *this;
  }

  FixedWidthOstreambufIterator& operator*() { return *this; }

  FixedWidthOstreambufIterator& operator++() { return *this; }  // NOLINT

  FixedWidthOstreambufIterator& operator++(int) { return *this; }  // NOLINT
};

int main() {
  unsigned int width = 100;
  unsigned int height = 45;
  fractalization::MandelbrotAsciiGen mandelbrot_gen{width, height, -0.5, -0.1, 0.3, width * 0.25};
  mandelbrot_gen.Generate(FixedWidthOstreambufIterator{width});
}
