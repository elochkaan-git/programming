cmake_minimum_required(VERSION 3.10)

set(VERSION_PATCH "1")
set(PROJECT_VERSION 0.1.${VERSION_PATCH})

project(lab_2_a VERSION ${PROJECT_VERSION})

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

execute_process(
  COMMAND sh -c ${CMAKE_CURRENT_SOURCE_DIR}/update_tag.sh
  OUTPUT_VARIABLE script_output
  RESULT_VARIABLE script_result
)

if (${script_result} EQUAL 1)
  message(STATUS "Script output: ${script_output}")
else()
  message(STATUS "Script output: ${script_output}")
  string(REGEX REPLACE "v" "" updated_version "${script_output}")
endif()


enable_testing()
add_executable(testing ${TEST_SOURCES})
set_target_properties(testing PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/tests)
target_link_libraries(testing GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(testing)