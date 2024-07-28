cmake_minimum_required(VERSION 3.26)
project(boxman)

set(CMAKE_CXX_STANDARD 23)

find_library(SDLFwk SDL2 REQUIRED)
find_library(SDLImg SDL2_image)
include_directories(.)
add_executable(boxman main.cpp
        window.cpp
        window.h
        errors.cpp
        errors.h
        texture.cpp
        texture.h
        level.cpp
        level.h
        gameobject.cpp
        gameobject.h
        spritesheet.cpp
        spritesheet.h
        state.h)
target_link_libraries(boxman PRIVATE ${SDLFwk} PRIVATE ${SDLImg})