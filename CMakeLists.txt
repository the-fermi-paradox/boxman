cmake_minimum_required(VERSION 3.26)
project(boxman)

set(CMAKE_CXX_STANDARD 17)

include_directories(${SDL2_INCLUDE_DIRS})
find_package(SDL2 REQUIRED COMPONENTS SDL2)
find_package(SDL2_image REQUIRED)
add_executable(boxman main.cpp
        window.cpp
        window.h
        errors.cpp
        errors.h
        texture.cpp
        texture.h)
target_link_libraries(boxman PRIVATE SDL2::SDL2 PRIVATE SDL2_image::SDL2_image)