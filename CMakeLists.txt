cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(test_assignment VERSION 0.0.0 LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(WITH_TESTS "Build tests" OFF)

if (MSVC)
  add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_subdirectory(3rd_party)

add_subdirectory(assignment_1st)
add_subdirectory(assignment_2nd)
add_subdirectory(assignment_3rd)

if (WITH_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
