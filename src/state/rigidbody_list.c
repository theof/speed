#include "speed.h"

void compute_rigid_body_list_tick(State *s) {
  if (s->rigidbody_list != NULL) {
    Rigidbody_List *current = s->rigidbody_list;
    Rigidbody_List *pt = s->rigidbody_list->next;

    while (pt != NULL) {
      if (current->rigidbody->can_move) {
        if (rigidbodies_intersects(current->rigidbody, pt->rigidbody)) {
          Vector_2d normal = get_rigibdoby_intersection_normal(
              current->rigidbody, pt->rigidbody);

          if (normal.x == 1.0) // RIGHT
          {
            printf("A is RIGHT of B\n");
          } else if (normal.x == -1.0) // LEFT
          {
            printf("A is LEFT of B\n");
          } else if (normal.y == 1.0) // BOT
          {
            printf("A is BOT of B\n");
          } else if (normal.y == -1.0) // TOP
          {
            printf("A is TOP of B\n");
          }
        }
      } else {
        current = pt;
      }
      pt = pt->next;
      if (pt == NULL && current->next != NULL) {
        current = current->next;
        pt = current->next;
      }
    }
  }
}
