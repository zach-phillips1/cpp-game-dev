cmake_minimum_required(VERSION 3.20)

project(RaylibPort)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib"
    GIT_TAG "5.5"
)

FetchContent_MakeAvailable(raylib)

add_executable(RaylibPort 
    main.cpp
    GameState.cpp
    renderer.cpp)

target_link_libraries(RaylibPort PRIVATE raylib)