cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(test_3rd_assignment)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
  LINK_PRIVATE
    GTest::GTest
    GTest::Main

    3rd_assignment
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  FOLDER tests
  VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data/ $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

add_test(NAME ${PROJECT_NAME}
  COMMAND ${PROJECT_NAME}
  WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

install(TARGETS ${PROJECT_NAME} DESTINATION tests COMPONENT tests)
