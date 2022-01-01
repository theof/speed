#include "speed.h"

float resolve_colision(Rigidbody *r_a, Rigidbody *r_b) {
  Rectangle *a = r_a->definition;
  Rectangle *b = r_b->definition;
  float xInvEntry, yInvEntry;
  float xInvExit, yInvExit;
  Vector_2d a_wh = get_wh_from_rectangle(a);
  Vector_2d b_wh = get_wh_from_rectangle(b);

  // find the distance between the objects on the near and far sides

  // for x
  if (r_a->speed->x > 0.0f) {
    // xInvEntry = b2.x - (b1.x + b1.w);
    xInvEntry = (b->top_left->x) - (a->top_left->x + a_wh.x);
    // xInvExit = (b2.x + b2.w) - b1.x;
    xInvExit = (b->top_left->x + b_wh.x) - a->top_left->x;
  } else {
    // xInvEntry = (b2.x + b2.w) - b1.x;
    xInvEntry = (b->top_left->x + b_wh.x) - a->top_left->x;
    // xInvExit = b2.x - (b1.x + b1.w);
    xInvExit = (b->top_left->x) - (a->top_left->x + a_wh.x);
  }

  // for y
  if (r_a->speed->y > 0.0f) {
    // yInvEntry = b2.y - (b1.y + b1.h);
    yInvEntry = b->top_left->y - (a->top_left->y + a_wh.y);
    // yInvExit = (b2.y + b2.h) - b1.y;
    yInvExit = (b->top_left->y + b_wh.y) - a->top_left->y;
  } else {
    // yInvEntry = (b2.y + b2.h) - b1.y;
    yInvEntry = (b->top_left->y + b_wh.y) - a->top_left->y;
    // yInvExit = b2.y - (b1.y + b1.h);
    yInvExit = b->top_left->y - (a->top_left->y + a_wh.y);
  }

  float xEntry, yEntry;
  float xExit, yExit;

  if (r_a->speed->x == 0.0f) {
    xEntry = -INFINITY;
    xExit = INFINITY;
  } else {
    xEntry = xInvEntry / r_a->speed->x;
    xExit = xInvExit / r_a->speed->x;
  }

  if (r_a->speed->y == 0.0f) {
    yEntry = -INFINITY;
    yExit = INFINITY;
  } else {
    yEntry = yInvEntry / r_a->speed->y;
    yExit = yInvExit / r_a->speed->y;
  }

  float entryTime = fmax(xEntry, yEntry);
  float exitTime = fmin(xExit, yExit);
  Vector_2d normal;

  printf("entryTime %f exitTime %f\n", entryTime, exitTime);
  if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f ||
      yEntry > 1.0f) {
    // No collision
    normal.x = 0.0f;
    normal.y = 0.0f;
    return 1.0f;
  }

  else {
    if (xEntry < yEntry) {
      if (xInvEntry < 0.0f) {
        normal.x = 1.0f;
        normal.y = 0.0f;
      } else {
        normal.x = -1.0f;
        normal.y = 0.0f;
      }
    } else {
      if (yInvEntry < 0.0f) {
        normal.x = 0.0f;
        normal.y = 1.0f;
      } else {
        normal.x = 0.0f;
        normal.y = -1.0f;
      }
    }
    return entryTime;
  }
}

void compute_rigid_body_list_tick(State *s) {
  if (s->rigidbody_list != NULL) {
    Rigidbody_List *current = s->rigidbody_list;
    Rigidbody_List *pt = s->rigidbody_list->next;

    // resolve colisions
    while (pt != NULL) {
      if (current->rigidbody->can_move) {
        float coef = resolve_colision(current->rigidbody, pt->rigidbody);

        current->rigidbody->speed->x *= coef;
        current->rigidbody->speed->y *= coef;
      } else {
        current = pt;
      }
      pt = pt->next;
      if (pt == NULL && current->next != NULL) {
        current = current->next;
        pt = current->next;
      }
    }
    current = s->rigidbody_list;

    // Apply speed vectors
    while (current != NULL) {
      if (current->rigidbody->can_move)
        rigidbody_update_definitions_from_speed(current->rigidbody);
      current = current->next;
    }
  }
}