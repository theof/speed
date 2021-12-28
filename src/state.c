#include "speed.h"

// Initializes a fresh state with neutral values
State *new_state() {
  State *s = (State*)malloc(sizeof(State));

  s->input=NULL;
  s->level=NULL;
  s->player=NULL;
  s->surface=NULL;
  s->engine_timers=NULL;
  s->window=NULL;
  return s;
}

void destroy_state(State* s) {
  if (s->input != NULL)
    destroy_input(s->input);
  if (s->level != NULL)
    destroy_level(s->level);
  if (s->player != NULL)
    destroy_player(s->player);
  if (s->surface != NULL)
    SDL_FreeSurface(s->surface);
  if (s->window != NULL)
    SDL_DestroyWindow(s->window);
  if (s->engine_timers != NULL)
    destroy_engine_timers(s->engine_timers);
  free(s);
  SDL_Quit();
}

void gracefully_abort_s_creation_and_exit(State* s, int errcode) {
  destroy_state(s);
  exit(errcode);
}

void init_SDL_systems(State *s) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    gracefully_abort_s_creation_and_exit(s, 1);
  }
  if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0) {
    fprintf(stderr, "could not initialize sdl2 gamepad submodule: %s\n",
            SDL_GetError());
    gracefully_abort_s_creation_and_exit(s, 1);
  }
}

SDL_Window* new_SDL_window(State *s) {
  SDL_Window *window = SDL_CreateWindow("hello_sdl2", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    gracefully_abort_s_creation_and_exit(s, 1);
  }                         
  return window;
}

SDL_Surface* new_SDL_surface(State *s) {
  SDL_Surface *surface = SDL_GetWindowSurface(s->window);

  if (surface == NULL) {
    fprintf(stderr, "could not create windows surface: %s\n", SDL_GetError());
    gracefully_abort_s_creation_and_exit(s, 1);
  }
  return surface;
}

State *init_state() {
  State *s = new_state();

  init_SDL_systems(s);
  s->window = new_SDL_window(s);
  s->surface = new_SDL_surface(s);
  s->level = parse_level("hellow.csv");
  s->player = new_player();
  s->input = new_input();
  s->engine_timers = new_engine_timers();
  return s;
}