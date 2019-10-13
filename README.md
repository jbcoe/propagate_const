# A const-propagating member-pointer-wrapper for the C++ standard library

On 2015-02-25 a proposal was accepted by the Library Working Group as N4388
and will be put forward for inclusion in Library Fundamentals Technical 
Specification V2.

## Build status
- on Travis: [![Travis Build Status](https://travis-ci.org/jbcoe/propagate_const.svg?branch=master)](https://travis-ci.org/jbcoe/propagate_const)
- on AppVeyor: [![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/github/jbcoe/propagate_const?svg=true&branch=master)](https://ci.appveyor.com/project/jbcoe/propagate-const)

# Contents
- [Building](#building)
- [Packaging](#packaging)
  - [Conan](#conan)
- [License](#license)

# Building

The project contains a helper scripts for building that can be found at **<project root>/scripts/build.py**. The project can be build with the helper scipt as follows:

```bash
cd <project root>
python script/build.py [--clean] [-o|--output=<build dir>] [-c|--config=<Debug|Release>] [--sanitizers] [-v|--verbose] [-t|--tests]
```

The script will by default build the project via Visual Studio on Windows. On Linux and Mac it will attempt to build via Ninja if available, then Make and will default to the system defaults for choice of compiler.

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

## Installing Via CMake

```bash
cd <project root>
mkdir build
cd build

cmake -G <generator> <configuration options> -DCMAKE_INSTALL_PREFIX=<install dir> ../
cmake --install ../
```

# Packaging
## Conan
```bash
cd <project root>
conan create ./ propagate_const/1.0@conan/stable -tf .conan/test_package
```


# License

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

The [MIT License](http://opensource.org/licenses/MIT)

Copyright (c) 2017 Jonathan B. Coe

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
