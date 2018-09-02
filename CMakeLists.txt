cmake_minimum_required(VERSION 3.8)

project(Fractalization VERSION 0.1.0 LANGUAGES CXX)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
enable_testing() # Include CTest without enabling all extra targets.

option(FRACTALIZATION_WARNINGS_AS_ERRORS "Treat warnings as errors when compiling tests and samples." ON)
option(FRACTALIZATION_CLANG_TIDY "Compile tests and samples using clang-tidy." OFF)

# Fractalization uses futures.
find_package(Threads REQUIRED)

# External dependencies
find_package(Eigen3 3.3 REQUIRED)

set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}/Fractalization")

# Fractalization definition
add_library(Fractalization INTERFACE)
target_compile_features(Fractalization INTERFACE cxx_std_17)
target_include_directories(Fractalization INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}>
)
target_link_libraries(Fractalization INTERFACE Eigen3::Eigen Threads::Threads)

# Fractalization installation
install(TARGETS Fractalization EXPORT FractalizationTargets)


set(FRACTALIZATION_CMAKE_CONFIG_DESTINATION
    "${CMAKE_INSTALL_DATADIR}/Fractalization/cmake")
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/FractalizationConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/FractalizationConfig.cmake"
    INSTALL_DESTINATION ${FRACTALIZATION_CMAKE_CONFIG_DESTINATION}
)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/FractalizationConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)
install(EXPORT FractalizationTargets
    DESTINATION ${FRACTALIZATION_CMAKE_CONFIG_DESTINATION})
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/FractalizationConfigVersion.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/FractalizationConfig.cmake"
    DESTINATION ${FRACTALIZATION_CMAKE_CONFIG_DESTINATION}
)
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION "${INCLUDE_INSTALL_DIR}")

if (FRACTALIZATION_CLANG_TIDY)
  find_program(
      CLANG_TIDY_BINARY
      NAMES "clang-tidy"
      DOC "Clang-tidy binary"
  )

  if(FRACTALIZATION_WARNINGS_AS_ERRORS)
    set(DO_CLANG_TIDY "${CLANG_TIDY_BINARY}" "-warnings-as-errors=*")
  else()
    set(DO_CLANG_TIDY "${CLANG_TIDY_BINARY}")
  endif()
endif()


macro(fractalization_target_compile_options target_arg)
  # Compiler-specific warning flags.
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options("${target_arg}" PRIVATE
        -Weverything # Enable all warnings by default.
        -Wno-c++98-compat -Wno-c++98-compat-pedantic  # Disable c++98 warnings.
        -Wno-switch-enum
        -Wno-padded
        )
  endif()
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options("${target_arg}" PRIVATE
        -Wall -Wextra # Enable most warnings.
        -Wpedantic  # Enforce strict standards conformance
        # Extra warnings recommended on C++ Best Practices.
        -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused
        -Woverloaded-virtual -Wconversion -Wsign-conversion
        -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches
        -Wlogical-op -Wnull-dereference -Wdouble-promotion
        -Wformat=2 -Wmissing-declarations -Wunreachable-code
        )
  endif()
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # Disable default warning level (if any), and enable all level 4 warnings
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
      string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
      target_compile_options("${target_arg}" PRIVATE /W4)
    endif()

    target_compile_options("${target_arg}" PRIVATE
        /permissive- # Enforce strict standards conformance
        # Default code analysis. Catch2 will trigger warnings if extensions are used.
        /analyze
        # Extra warnings recommended on C++ Best Practices.
        /w14640 /w14254 /w14263 /w14265 /w14287 /we4289 /w14296 /w14311 /w14545
        /w14546 /w14547 /w14549 /w14555 /w14640 /w14826 /w14905 /w14906 /w14928)

    # Disable warnings for Eigen header files.
    get_target_property(EIGEN3_INCLUDE_DIRECTORIES
        Eigen3::Eigen INTERFACE_INCLUDE_DIRECTORIES)
    target_compile_options("${target_arg}" PRIVATE
        /experimental:external /external:I "${EIGEN3_INCLUDE_DIRECTORIES}"
        /external:W0)
    # Disable warnings triggered when using Eigen3 code.
    target_compile_options("${target_arg}" PRIVATE
        /wd6326) # Potential comparison of a constant with another constant.
  endif()

  if(FRACTALIZATION_WARNINGS_AS_ERRORS)
    # Treat warnings as errors in all projects.
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
      target_compile_options("${target_arg}" PRIVATE /WX)
    endif()
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR
        "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
      target_compile_options("${target_arg}" PRIVATE -Werror)
    endif()
  endif()

  if(FRACTALIZATION_CLANG_TIDY AND CLANG_TIDY_BINARY)
    set_target_properties(
        ${target_arg} PROPERTIES
        CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
    )
  endif()
endmacro()

add_subdirectory(samples)
add_subdirectory(tests EXCLUDE_FROM_ALL)

# Build examples, is re