# Test assignment (Saber Interactive)

## Requirements

* CMake 3.10+
* GLM
* C++ 11
* [Google Test]

## Installation

You can build and run this project directly on your system.

* Download the source from GitHub with:

```sh
git clone --recursive https://github.com/arttet/saber_interactive_test_assignment
```

Alternatively, if you already have the existing source tree use:
```sh
git clone https://github.com/arttet/saber_interactive_test_assignment
git submodule update --init
```

## Building

* Run the following commands:

```sh
cd saber_interactive_test_assignment
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ../
cmake --build .
```

## Testing

```sh
cmake -DCMAKE_BUILD_TYPE=Release -DWITH_TESTS=1 ../
cmake --build .
ctest -C Release --output-on-failure --repeat-until-fail 2
```
