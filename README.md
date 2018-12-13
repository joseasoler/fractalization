# Fractalization

Fractalization is a header-only fractal generation library, implemented using C++17. This library splits the fractal generation process in three different components:

**Transformation:** Given the position of one of the points of the image, obtains the complex number that it is going to display.

**Fractal:** Obtains the number of iterations required to check if a complex number is part of a fractal set.

**Output:** Converts the number of iterations obtained in the previous step to the desired output format, which could be an RGBA pixel, ASCII...

Fractalization allows to compose different component implementations to create a fractal generator. This fractal generator class is generated in compile-time.
## Getting Started

Fractalization provides CMake support. You can use CMake to build the samples and tests, or to install the library. Fractalization also supports Cmake's find_package command. Alternatively, you can download Fractalization and add its include folder to your project's header search path.

The only dependency required to use Fractalization is [Eigen3](http://eigen.tuxfamily.org/index.php?title=Main_Page). [SFML](https://www.sfml-dev.org/) is an optional dependency, and it is used by one of the sample programs.

### Samples

If you want to check some examples, Fractalization includes some sample programs in the samples subfolder.

####  ASCII

![ASCII](https://user-images.githubusercontent.com/3092211/44953339-c85c9d00-ae8b-11e8-9429-7245a29b3a17.png)

####  SFML

![SFML](https://user-images.githubusercontent.com/3092211/44953340-cc88ba80-ae8b-11e8-90ca-aeda9f7fb925.png)

## Development

### Compiler support

This project has been developed and tested using [Clang](https://clang.llvm.org/), [GCC](https://gcc.gnu.org/) and [Microsoft Visual Studio](https://visualstudio.microsoft.com/) and it has been tested on Linux and Windows. You will need a compiler version that supports most of the features of the C++17 standard.

### Testing

Fractalization uses [Catch2](https://github.com/catchorg/Catch2) for its tests, and they are built by the FractalizationTests target. Check the [Command line](https://github.com/catchorg/Catch2/blob/master/docs/command-line.md) section of the Catch2 documentation for details on how to run the tests.

### Coding style

Fractalization follows the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html), with a few exceptions:

* Longer line length (120).
* C++ file extension is cpp. Header file extension is hpp.
* Filenames and folder names are all lowercase and use underscores (_) as separator.

The project supports [clang-format](https://clang.llvm.org/docs/ClangFormat.html); check the [.clang-format](.clang-format) and [.clang-tidy](.clang-tidy) files for details.

### Versioning

Fractalization uses [Semantic Versioning](http://semver.org/). For the versions available, see the [tags on this repository](https://github.com/terkhen/fractalization/tags).

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

* **[Billie Thompson](https://github.com/PurpleBooth)** - [README.md template](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2)
* **[Jacek Galowicz](https://galowicz.de/)** - Fractalization started as an experiment about two of the recipes of the [C++17 STL Cookbook](https://www.packtpub.com/application-development/c17-stl-cookbook) book.
* **[Jason Turner](https://github.com/lefticus)** - [C++ Best Practices](https://lefticus.gitbooks.io/cpp-best-practices/) for all of its great content in general, and the recommended compilation flags in particular.
* **[Manuel Binna](https://github.com/mbinna)** - [Effective Modern CMake](https://gist.github.com/mbinna/c61dbb39bca0e4fb7d1f73b0d66a4fd1)
* **[Mario Badr](https://github.com/mariobadr)** - [Using clang-tidy with CMake](http://mariobadr.com/using-clang-tidy-with-cmake-36.html)
* **[Paul Bourke](http://paulbourke.net)** - [Character representation of grey scale images](http://paulbourke.net/dataformats/asciiart/)
