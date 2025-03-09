cmake_minimum_required(VERSION 3.26)
project(boxman)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")

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
target_link_libraries(boxman PRIVATE ${SDLFwk} PRIVATE ${SDLImg} PRIVATE ${SDLMixer})

# Function to collect all files in a directory (CMake 3.12+ required)
function(collect_files DIR OUT_VAR)
    file(GLOB_RECURSE FILES ${DIR}/*)
    set(${OUT_VAR} ${FILES} PARENT_SCOPE)
endfunction()

# Collect all files inside sokoban and levels
collect_files(${CMAKE_SOURCE_DIR}/sokoban SOKOBAN_FILES)
collect_files(${CMAKE_SOURCE_DIR}/levels LEVEL_FILES)

# Copy sokoban assets only if they change
add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/sokoban
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/sokoban ${CMAKE_BINARY_DIR}/sokoban
        DEPENDS ${SOKOBAN_FILES}
        COMMENT "Copying sokoban assets..."
)

# Copy level files only if they change
add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/levels
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/levels ${CMAKE_BINARY_DIR}/levels
        DEPENDS ${LEVEL_FILES}
        COMMENT "Copying level files..."
)

# Ensure that the asset copying is always checked before the executable builds
add_custom_target(copy_assets DEPENDS ${CMAKE_BINARY_DIR}/sokoban ${CMAKE_BINARY_DIR}/levels)
add_dependencies(boxman copy_assets)
