cmake_minimum_required(VERSION 3.10.0)
project(lab_5 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

# Source for part 1
# set(SOURCE_FILES multifiles/lab_2.cpp multifiles/functions.cpp multifiles/functions.hpp)

# Source for part 2
# set(SOURCE_FILES div_without_div/division_without_division.cpp)

# Source for part 3
set(SOURCE_FILES try-catch/try-catch.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

include(CPack)
