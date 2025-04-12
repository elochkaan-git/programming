include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/releases/download/v1.16.0/googletest-1.16.0.tar.gz
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(COMMON_SRCS "../main.cpp")

add_executable(tests tests.cpp ${COMMON_SRCS})
target_include_directories(tests PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(tests PUBLIC gtest gtest_main)