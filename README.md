# A const-propagating member-pointer-wrapper for the C++ standard library

[![travis][badge.travis]][travis]
[![appveyor][badge.appveyor]][appveyor]
[![codecov][badge.codecov]][codecov]
[![language][badge.language]][language]
[![license][badge.license]][license]
[![issues][badge.issues]][issues]

[badge.travis]: https://img.shields.io/travis/jbcoe/propagate_const/master.svg?logo=travis
[badge.appveyor]: https://img.shields.io/appveyor/ci/jbcoe/propagate-const/master.svg?logo=appveyor
[badge.codecov]: https://img.shields.io/codecov/c/github/jbcoe/propagate_const/master.svg?logo=codecov
[badge.language]: https://img.shields.io/badge/language-C%2B%2B14-yellow.svg
[badge.license]: https://img.shields.io/badge/license-MIT-blue.svg
[badge.issues]: https://img.shields.io/github/issues/jbcoe/propagate_const.svg

[travis]: https://travis-ci.org/jbcoe/propagate_const
[appveyor]: https://ci.appveyor.com/project/jbcoe/propagate-const
[codecov]: https://codecov.io/gh/jbcoe/propagate_const
[language]: https://en.wikipedia.org/wiki/C%2B%2B14
[license]: https://en.wikipedia.org/wiki/MIT_License
[issues]: http://github.com/jbcoe/propagate_const/issues

On 2015-02-25 a proposal was accepted by the Library Working Group as N4388
and will be put forward for inclusion in Library Fundamentals Technical 
Specification V2.

# Contents
- [Integration](#integration)
  - [CMake](#cmake)
    - [External](#external)
- [Building](#building)
- [Packaging](#packaging)
  - [Conan](#conan)
- [License](#license)


# Integration
Propagate const is shipped as a single header file, [`propagate_const.h`](https://github.com/jbcoe/propagate_const/blob/master/propagate_const.h) that can be directly included in your project or included via an official [release package](https://github.com/jbcoe/propagate_const/releases).
## CMake
To include in your CMake build then add a dependency upon the interface target, `propagate_const::propagate_const`.  This provides the necessary include paths and C++ features required to include `propagate_const` into your project.

### External
To include `propagate_const` you will need use find package to locate the provided namespace imported targets from the generated package configuration.  The package configuration file, *propagate_const-config.cmake* can be included from the install location or directly out of the build tree. 
```cmake
# CMakeLists.txt
find_package(propagate_const 1.0.0 REQUIRED)
...
add_library(foo ...)
...
target_link_libraries(foo PRIVATE propagate_const::propagate_const)
```
# Building

The project contains a helper scripts for building that can be found at **<project root>/scripts/build.py**. The project can be build with the helper script as follows:

## Conan

```bash
conan create <project root> [--test-folder None]
```

## Dependencies

* [Catch2 2.10.2](https://github.com/catchorg/Catch2/tree/v2.10.2) to build the test suite

## Building Manually Via CMake

It is possible to build the project manually via CMake for a finer grained level of control regarding underlying build systems and compilers. This can be achieved as follows: 
```bash
cd <project root>
mkdir build
cd build

cmake -G <generator> <configuration options> ../
cmake --build ../
ctest
```

The following configuration options are available:

| Name                | Possible Values | Description                             | Default Value |
|---------------------|-----------------|-----------------------------------------|---------------|
| `BUILD_TESTING`     | `ON`, `OFF`     | Build the test suite                    | `ON`          |
| `ENABLE_SANITIZERS` | `ON`, `OFF`     | Build the tests with sanitizers enabled | `OFF`         |
| `Catch2_ROOT`       | `<path>`        | Path to a Catch2 installation           | undefined     |

## Installing Via CMake

```bash
cd <project root>
mkdir build
cd build

cmake -G <generator> <configuration options> -DCMAKE_INSTALL_PREFIX=<install dir> ../
cmake --install ../
```

# License

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

The [MIT License](http://opensource.org/licenses/MIT)

Copyright (c) 2017 Jonathan B. Coe

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
