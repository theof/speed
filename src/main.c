// SDL2 Hello, World!
// This should display a white screen for 2 seconds
// compile with: clang++ main.cpp -o hello_sdl2 -lSDL2
// run with: ./hello_sdl2
#include "SDL_stdinc.h"
#include "SDL_timer.h"
#include "SDL_video.h"
#include "speed.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#define SCREEN_WIDTH 640

#define SCREEN_HEIGHT 480

void draw(SDL_Window *window, SDL_Surface *screenSurface, Player *player) {
  SDL_FillRect(screenSurface, NULL,
               SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
  draw_player(player, screenSurface);
  SDL_UpdateWindowSurface(window);
}

void handle_event(SDL_Event *ev, bool *game_is_still_running, Input *input) {
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

int main(int argc, char *args[]) {

  parse_level("hellow.csv");

  SDL_Window *window = NULL;
  SDL_Surface *screenSurface = NULL;
  Player *player = new_player();

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
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

  Uint32 last_frame_ts = SDL_GetTicks();
  Uint32 new_frame_ts;
  Uint32 millis_elapsed;
  bool game_is_still_running = true;
  Input *input = new_input();
  while (game_is_still_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) { // poll until all events are handled!
      handle_event(&event, &game_is_still_running, input);
    }

    // update game state, draw the current frame
    new_frame_ts = SDL_GetTicks();
    millis_elapsed = new_frame_ts - last_frame_ts; // XXX might overflow
    printf("%d\n", millis_elapsed);
    update_player(player, millis_elapsed, input);
    draw(window, screenSurface, player);
    last_frame_ts = new_frame_ts;
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
