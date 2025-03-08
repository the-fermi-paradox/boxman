cmake_minimum_required(VERSION 3.26)
project(boxman)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")

find_library(SDLFwk SDL2 REQUIRED)
find_library(SDLImg SDL2_image)
include_directories(.)
add_executable(
        boxman
        main.cpp
        Window.cpp
        Window.h
        errors.cpp
        errors.h
        Texture.cpp
        Texture.h
        level.cpp
        level.h
        GameObjects/GameObject.cpp
        GameObjects/GameObject.h
        Spritesheet.cpp
        Spritesheet.h
        State.h
        Crate.cpp
        Crate.h
        GameObjects/Player.cpp
        GameObjects/Player.h
        GameObjects/Obstacle.cpp
        GameObjects/Obstacle.h
        GameObjects/Moveable.cpp
        GameObjects/Moveable.h
        GameObjects/Target.cpp
        GameObjects/Target.h
)
target_link_libraries(boxman PRIVATE ${SDLFwk} PRIVATE ${SDLImg})

add_custom_command(TARGET boxman POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/sokoban ${CMAKE_BINARY_DIR}/sokoban
        COMMENT "Copying sokoban assets..."
)

add_custom_command(TARGET boxman POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/level.json ${CMAKE_BINARY_DIR}/level.json
        COMMENT "Copying level.json..."
)
