cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(test_1st_assignment)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
  LINK_PRIVATE
    GTest::GTest
    GTest::Main

    1st_assignment
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER tests)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
