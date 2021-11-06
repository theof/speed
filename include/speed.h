#pragma once
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
 * Player controler
 */
typedef struct S_Player {
  Vector_2d *position;
  Vector_2d *speed;
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







typedef struct S_Point {
	int		x;
	int		y;
} Point;


typedef struct S_Rectangle {
	Point		top_left;
	Point		bottom_right;
} Rectangle;


typedef struct S_Wall {
	Rectangle	position;
} Wall;

typedef struct S_Start {
	Point		position;
} Start;

typedef struct S_End {
	Point		position;
} End;

typedef struct S_Lever {
	Point		position;
} Lever;

typedef struct S_Level {
	int			wall_count;
	Wall**		walls;
	int			lever_count;
	Lever**		levels;
	Start		start;
	End			end;
} Level;

void parse_level(char* filename);

