#include "speed.h"

// Link the target rectangle to a rigidbody, this rectangle won't be freed when
// the rigidbody is destroyed
Rigidbody *new_rigidbody(Rectangle *target_rectangle) {
  Rigidbody *rigidbody = (Rigidbody *)malloc(sizeof(Rigidbody));

  rigidbody->speed = (Vector_2d){0., 0.};
  rigidbody->energy_retain = 0.0f;
  rigidbody->weight = 0.0f;
  rigidbody->can_move = false;
  rigidbody->definition = target_rectangle;
  rigidbody->collide_direction = COLLIDE_NONE;
  return rigidbody;
}

// The rigidbody->definition member won't be freed here, since we just link it
// in the construtor
void destroy_rigidbody(Rigidbody *rigidbody) { free(rigidbody); }

void rigidbody_update_definitions_from_speed(Rigidbody *rigidbody) {
  Vector_2d desired_position =
      add_vector_2d(rigidbody->definition->top_left, rigidbody->speed);

  set_rectangle_position(rigidbody->definition, desired_position);
}