#include "speed.h"

Player *new_player() {
  Player *player = (Player *)malloc(sizeof(Player));

  player->position.x = 0.0;
  player->position.y = 0.0;
  player->speed.x = 0.0;
  player->speed.y = 0.0;
  player->casting = false;
  player->cast_delta = 0.0;
  player->cast_speed_mod = 0.1;
  return player;
}

void destroy_player(Player *player) { free(player); }

void start_to_cast(Player *player) { player->casting = true; }

void _apply_cast(Direction direction) {
  switch (direction) {
  case BOTTOM: {
    printf("Bottom Cast");
    break;
  }
  case TOP: {
    printf("Top Cast");
    break;
  }
  case LEFT: {
    printf("Left Cast");
    break;
  }
  case RIGHT: {
    printf("Right Cast");
    break;
  }
  case NEUTRAL: {
    printf("Neutral Cast");
    break;
  }
  }
}

// https://wiki.libsdl.org/SDL_JoystickGetAxis
// A signed integer (-32768 to 32767) representing the current position of the
// axis.
void end_cast(Sint16 x_move, Sint16 y_move, Player *player) {
  float power_level = player->cast_delta;

  player->casting = false;
  // Has a casting direction
  if (x_move || y_move) {
    if (x_move > 0 && abs(y_move) < x_move / 2)
      return _apply_cast(RIGHT);
    if (x_move < 0 && y_move < (-x_move / 2))
      return _apply_cast(LEFT);
    if (y_move > 0 && abs(x_move) < y_move / 2)
      return _apply_cast(TOP);
    if (y_move < 0 && x_move < (-y_move / 2))
      return _apply_cast(BOTTOM);
  } else
    return _apply_cast(NEUTRAL);
}