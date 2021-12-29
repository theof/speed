#include "SDL_rect.h"
#include "SDL_surface.h"
#include "speed.h"

#define PLAYER_SIDE 25.0

Player *new_player() {
  Player *player = (Player *)malloc(sizeof(Player));

  player->definition = new_rectangle(0.0, 0.0, PLAYER_SIDE, PLAYER_SIDE);
  return player;
}

void destroy_player(Player *player) {
  destroy_rectangle(player->definition);
  free(player);
}

void draw_player(Player *player, SDL_Surface *surface, Input *input) {
  SDL_Rect rect;
  Vector_2d hw = get_hw_from_rectangle(player->definition);

  rect.h = hw.x;
  rect.w = hw.y;
  rect.x = player->definition->top_left->x;
  rect.y = player->definition->top_left->y;

  SDL_FillRect(
      surface, &rect,
      SDL_MapRGB(surface->format, 0xFF, 0x00, input->action ? 0xFF : 0x00));
}

void update_player(Player *player, Uint32 delta_millis, Input *input) {
  Vector_2d desired_position;

  desired_position.x = player->definition->top_left->x +
                       (0.3 * input->direction.x * delta_millis);
  desired_position.y = player->definition->top_left->y +
                       (0.3 * input->direction.y * delta_millis);
  set_rectangle_position(player->definition, &desired_position);
}

// void _apply_cast(Direction direction) {
//   switch (direction) {
//   case BOTTOM: {
//     printf("Bottom Cast");
//     break;
//   }
//   case TOP: {
//     printf("Top Cast");
//     break;
//   }
//   case LEFT: {
//     printf("Left Cast");
//     break;
//   }
//   case RIGHT: {
//     printf("Right Cast");
//     break;
//   }
//   case NEUTRAL: {
//     printf("Neutral Cast");
//     break;
//   }
//   }
// }

// https://wiki.libsdl.org/SDL_JoystickGetAxis
// A signed integer (-32768 to 32767) representing the current position of the
// axis.
// void end_cast(Sint16 x_move, Sint16 y_move, Player *player) {
//   float power_level = player->cast_delta;

//   player->casting = false;
//   // Has a casting direction
//   if (x_move || y_move) {
//     if (x_move > 0 && abs(y_move) < x_move / 2)
//       return _apply_cast(RIGHT);
//     if (x_move < 0 && y_move < (-x_move / 2))
//       return _apply_cast(LEFT);
//     if (y_move > 0 && abs(x_move) < y_move / 2)
//       return _apply_cast(TOP);
//     if (y_move < 0 && x_move < (-y_move / 2))
//       return _apply_cast(BOTTOM);
//   } else
//     return _apply_cast(NEUTRAL);
// }
