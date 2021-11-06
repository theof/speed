#include "speed.h"

void destroy_vector_2d(vector_2d *vector) { free(vector); }

S_PLAYER new_player() {
  Player *player = (Player *)malloc(sizeof(Player));

  player->position = new_vector_2d(0, 0);
  player->speed = new_vector_2d(0, 0);
  return player;
}

void destroy_player(S_PLAYER *player) {
  destroy_vector_2d(player.position);
  destroy_vector_2d(player.speed);
  free(player);
}