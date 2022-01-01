#include "speed.h"

Rectangle *new_rectangle(float x1, float y1, float x2, float y2) {
  Rectangle *new_rectangle = (Rectangle *)malloc(sizeof(Rectangle));

  new_rectangle->top_left = new_vector_2d(x1, y1);
  new_rectangle->bottom_right = new_vector_2d(x2, y2);
  return new_rectangle;
}

Rectangle *new_empty_rectangle() { return new_rectangle(0.0, 0.0, 0.0, 0.0); }
Rectangle *clone_rectangle(Rectangle *source) {
  return new_rectangle(source->top_left->x, source->top_left->y,
                       source->bottom_right->x, source->bottom_right->y);
}

void destroy_rectangle(Rectangle *rectangle) {
  destroy_vector_2d(rectangle->top_left);
  destroy_vector_2d(rectangle->bottom_right);
  free(rectangle);
}

// w is mapped to x
// h is mapped to y
Vector_2d get_wh_from_rectangle(Rectangle *rectangle) {
  Vector_2d point;

  point.x = roundf(rectangle->bottom_right->x - rectangle->top_left->x);
  point.y = roundf(rectangle->bottom_right->y - rectangle->top_left->y);
  return point;
}

void set_rectangle_position(Rectangle *rectangle, Vector_2d *desired_position) {
  Vector_2d wh = get_wh_from_rectangle(rectangle);

  rectangle->top_left->x = desired_position->x;
  rectangle->top_left->y = desired_position->y;
  rectangle->bottom_right->x = desired_position->x + wh.x;
  rectangle->bottom_right->y = desired_position->y + wh.y;
}

bool check_rectangle_collision(Rectangle *a, Rectangle *b) {
  return !(a->bottom_right->x < b->top_left->x ||
           a->top_left->x > b->bottom_right->x ||
           a->bottom_right->y < b->top_left->y ||
           a->top_left->y > b->bottom_right->y);
}