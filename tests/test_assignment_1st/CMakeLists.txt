cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(test_assignment_1st)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
  LINK_PRIVATE
    GTest::GTest
    GTest::Main

    assignment_1st
)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
