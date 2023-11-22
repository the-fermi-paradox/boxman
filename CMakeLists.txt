cmake_minimum_required(VERSION 3.26)
project(boxman)

set(CMAKE_CXX_STANDARD 17)

add_executable(boxman main.cpp)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(boxman ${SDL2_LIBRARIES})