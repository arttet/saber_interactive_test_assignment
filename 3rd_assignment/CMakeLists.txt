cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(3rd_assignment)

file(GLOB_RECURSE ALL_SOURCE_FILES
  "*.h"
  "*.cpp"
)

add_library(${PROJECT_NAME} STATIC ${ALL_SOURCE_FILES})

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include
)

target_link_libraries(${PROJECT_NAME}
  LINK_PUBLIC
    glm
)
