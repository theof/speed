#pragma once
#define SPEED 42

#include <stdlib.h>

/*
 * A simple utility type that contains two point
 * Could be expanded to have dot product functions and more
 */
typedef struct S_VECTOR_2D {
  x : float;
  y : float;
} Vector_2d;
void destroy_vector_2d(vector_2d *vector);

/*
 * Player controler
 */
typedef struct S_PLAYER {
  struct Vector_2d *position;
  struct Vector_2d *speed;
} Player;
S_PLAYER new_player();
void destroy_player(S_PLAYER *player);