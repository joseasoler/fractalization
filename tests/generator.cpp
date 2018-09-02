#include "fractalization/generator.hpp"
#include "catch2/catch.hpp"
#include "fractalization/components/transformation.hpp"

#include <deque>
#include <list>
#include <vector>

enum class GenResult {
  EVEN_ROW,
  ODD_ROW,
  NOT_GENERATED,
};

class FractalGenTest {
 public:
  GenResult Evaluate(std::pair<float, float> cp) const {
    auto row = static_cast<std::uint64_t>(cp.first);
    return ((row % 2) == 0) ? GenResult::EVEN_ROW : GenResult::ODD_ROW;
  }
};

class OutputGenTest {
 public:
  static constexpr std::uint32_t OUTPUT_SIZE = 1;

  template <class RndmIt>
  RndmIt Process(GenResult fractal_scalar, RndmIt output_start) const {
    *output_start = fractal_scalar;
    output_start++;
    return output_start;
  }
};

using GenTest = fractalization::Generator<float, FractalGenTest, OutputGenTest>;

enum class GenTestResult {
  SUCCESS,
  INCORRECT_GENERATION,
  NOT_GENERATED,
};

template <class ExecutionTag, class SeqContainer>
GenTestResult TestGeneration(ExecutionTag tag, std::uint32_t width, std::uint32_t height) {
  auto center_w = static_cast<float>(width) / 2.f;
  auto center_h = static_cast<float>(height) / 2.f;
  GenTest gen{fractalization::Transformation<float>(width, height, center_w, center_h, 0.f, 1.f),
              FractalGenTest(), OutputGenTest()};
  SeqContainer image(width * height, GenResult::NOT_GENERATED);
  gen.Generate(tag, std::begin(image));

  bool found_error = false;
  GenResult error_result = GenResult::NOT_GENERATED;

  auto it_image = std::begin(image);
  for (std::uint32_t idx = 0; idx < image.size(); idx++) {
    GenResult expected = ((idx % width) % 2) == 0 ? GenResult::EVEN_ROW : GenResult::ODD_ROW;
    GenResult result = *it_image;
    if (expected != result) {
      found_error = true;
      error_result = result;
      break;
    }
    it_image++;
  }

  if (!found_error) {
    return GenTestResult::SUCCESS;
  }
  if (error_result == GenResult::NOT_GENERATED) {
    return GenTestResult ::NOT_GENERATED;
  }
  return GenTestResult ::INCORRECT_GENERATION;
}

SCENARIO("A generator is used to create a 100x50 image sequentially", "[Generator]") {
  GIVEN("A simple generator") {
    WHEN("A 100x50 image is generated sequentially") {
      GenTestResult result =
          TestGeneration<fractalization::Sequential, std::vector<GenResult>>(fractalization::SEQUENTIAL, 100, 50);
      THEN("All points of the image have been generated") { REQUIRE(result != GenTestResult::NOT_GENERATED); }
      THEN("All points of the image have the expected value") {
        REQUIRE(result != GenTestResult::INCORRECT_GENERATION);
      }
    }
  }
}
SCENARIO("A generator is used to create a 1000x800 image sequentially", "[Generator]") {
  GIVEN("A simple generator") {
    WHEN("A 1000x800 image is generated sequentially") {
      GenTestResult result =
          TestGeneration<fractalization::Sequential, std::vector<GenResult>>(fractalization::SEQUENTIAL, 1000, 800);
      THEN("All points of the image have been generated") { REQUIRE(result != GenTestResult::NOT_GENERATED); }
      THEN("All points of the image have the expected value") {
        REQUIRE(result != GenTestResult::INCORRECT_GENERATION);
      }
    }
  }
}
SCENARIO("A generator is used to create a 400x1500 image sequentially", "[Generator]") {
  GIVEN("A simple generator") {
    WHEN("A 400x1500 image is generated sequentially") {
      GenTestResult result =
          TestGeneration<fractalization::Sequential, std::vector<GenResult>>(fractalization::SEQUENTIAL, 400, 1500);
      THEN("All points of the image have been generated") { REQUIRE(result != GenTestResult::NOT_GENERATED); }
      THEN("All points of the image have the expected value") {
        REQUIRE(result != GenTestResult::INCORRECT_GENERATION);
      }
    }
  }
}
SCENARIO("A generator is used to create a 100x50 image in parallel", "[Generator]") {
  GIVEN("A simple generator") {
    WHEN("A 100x50 image is generated in parallel") {
      GenTestResult result =
          TestGeneration<fractalization::Parallel, std::vector<GenResult>>(fractalization::PARALLEL, 100, 50);
      THEN("All points of the image have been generated") { REQUIRE(result != GenTestResult::NOT_GENERATED); }
      THEN("All points of the image have the expected value") {
        REQUIRE(result != GenTestResult::INCORRECT_GENERATION);
      }
    }
  }
}
SCENARIO("A generator is used to create a 1000x800 image in parallel", "[Generator]") {
  GIVEN("A simple generator") {
    WHEN("A 1000x800 image is generated in parallel") {
      GenTestResult result =
          TestGeneration<fractalization::Parallel, std::vector<GenResult>>(fractalization::PARALLEL, 1000, 800);
      THEN("All points of the image have been generated") { REQUIRE(result != GenTestResult::NOT_GENERATED); }
      THEN("All points of the image have the expected value") {
        REQUIRE(result != GenTestResult::INCORRECT_GENERATION);
      }
    }
  }
}
SCENARIO("A generator is used to create a 400x1500 image in parallel", "[Generator]") {
  GIVEN("A simple generator") {
    WHEN("A 400x1500 image is generated in parallel") {
      GenTestResult result =
          TestGeneration<fractalization::Parallel, std::vector<GenResult>>(fractalization::PARALLEL, 400, 1500);
      THEN("All points of the image have been generated") { REQUIRE(result != GenTestResult::NOT_GENERATED); }
      THEN("All points of the image have the expected value") {
        REQUIRE(result != GenTestResult::INCORRECT_GENERATION);
      }
    }
  }
}
SCENARIO("A generator is used to create an image in parallel inside of a list", "[Generator]") {
  GIVEN("A simple generator") {
    WHEN("An image is generated in parallel in a list") {
      GenTestResult result =
          TestGeneration<fractalization::Parallel, std::list<GenResult>>(fractalization::PARALLEL, 300, 300);
      THEN("All points of the image have been generated") { REQUIRE(result != GenTestResult::NOT_GENERATED); }
      THEN("All points of the image have the expected value") {
        REQUIRE(result != GenTestResult::INCORRECT_GENERATION);
      }
    }
  }
}
SCENARIO("A generator is used to create an image in parallel inside of a deque", "[Generator]") {
  GIVEN("A simple generator") {
    WHEN("An image is generated in parallel in a deque") {
      GenTestResult result =
          TestGeneration<fractalization::Parallel, std::deque<GenResult>>(fractalization::PARALLEL, 300, 300);
      THEN("All points of the image have been generated") { REQUIRE(result != GenTestResult::NOT_GENERATED); }
      THEN("All points of the image have the expected value") {
        REQUIRE(result != GenTestResult::INCORRECT_GENERATION);
      }
    }
  }
}
