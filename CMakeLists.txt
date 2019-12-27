cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(test_assignment VERSION 0.0.0 LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(WITH_TESTS "Build tests" OFF)

add_subdirectory(3rd_party)

add_subdirectory(assignment_1st)
add_subdirectory(assignment_2nd)
add_subdirectory(assignment_3rd)

if (WITH_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
