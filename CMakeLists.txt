cmake_minimum_required(VERSION 3.16)
project(FatFlappyDragon C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)

# ----------------------
# Project Sources
# ----------------------
# Collect all C source files in sources/ directory
file(GLOB_RECURSE PROJECT_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/sources/*.c"
)

# Include directory
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/sources/")

# ----------------------
# Executable
# ----------------------
add_executable(${PROJECT_NAME} src/main.c)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# ----------------------
# Assets Path
# ----------------------
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")

# Copy assets to the build directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/src/assets"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)
