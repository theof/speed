#include "speed.h"

void draw_level(Level *level, SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0x25, 0x00, 0x35, 0xFF);
  for (int index = 0; index < level->wall_count; index++) {
    Wall *wall = level->walls[index];
    SDL_Rect rect;
    Vector_2d wh = get_wh_from_rectangle(wall->definition);

    rect.w = wh.x;
    rect.h = wh.y;
    rect.x = wall->definition->top_left->x;
    rect.y = wall->definition->top_left->y;
    SDL_RenderFillRect(renderer, &rect);
  }
}

void destroy_level(Level *level) {
  int i;

  for (i = 0; i < level->wall_count; i += 1) {
    destroy_wall(level->walls[i]);
  }
  free(level->walls);
  for (i = 0; i < level->lever_count; i += 1) {
    destroy_lever(level->levers[i]);
  }
  free(level->levers);
  destroy_start(level->start);
  destroy_end(level->end);
  free(level);
}

Level *new_level() {
  Level *level = malloc(sizeof(Level));

  level->end = NULL;
  level->start = NULL;
  level->walls = NULL;
  level->levers = NULL;
  level->wall_count = 0;
  level->lever_count = 0;
  return level;
}
