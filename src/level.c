#include "speed.h"

void draw_level(Level *level, SDL_Surface *surface) {
  int index = 0;

  while (index < level->wall_count)
  {
    Wall *wall = level->walls[index];
    SDL_Rect sdl_rectangle;
    Point hw = get_hw_from_rectangle(&wall->position);

    sdl_rectangle.h = hw.x;
    sdl_rectangle.w = hw.y;
    sdl_rectangle.x = wall->position.top_left.x;
    sdl_rectangle.y = wall->position.top_left.y;
    SDL_FillRect(surface, &sdl_rectangle, SDL_MapRGB(surface->format, 0x25, 0x00, 0x35));
    index++;
  }
}