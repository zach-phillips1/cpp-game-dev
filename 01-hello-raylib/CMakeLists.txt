cmake_minimum_required(VERSION 3.20)
project(HelloRaylib)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib"
    GIT_TAG "5.5"
)

FetchContent_MakeAvailable(raylib)

add_executable(HelloRaylib main.cpp)

target_link_libraries(HelloRaylib PRIVATE raylib)