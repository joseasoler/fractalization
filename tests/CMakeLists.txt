find_package(Catch2 2.3.0 REQUIRED)

# Export compile commands for static analysis tools.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(FractalizationTests
  fractalization_tests.cpp # Catch2 main file
  components/transformation.cpp
  components/fractal/mandelbrot.cpp
  components/output/ascii.cpp
  components/output/grayscale_rgba.cpp
  mandelbrot_ascii_gen.cpp
  mandelbrot_grayscale_gen.cpp
        generator.cpp)

target_link_libraries(FractalizationTests PRIVATE Fractalization Catch2::Catch2)

fractalization_target_compile_options(FractalizationTests)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # Default code analysis. Catch2 will trigger warnings with extensions
  target_compile_options(FractalizationTests PRIVATE /analyze)
endif()

add_test(NAME Tests COMMAND $<TARGET_FILE:FractalizationTests>)
