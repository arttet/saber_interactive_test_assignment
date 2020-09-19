cmake_minimum_required(VERSION 3.11.4 FATAL_ERROR)

project(test_assignment VERSION 1.0.0 LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(WITH_TESTS "Build tests" ON)

if (MSVC)
  string(REGEX REPLACE "/W[1-3]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
  add_compile_options(/EHsc)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

include(FetchContent)
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        0.9.9.8
)
FetchContent_GetProperties(glm)
if (NOT glm)
  FetchContent_Populate(glm)
  add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_subdirectory(1st_assignment)
add_subdirectory(2nd_assignment)
add_subdirectory(3rd_assignment)

if (WITH_TESTS)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.10.0
  )
  FetchContent_GetProperties(googletest)
  if (NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
  endif()

  add_library(GTest::GTest ALIAS gtest)
  add_library(GTest::Main ALIAS gtest_main)

  enable_testing()
  add_subdirectory(tests)

  install(DIRECTORY data/ DESTINATION tests COMPONENT tests)
  install(TARGETS RUNTIME DESTINATION tests COMPONENT tests)
endif()

foreach(RUNTIME_DESTINATION IN ITEMS tests)
  set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION ${RUNTIME_DESTINATION})
  include(InstallRequiredSystemLibraries)
endforeach()
install(FILES LICENSE README.md DESTINATION .)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README  "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
include (CPack)
