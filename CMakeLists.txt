cmake_minimum_required(VERSION 3.22)
project(mycache VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(MYCACHE_CLANG_TIDY "Run clang-tidy on the project's code during the build" OFF)

add_library(mycache_warnings INTERFACE)
target_compile_options(mycache_warnings INTERFACE -Wall -Wextra -Wpedantic -Werror)

add_library(mycache_core src/args.cpp)
target_include_directories(mycache_core PUBLIC src)
target_link_libraries(mycache_core PRIVATE mycache_warnings)

add_executable(mycache src/main.cpp)
target_link_libraries(mycache PRIVATE mycache_core mycache_warnings)
target_compile_definitions(mycache PRIVATE MYCACHE_VERSION="${PROJECT_VERSION}")

if(MYCACHE_CLANG_TIDY)
  find_program(CLANG_TIDY_EXE NAMES clang-tidy REQUIRED)
  # Set per target so that GoogleTest, fetched below, is not analyzed.
  set_target_properties(mycache_core mycache PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif()

include(CTest)
if(BUILD_TESTING)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG 52eb8108c5bdec04579160ae17225d66034bd723 # v1.17.0
  )
  FetchContent_MakeAvailable(googletest)

  add_executable(mycache_tests tests/args_test.cpp)
  target_link_libraries(mycache_tests PRIVATE mycache_core mycache_warnings GTest::gtest_main)

  include(GoogleTest)
  gtest_discover_tests(mycache_tests)
endif()
