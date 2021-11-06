#pragma once
#define SPEED 42

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
} Player;
Player *new_player();
void destroy_player(Player *player);