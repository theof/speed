#include "speed.h"

Vector_2d *new_vector_2d(float x, float y) {
  Vector_2d *vector = (Vector_2d *)malloc(sizeof(Vector_2d));

  vector->x = x;
  vector->y = y;
  return vector;
}
