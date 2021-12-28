#include "speed.h"

void draw_level(Level *level, SDL_Surface *surface) {

  for (int index = 0;index < level->wall_count; index ++)
  {
    Wall *wall = level->walls[index];
    SDL_Rect sdl_rectangle;
    Point hw = get_hw_from_rectangle(&wall->position);

    sdl_rectangle.h = hw.x;
    sdl_rectangle.w = hw.y;
    sdl_rectangle.x = wall->position.top_left.x;
    sdl_rectangle.y = wall->position.top_left.y;
    SDL_FillRect(surface, &sdl_rectangle, SDL_MapRGB(surface->format, 0x25, 0x00, 0x35));
  }
}