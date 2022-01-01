#include "speed.h"

void draw_level(Level *level, SDL_Surface *surface) {

  for (int index = 0; index < level->wall_count; index++) {
    Wall *wall = level->walls[index];
    SDL_Rect sdl_rectangle;
    Vector_2d wh = get_wh_from_rectangle(wall->definition);

    sdl_rectangle.w = wh.x;
    sdl_rectangle.h = wh.y;
    sdl_rectangle.x = wall->definition->top_left->x;
    sdl_rectangle.y = wall->definition->top_left->y;
    SDL_FillRect(surface, &sdl_rectangle,
                 SDL_MapRGB(surface->format, 0x25, 0x00, 0x35));
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