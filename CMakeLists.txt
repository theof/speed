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
	src/level.c
    src/level/parser.c
      src/level/entities/wall.c
      src/level/entities/lever.c
      src/level/entities/end.c
      src/level/entities/start.c
  src/player.c
  src/input.c
  src/level.c
  src/rectangle.c
  src/engine_timers.c
  src/state.c
    src/state/rigidbody_list.c
  src/rigidbody.c
  src/rigidbody_list.c
  src/draw.c
  src/spritesheets.c
)
target_link_libraries(speed ${SDL2_LIBRARIES} m)
