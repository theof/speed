#include "speed.h"

Player *new_player() {
  Player *player = (Player *)malloc(sizeof(Player));

  player->position = new_vector_2d(0, 0);
  player->speed = new_vector_2d(0, 0);
  player->casting = false;
  player->cast_delta = 0.0;
  return player;
}

void destroy_player(Player *player) {
  destroy_vector_2d(player->position);
  destroy_vector_2d(player->speed);
  free(player);
}