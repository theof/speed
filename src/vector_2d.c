#include "speed.h"

Vector_2d *new_vector_2d(float x, float y) {
  Vector_2d *vector_2d = (Vector_2d *)malloc(sizeof(Vector_2d));

  vector_2d->x = x;
  vector_2d->y = y;
  return vector_2d;
}

void destroy_vector_2d(Vector_2d *vector) { free(vector); }

Vector_2d add_vector_2ds(Vector_2d const *v1, Vector_2d const *v2) {
  Vector_2d result;

  result.x = v1->x + v2->x;
  result.y = v1->y + v2->y;
  return result;
}