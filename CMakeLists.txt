cmake_minimum_required(VERSION 3.9.2)
project(boxman)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
add_custom_target(copy_levels ALL
        COMMAND ${CMAKE_COMMAND} -E echo "Copying level files..."
        COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/levels
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/levels ${CMAKE_BINARY_DIR}/levels
)
add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E echo "Copying asset files..."
        COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/sokoban
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/sokoban ${CMAKE_BINARY_DIR}/sokoban
)
add_custom_target(copy_music ALL
        COMMAND ${CMAKE_COMMAND} -E echo "Copying music files..."
        COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/music
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/music ${CMAKE_BINARY_DIR}/music
)

find_library(SDLFwk SDL2 REQUIRED)
find_library(SDLImg SDL2_image)
find_library(SDLMixer SDL2_mixer)
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
        GameObjects/Crate.cpp
        GameObjects/Crate.h
        GameObjects/Player.cpp
        GameObjects/Player.h
        GameObjects/Obstacle.cpp
        GameObjects/Obstacle.h
        GameObjects/Moveable.cpp
        GameObjects/Moveable.h
        GameObjects/Target.cpp
        GameObjects/Target.h
        Game.cpp
        Game.h
        Renderer.cpp
        Renderer.h
)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/cargs)
add_dependencies(boxman copy_levels copy_assets copy_music)
target_link_libraries(boxman PRIVATE cargs PRIVATE ${SDLFwk} PRIVATE ${SDLImg} PRIVATE ${SDLMixer})

