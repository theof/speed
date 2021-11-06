#pragma once
#include "SDL_stdinc.h"
#define SPEED 42

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>

/*
 * A simple utility type that contains two point
 * Could be expanded to have dot product functions and more
 */
typedef struct S_Vector_2d {
  float x;
  float y;
} Vector_2d;
Vector_2d *new_vector_2d(float x, float y);
void destroy_vector_2d(Vector_2d *vector);

/*
 * physical_input.c
 * abstraction layer to read human inputs
 */
typedef struct S_Input {
  Vector_2d direction; // all values should be normalized between -1.0 and 1.0
  bool action;
  SDL_GameController *controller;
} Input;
Input *new_input();
void destroy_input(Input *input);
void update_input(Input *input, SDL_Event *event);
void detect_controlers(Input *input, SDL_Event *event);
void try_and_find_controller(Input *input);

/*
 * Player.c
 */
typedef struct S_Player {
  Vector_2d position;
  Vector_2d speed;
  bool casting;
  float cast_delta;
  float cast_speed_mod;
} Player;
typedef enum E_Direction {
  BOTTOM,
  TOP,
  LEFT,
  RIGHT,
  NEUTRAL,
} Direction;
Player *new_player();
void destroy_player(Player *player);
void draw_player(Player *player, SDL_Surface *surface, Input *input);
void update_player(Player *player, Uint32 millis_elapsed, Input *input);

typedef struct S_Point {
  int x;
  int y;
} Point;

typedef struct S_Rectangle {
  Point top_left;
  Point bottom_right;
} Rectangle;

typedef struct S_Wall {
  Rectangle position;
} Wall;

typedef struct S_Start {
  Point position;
} Start;

typedef struct S_End {
  Point position;
} End;

typedef struct S_Lever {
  Point position;
  bool activated;

} Lever;

typedef struct S_Level {
  int wall_count;
  Wall **walls;
  int lever_count;
  Lever **levers;
  Start *start;
  End *end;
} Level;

void parse_level(char *filename);
