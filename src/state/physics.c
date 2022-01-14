#include "speed.h"

void compute_rigid_body_list_tick(State *s) {
  if (s->rigidbody_list != NULL) {
    Rigidbody_List *pointer = s->rigidbody_list;

    reset_all_rigidbody_list_member_collisions(pointer);
    while (pointer != NULL) {
      // Compute new speed
      apply_gravity(pointer);
      resolve_collision_loop(pointer);
      rigidbody_update_definitions_from_speed(pointer->rigidbody);
      pointer = pointer->next;
    }
  }
}