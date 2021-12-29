#include "speed.h"

// Link the target rectangle to a rigidbody, this rectangle won't be freed when
// the rigidbody is destroyed
Rigidbody *new_rigidbody(Rectangle *target_rectangle, float weight,
                         bool can_move) {
  Rigidbody *rigidbody = (Rigidbody *)malloc(sizeof(Rigidbody));

  rigidbody->acceleration = new_vector_2d(0.0, 0.0);
  rigidbody->speed = new_vector_2d(0.0, 0.0);
  rigidbody->weight = weight;
  rigidbody->can_move = can_move;
  rigidbody->definition = target_rectangle;
  return rigidbody;
}

// The rigidbody->definition member won't be freed here, since we just link it
// in the construtor
void destroy_rigidbody(Rigidbody *rigidbody) {
  destroy_vector_2d(rigidbody->acceleration);
  destroy_vector_2d(rigidbody->speed);
  free(rigidbody);
}

bool rigidbodies_intersects(Rigidbody *r1, Rigidbody *r2) {
  Rectangle *a = r1->definition;
  Rectangle *b = r2->definition;

  if (a->bottom_right->x < b->top_left->x ||
      a->top_left->x > b->bottom_right->x)
    return false;
  if (a->bottom_right->y < b->top_left->y ||
      a->top_left->y > b->bottom_right->y)
    return false;
  return true;
}

float compute_depth_from_length_and_maxes(float a_length, float b_length,
                                          float a_max, float b_max) {
  float depth = b_length - (b_max - a_max);

  if (depth >= a_length)
    return depth;
  else
    return depth - a_length;
}

Vector_2d get_rigibdoby_intersection_normal(Rigidbody *r1, Rigidbody *r2) {
  Vector_2d normal;
  Rectangle *a = r1->definition;
  Rectangle *b = r2->definition;
  Vector_2d ahw = get_hw_from_rectangle(a);
  Vector_2d bhw = get_hw_from_rectangle(b);
  float depth_x = compute_depth_from_length_and_maxes(
      ahw.y, bhw.y, a->bottom_right->x, b->bottom_right->x);
  float depth_y = compute_depth_from_length_and_maxes(
      ahw.x, bhw.x, a->bottom_right->y, b->bottom_right->y);

  // printf("depth x %f depth y %f\n", depth_x, depth_y);
  if (abs(depth_x) < abs(depth_y)) {
    normal.x = depth_x > 0 ? 1.0 : -1.0;
    normal.y = 0.0;
  } else {
    normal.x = 0.0;
    normal.y = depth_y > 0 ? 1.0 : -1.0;
  }
  return normal;
}