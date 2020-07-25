# stereogram

Simple generator of Single Image Random Dot Stereograms (SIRDS).
Based on an included paper.

## How to build

Required: Conan, CMake and C++17 conformant compiler.

* `mkdir build && cd build`
* `conan install .. --build missing`
* `cmake ..`
* `cmake --build .`
