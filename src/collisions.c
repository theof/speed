#include "speed.h"

typedef struct S_Collision_Result {
  Vector_2d normal;
  float entry_time;
} Collision_Result;

Collision_Result swept_AABB(Rigidbody *r_a, Rigidbody *r_b) {
  Rectangle *a = r_a->definition;
  Rectangle *b = r_b->definition;
  float x_inv_entry, y_inv_entry;
  float x_inv_exit, y_inv_exit;
  Vector_2d a_wh = get_wh_from_rectangle(a);
  Vector_2d b_wh = get_wh_from_rectangle(b);

  // find the distance between the objects on the near and far sides

  // for x
  if (r_a->speed.x > 0.0f) {
    x_inv_entry = (b->top_left.x) - (a->top_left.x + a_wh.x);
    x_inv_exit = (b->top_left.x + b_wh.x) - a->top_left.x;
  } else {
    x_inv_entry = (b->top_left.x + b_wh.x) - a->top_left.x;
    x_inv_exit = (b->top_left.x) - (a->top_left.x + a_wh.x);
  }

  // for y
  if (r_a->speed.y > 0.0f) {
    y_inv_entry = b->top_left.y - (a->top_left.y + a_wh.y);
    y_inv_exit = (b->top_left.y + b_wh.y) - a->top_left.y;
  } else {
    y_inv_entry = (b->top_left.y + b_wh.y) - a->top_left.y;
    y_inv_exit = b->top_left.y - (a->top_left.y + a_wh.y);
  }

  float x_entry, y_entry;
  float x_exit, y_exit;

  if (r_a->speed.x == 0.0f) {
    x_entry = -INFINITY;
    x_exit = INFINITY;
  } else {
    x_entry = x_inv_entry / r_a->speed.x;
    x_exit = x_inv_exit / r_a->speed.x;
  }

  if (r_a->speed.y == 0.0f) {
    y_entry = -INFINITY;
    y_exit = INFINITY;
  } else {
    y_entry = y_inv_entry / r_a->speed.y;
    y_exit = y_inv_exit / r_a->speed.y;
  }

  float entry_time = fmax(x_entry, y_entry);
  float exit_time = fmin(x_exit, y_exit);
  Collision_Result result;

  if (entry_time > exit_time || x_entry < 0.0f && y_entry < 0.0f ||
      x_entry > 1.0f || y_entry > 1.0f) {
    // No collision
    result.normal.x = 0.0f;
    result.normal.y = 0.0f;
    result.entry_time = 1.0f;
    return result;
  }

  else {
    if (x_entry < y_entry) {
      if (x_inv_entry < 0.0f) {
        result.normal.x = 1.0f;
        result.normal.y = 0.0f;
      } else {
        result.normal.x = -1.0f;
        result.normal.y = 0.0f;
      }
    } else {
      if (y_inv_entry < 0.0f) {
        result.normal.x = 0.0f;
        result.normal.y = 1.0f;
      } else {
        result.normal.x = 0.0f;
        result.normal.y = -1.0f;
      }
    }
    result.entry_time = entry_time;
    return result;
  }
}

// Don't forgetti to free rectangle after use
Rectangle get_swept_broadphase_rectangle(Rigidbody *rigidbody) {
  Rectangle b = *rigidbody->definition;
  Rectangle br;

  br.top_left.x =
      rigidbody->speed.x > 0 ? b.top_left.x : b.top_left.x + rigidbody->speed.x;
  br.top_left.y =
      rigidbody->speed.y > 0 ? b.top_left.y : b.top_left.y + rigidbody->speed.y;
  br.bottom_right.x = rigidbody->speed.x > 0
                          ? rigidbody->speed.x + b.bottom_right.x
                          : b.bottom_right.x - rigidbody->speed.x;
  br.bottom_right.y = rigidbody->speed.y > 0
                          ? rigidbody->speed.y + b.bottom_right.y
                          : b.bottom_right.y - rigidbody->speed.y;

  return br;
}

void swept_narrow_phase_evaluations(Rigidbody_List *current,
                                    Rigidbody_List *pt) {
  Collision_Result collision = swept_AABB(current->rigidbody, pt->rigidbody);

  if (collision.entry_time != 1.0f) {
    Vector_2d *speed = &current->rigidbody->speed;
    float magnitude = sqrt((speed->x * speed->x + speed->y * speed->y)) *
                      collision.entry_time;
    float dotprod =
        (speed->x * collision.normal.y + speed->y * collision.normal.x) *
        collision.entry_time;
    speed->x = dotprod * collision.normal.y;
    speed->y = dotprod * collision.normal.x;
  }
}

void resolve_collision(Rigidbody_List *current, Rigidbody_List *pt) {
  Rectangle swept_broadphase_rectangle =
      get_swept_broadphase_rectangle(current->rigidbody);

  if (check_rectangle_collision(&swept_broadphase_rectangle,
                                pt->rigidbody->definition)) {
    swept_narrow_phase_evaluations(current, pt);
  }
}

void resolve_collision_loop(Rigidbody_List *anchor_pointer) {
  if (anchor_pointer->rigidbody->can_move) {
    Rigidbody_List *pt = anchor_pointer->next;

    while (pt != NULL) {
      resolve_collision(anchor_pointer, pt);
      pt = pt->next;
    }
    pt = anchor_pointer->prev;
    while (pt != NULL) {
      resolve_collision(anchor_pointer, pt);
      pt = pt->prev;
    }
  }
}