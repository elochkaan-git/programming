cmake_minimum_required(VERSION 3.10.0)
project(lab_1_00 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(lab_1_00 main.cpp func/activities_counter.cpp func/attention.cpp func/is_active.cpp func/switch.cpp pip_girl.h)

set(CPACK_PROJECT_NAME $(PROJECT_NAME))
set(CPACK_PROJECT_VERSION $(PROJECT_VERSION))
include(CPack)