#include "speed.h"

Vector_2d *new_vector_2d(float x, float y) {
  Vector_2d *vector_2d = (Vector_2d*)malloc(sizeof(Vector_2d));

  vector_2d->x = x;
  vector_2d->y = y;
  return vector_2d;
}

void destroy_vector_2d(Vector_2d* vector) {
  free(vector);
}