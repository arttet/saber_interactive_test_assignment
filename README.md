# Test assignment (Saber Interactive)
[![Build Status](https://dev.azure.com/arttet/CI/_apis/build/status/1?api-version=5.1-preview.1)](https://dev.azure.com/arttet/CI/_build?definitionId=1&_a=summary)

## Requirements

* CMake 3.11.4+
* GLM
* C++ 11
* Google Test

## Installation

You could build and run this project directly on your system.

* Download the source from GitHub with:

```sh
git clone https://github.com/arttet/saber_interactive_test_assignment
```

## Build

* Run the following commands:

```sh
cd saber_interactive_test_assignment
mkdir build
cd build
cmake ../
cmake --build . --config Release
```

## Test

```sh
cmake -DWITH_TESTS=1 ../
cmake --build . --config Release
ctest -C Release --output-on-failure --repeat-until-fail 2
```
