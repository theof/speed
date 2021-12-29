#include "speed.h"

Rectangle *new_rectangle(float x1, float y1, float x2, float y2) {
  Rectangle *new_rectangle = (Rectangle *)malloc(sizeof(Rectangle));

  new_rectangle->top_left = new_vector_2d(x1, y1);
  new_rectangle->bottom_right = new_vector_2d(x2, y2);
  return new_rectangle;
}

Rectangle *new_empty_rectangle() { return new_rectangle(0.0, 0.0, 0.0, 0.0); }

void destroy_rectangle(Rectangle *rectangle) {
  destroy_vector_2d(rectangle->top_left);
  destroy_vector_2d(rectangle->bottom_right);
  free(rectangle);
}

// h is mapped to x
// w is mapped to y
Vector_2d get_hw_from_rectangle(Rectangle *rectangle) {
  Vector_2d point;

  point.x = rectangle->bottom_right->y - rectangle->top_left->y;
  point.y = rectangle->bottom_right->x - rectangle->top_left->x;
  return point;
}

void set_rectangle_position(Rectangle *rectangle, float x, float y) {
  Vector_2d hw = get_hw_from_rectangle(rectangle);

  rectangle->top_left->x = x;
  rectangle->top_left->y = y;
  rectangle->bottom_right->x = x + hw.x;
  rectangle->bottom_right->y = y + hw.y;
}