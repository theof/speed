#include "SDL_stdinc.h"
#include "SDL_timer.h"
#include "SDL_video.h"
#include "speed.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#define SCREEN_WIDTH 640

#define SCREEN_HEIGHT 480

void draw(SDL_Window *window, SDL_Surface *screenSurface, Player *player,
          Input *input, Level *level) {
  SDL_FillRect(screenSurface, NULL,
               SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
  draw_player(player, screenSurface, input);
  draw_level(level, screenSurface);
  SDL_UpdateWindowSurface(window);
}

void handle_event(SDL_Event *ev, bool *game_is_still_running, Input *input) {
  detect_controlers(input, ev);
  switch (ev->type) {
  case SDL_WINDOWEVENT:
    switch (ev->window.event) {
    case SDL_WINDOWEVENT_CLOSE:
      printf("window destroyed\n");
      *game_is_still_running = false;
      break;
    }
    break;
  case SDL_KEYUP:
    if (ev->key.keysym.sym == SDLK_ESCAPE) {
      printf("escape\n");
      *game_is_still_running = false;
    }
    break;
  }
  update_input(input, ev);
}

void loop(SDL_Window *window, SDL_Surface *surface, Level *level) {
  Player *player = new_player();
  Uint32 last_frame_ts = SDL_GetTicks();
  Uint32 new_frame_ts;
  Uint32 millis_elapsed;
  bool game_is_still_running = true;
  Input *input = new_input();
  try_and_find_controller(input);
  while (game_is_still_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) { // poll until all events are handled!
      handle_event(&event, &game_is_still_running, input);
    }

    // update game state, draw the current frame
    new_frame_ts = SDL_GetTicks();
    millis_elapsed = new_frame_ts - last_frame_ts; // XXX might overflow
    update_player(player, millis_elapsed, input);
    draw(window, surface, player, input, level);
    last_frame_ts = new_frame_ts;
    SDL_Delay(10);
  }
  destroy_input(input);
  destroy_player(player);
}

int main(int argc, char *args[]) {
  Level *level = parse_level("hellow.csv");
  SDL_Window *window = NULL;
  SDL_Surface *screenSurface = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    return 1;
  }
  if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0) {
    fprintf(stderr, "could not initialize sdl2 gamepad submodule: %s\n",
            SDL_GetError());
    return 1;
  }
  window = SDL_CreateWindow("hello_sdl2", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    return 1;
  }
  screenSurface = SDL_GetWindowSurface(window);

  loop(window, screenSurface, level);

  destroy_level(level);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
