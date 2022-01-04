#include "speed.h"

void compute_rigid_body_list_tick(State *s) {
  if (s->rigidbody_list != NULL) {
    Rigidbody_List *pointer = s->rigidbody_list;

    while (pointer != NULL) {
      // Compute new speed
      resolve_collision_loop(pointer);
      rigidbody_update_definitions_from_speed(pointer->rigidbody);
      pointer = pointer->next;
    }
  }
}