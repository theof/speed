#include "speed.h"

#define GRAVITY 0.05f

void apply_gravity(Rigidbody_List *rigidbody_list) {
  Rigidbody *rigidbody = rigidbody_list->rigidbody;

  if (rigidbody->weight != 0.0f && rigidbody->can_move &&
      rigidbody->collide_direction != COLLIDE_BOTTOM) {
    rigidbody->speed.y += GRAVITY;
  }
}