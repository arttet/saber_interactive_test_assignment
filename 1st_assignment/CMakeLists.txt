cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(1st_assignment)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include
)
