cmake_minimum_required(VERSION 3.7)

project(speed)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(speed src/main.c)
target_link_libraries(speed ${SDL2_LIBRARIES})
