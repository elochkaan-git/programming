cmake_minimum_required(VERSION 3.10)

project(hash_and_files)

add_executable(hash task_1.cpp hash.cpp hash.hpp)

add_executable(store task_2.cpp store.cpp store.hpp)

find_package(OpenCV REQUIRED)
find_package(OpenSSL REQUIRED)
add_executable(hash_image task_3.cpp image.hpp image.cpp)
target_link_libraries(hash_image ${OpenCV_LIBRARIES} OpenSSL::Crypto)