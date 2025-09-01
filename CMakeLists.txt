cmake_minimum_required(VERSION 3.10)
project(lab_2_a)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
)
FetchContent_MakeAvailable(googletest)

file(GLOB SOURCES "*.cpp")
file(GLOB TEST_SOURCES "tests/*.cpp")

add_executable(main ${SOURCES})
target_compile_features(main PRIVATE cxx_std_17)

enable_testing()
add_executable(testing ${TEST_SOURCES})
set_target_properties(testing PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/tests)
target_link_libraries(testing GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(testing)