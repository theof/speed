#pragma once
#include "SDL_stdinc.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct S_EngineTimers {
  Uint32 last_frame_ts;
  Uint32 new_frame_ts;
  Uint32 millis_elapsed;
} EngineTimers;
EngineTimers *new_engine_timers();
void destroy_engine_timers(EngineTimers *engine_timers);

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
 * Representation of a rectangle and a bunch of utility around it
 */
typedef struct S_Rectangle {
  Vector_2d *top_left;
  Vector_2d *bottom_right;
} Rectangle;
Rectangle *new_rectangle(float x1, float y1, float x2, float y2);
Rectangle *new_empty_rectangle();
void destroy_rectangle(Rectangle *rectangle);
Vector_2d get_hw_from_rectangle(Rectangle *rectangle);

/*
 * level entities
 */
typedef struct S_Wall {
  Rectangle *definition;
} Wall;

typedef struct S_Start {
  Vector_2d *position;
} Start;

typedef struct S_End {
  Vector_2d *position;
} End;

typedef struct S_Lever {
  Vector_2d *position;
  bool activated;
} Lever;

/*
 * Representation of a single instance Level
 * level.c
 */
typedef struct S_Level {
  int wall_count;
  Wall **walls;
  int lever_count;
  Lever **levers;
  Start *start;
  End *end;
} Level;
void destroy_level(Level *level);
Level *new_level();
void draw_level(Level *level, SDL_Surface *surface);

/*
 * level parser.c
 */
Level *parse_level(char *filename);

// level/entities/wall.c
Wall *new_wall(char *line);
void add_wall(Wall *wall, Level *level);
void destroy_wall(Wall *wall);

// level/entities/start.c
Start *new_start(char *line);
void add_start(Start *start, Level *level);
void destroy_start(Start *start);

// level/entities/end.c
End *new_end(char *line);
void add_end(End *end, Level *level);
void destroy_end(End *end);

// level/entities/lever.c
Lever *new_lever(char *line);
void add_lever(Lever *lever, Level *level);
void destroy_lever(Lever *lever);

typedef struct S_Rigidbody {
  Rectangle *definition;
  float weight;
  Vector_2d *acceleration;
  Vector_2d *speed;
} Rigidbody;
Rigidbody *new_rigidbody(Rectangle *target_rectangle, float weight);
void destroy_rigidbody(Rigidbody *target);

typedef struct S_Rigidbody_List {
  Rigidbody *rigid_body;
  struct S_Rigidbody_List *next;
  struct S_Rigidbody_List *prev;
} Rigidbody_List;
Rigidbody_List *new_rigidbody_list();
Rigidbody_List *add_member_to_end_of_list(Rigidbody_List *start,
                                          Rectangle *target_rectangle,
                                          float weight);
Rigidbody_List *add_member_to_start_of_list(Rigidbody_List *start,
                                            Rectangle *target_rectangle,
                                            float weight);
void remove_member_from_list(Rigidbody_List *target_member);
void destroy_rigidbody_list(Rigidbody_List *start);

/*
 * Player.c
 */
typedef struct S_Player {
  Rectangle *definition;
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

typedef struct S_State {
  Level *level;
  Input *input;
  SDL_Window *window;
  SDL_Surface *surface;
  Player *player;
  EngineTimers *engine_timers;
} State;
State *init_state();
void destroy_state(State *state);