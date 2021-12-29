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