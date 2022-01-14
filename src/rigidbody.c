#include "speed.h"

#define COLLISION_RECTANGLE_AMOUNT 4
// 5 px ray casting
#define COLLISION_RECTANGLE_STREGH 5.0f;

// Link the target rectangle to a rigidbody, this rectangle won't be freed when
// the rigidbody is destroyed
Rigidbody *new_rigidbody(Rectangle *target_rectangle) {
  Rigidbody *rigidbody = (Rigidbody *)malloc(sizeof(Rigidbody));

  rigidbody->speed = (Vector_2d){0., 0.};
  rigidbody->energy_retain = 0.0f;
  rigidbody->weight = 0.0f;
  rigidbody->can_move = false;
  rigidbody->definition = target_rectangle;
  rigidbody->update_collision_direction = false;
  rigidbody->collision_direction = (Collision_Direction){0};
  rigidbody->collision_side_rectangles = NULL;
  return rigidbody;
}

// The rigidbody->definition member won't be freed here, since we just link it
// in the construtor
void destroy_rigidbody(Rigidbody *rigidbody) {
  if (rigidbody->collision_side_rectangles != NULL) {
    for (int i = 0; i < COLLISION_RECTANGLE_AMOUNT; i++)
      free(rigidbody->collision_side_rectangles[i]);
    free(rigidbody->collision_side_rectangles);
  }
  free(rigidbody);
}

void rigid_body_update_collision_rectangle_from_definition(
    Rigidbody *rigidbody) {
  if (rigidbody->collision_side_rectangles != NULL) {
    Rectangle *target = rigidbody->collision_side_rectangles[0];
    // Define top
    target->top_left = rigidbody->definition->top_left;
    target->bottom_right = rigidbody->definition->bottom_right;
    target->top_left.y -= COLLISION_RECTANGLE_STREGH;
    target->bottom_right.y -= COLLISION_RECTANGLE_STREGH;

    target = rigidbody->collision_side_rectangles[1];
    // Define right
    target->top_left = rigidbody->definition->top_left;
    target->bottom_right = rigidbody->definition->bottom_right;
    target->top_left.x += COLLISION_RECTANGLE_STREGH;
    target->bottom_right.x += COLLISION_RECTANGLE_STREGH;

    target = rigidbody->collision_side_rectangles[2];
    // Define bottom
    target->top_left = rigidbody->definition->top_left;
    target->bottom_right = rigidbody->definition->bottom_right;
    target->top_left.y += COLLISION_RECTANGLE_STREGH;
    target->bottom_right.y += COLLISION_RECTANGLE_STREGH;

    target = rigidbody->collision_side_rectangles[3];
    // Define left
    target->top_left = rigidbody->definition->top_left;
    target->bottom_right = rigidbody->definition->bottom_right;
    target->top_left.x -= COLLISION_RECTANGLE_STREGH;
    target->bottom_right.x -= COLLISION_RECTANGLE_STREGH;
  }
}

void rigidbody_update_definitions_from_speed(Rigidbody *rigidbody) {
  Vector_2d desired_position =
      add_vector_2d(rigidbody->definition->top_left, rigidbody->speed);

  set_rectangle_position(rigidbody->definition, desired_position);
  rigid_body_update_collision_rectangle_from_definition(rigidbody);
}

void set_border_collision_computing(bool value, Rigidbody *rigidbody) {
  if (value) {
    if (rigidbody->collision_side_rectangles == NULL) {
      rigidbody->collision_side_rectangles = (Rectangle **)malloc(
          sizeof(Rectangle *) * COLLISION_RECTANGLE_AMOUNT);
      for (int i = 0; i < COLLISION_RECTANGLE_AMOUNT; i++)
        rigidbody->collision_side_rectangles[i] = new_rectangle(0, 0, 0, 0);
      rigidbody->update_collision_direction = true;
    }
  } else {
    rigidbody->update_collision_direction = false;
    rigidbody->collision_direction = (Collision_Direction){0};
  }
}