#ifndef FRACTALIZATION_GENERATOR_HPP
#define FRACTALIZATION_GENERATOR_HPP

#include "fractalization/components/transformation.hpp"

#include <future>
#include <iterator>
#include <type_traits>
#include <utility>
#include <vector>

namespace fractalization {

namespace internal {

template <class It, class Transformation, class Fractal, class Output>
inline void GenerateIdx(std::uint32_t *output_idx, It &output_begin, const Transformation &transformation,
                        const Fractal &fractal, const Output &output) {
  const auto c_point = transformation.Transform(*output_idx);
  const auto f_value = fractal.Evaluate(c_point);
  output_begin = output.Process(f_value, output_begin);
  (*output_idx)++;
}

template <class It, class Transformation, class Fractal, class Output>
void GenerationTask(std::uint32_t output_idx, It output_begin, std::uint32_t total_output_idxs,
                    const Transformation &transformation, const Fractal &fractal, const Output &output) {
  auto output_idx_end = output_idx + total_output_idxs;
  while (output_idx < output_idx_end) {
    GenerateIdx(&output_idx, output_begin, transformation, fractal, output);
  }
}

}  // namespace internal

struct Sequential {};
struct Parallel {};
static constexpr Sequential SEQUENTIAL{};
static constexpr Parallel PARALLEL{};

template <typename CmplxScalar, class Fractal, class Output>
class Generator {
 private:
  Transformation<CmplxScalar> transformation_;
  const Fractal fractal_;
  const Output output_;

  template <class FwdIt>
  std::enable_if_t<
      std::is_base_of<std::forward_iterator_tag, typename std::iterator_traits<FwdIt>::iterator_category>::value, void>
  DoGenerate(Parallel /* tag */, FwdIt output_begin) const {
    // ToDo Switch to parallel STL algorithms with execution policies when they are implemented in GCC and clang.
    std::uint32_t output_idx = 0;

    auto num_tasks = std::min(transformation_.width, transformation_.height);
    auto task_size = std::max(transformation_.width, transformation_.height);
    std::vector<std::future<void>> gen_tasks{num_tasks};
    FwdIt task_begin = output_begin;
    // Lambda responsible for task creation.
    auto task_creator = [this, &task_begin, &output_idx, task_size]() -> std::future<void> {
      auto future = std::async(std::launch::async, [output_idx, task_begin, task_size, this]() {
        internal::GenerationTask<FwdIt, Transformation<CmplxScalar>, Fractal, Output>(
            output_idx, task_begin, task_size, transformation_, fractal_, output_);
      });

      // Update starting values for the next task.
      output_idx += task_size;
      std::advance(task_begin, task_size * Output::OUTPUT_SIZE);
      return future;
    };

    // Launch each task, and fill the vector with their futures.
    std::generate(std::begin(gen_tasks), std::end(gen_tasks), task_creator);

    // Wait until all tasks are done.
    for (const auto &f : gen_tasks) {
      f.wait();
    }
  }

  template <class It>
  void DoGenerate(Sequential /* tag */, It output_begin) const {
    std::uint32_t output_idx = 0;
    std::uint32_t total_output_idxs = transformation_.width * transformation_.height;
    internal::GenerationTask(output_idx, output_begin, total_output_idxs, transformation_, fractal_, output_);
  }

 public:
  static constexpr std::uint32_t OUTPUT_SIZE = Output::OUTPUT_SIZE;
  Generator(Transformation<CmplxScalar> t, Fractal f, Output p)
      : transformation_{std::move(t)}, fractal_{std::move(f)}, output_{std::move(p)} {}

  template <class It, class ExecutionTag>
  void Generate(ExecutionTag tag, It output_begin) const {
    DoGenerate(tag, output_begin);
  }

  template <class It>
  void Generate(It output_begin) const {
    DoGenerate(SEQUENTIAL, output_begin);
  }

  Transformation<CmplxScalar> &GetTransformation() { return transformation_; }
};

}  // namespace fractalization

#endif  // FRACTALIZATION_GENERATOR_HPP
