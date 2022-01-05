#include "speed.h"

void draw(State *s) {
  SDL_SetRenderDrawColor(s->renderer, 0xFF, 0xFF, 0xFF, 255);
  SDL_RenderClear(s->renderer);

  draw_player(s->player, s->renderer, s->input);
  draw_level(s->level, s->renderer);

  SDL_RenderPresent(s->renderer);
}
