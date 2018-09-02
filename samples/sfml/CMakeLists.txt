find_package(SFML 2.5.0 COMPONENTS graphics QUIET)

if(SFML_FOUND)
  add_executable(FractalizationSFML fractalization_sprite.hpp fractalization_sprite.cpp fractalization_sfml.cpp)

  target_link_libraries(FractalizationSFML PRIVATE Fractalization sfml-graphics)
  fractalization_target_compile_options(FractalizationSFML)
else()
  message(STATUS "SFML library not found. It will not be possible to build the Fractalization SFML sample.")
endif()