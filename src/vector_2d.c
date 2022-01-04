#include "speed.h"

Vector_2d *new_vector_2d(float x, float y) {
  Vector_2d *vector_2d = (Vector_2d *)malloc(sizeof(Vector_2d));

  vector_2d->x = x;
  vector_2d->y = y;
  return vector_2d;
}

Vector_2d add_vector_2d(const Vector_2d destination,
                        const Vector_2d source) {
  Vector_2d result;

  result.x = destination.x + source.x;
  result.y = destination.y + source.y;
  return result;
}

Vector_2d scale_vector(const Vector_2d vector, float scale_factor) {
  Vector_2d result;

  result.x = vector.x * scale_factor;
  result.y = vector.y * scale_factor;
  return result;
}