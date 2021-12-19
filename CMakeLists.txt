cmake_minimum_required(VERSION 3.7)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 23)
set(WARN_CFLAGS -Wall -Wextra -Wpedantic)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

project(speed)

find_package(SDL2 REQUIRED)
set(CMAKE_BUILD_TYPE Debug)
include_directories(${SDL2_INCLUDE_DIRS} include)

add_executable(speed
  src/main.c
	src/vector_2d.c
	src/level_file_parser.c
  src/player.c
  src/input.c
  src/level.c
  src/rectangle.c
  src/collisions.c
)
target_link_libraries(speed ${SDL2_LIBRARIES})
