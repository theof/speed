#include "speed.h"

// Initializes a fresh state with neutral values
State *new_state() {
  State *s = (State *)malloc(sizeof(State));

  s->input = NULL;
  s->level = NULL;
  s->player = NULL;
  s->surface = NULL;
  s->engine_timers = NULL;
  s->window = NULL;
  s->rigidbody_list = NULL;
  return s;
}

void destroy_state(State *s) {
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
  if (s->rigidbody_list != NULL)
    destroy_rigidbody_list(s->rigidbody_list);
  free(s);
  SDL_Quit();
}

void gracefully_abort_s_creation_and_exit(State *s, int errcode) {
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

SDL_Window *new_SDL_window(State *s) {
  SDL_Window *window = SDL_CreateWindow("hello_sdl2", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                        SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    gracefully_abort_s_creation_and_exit(s, 1);
  }
  return window;
}

SDL_Surface *new_SDL_surface(State *s) {
  SDL_Surface *surface = SDL_GetWindowSurface(s->window);

  if (surface == NULL) {
    fprintf(stderr, "could not create windows surface: %s\n", SDL_GetError());
    gracefully_abort_s_creation_and_exit(s, 1);
  }
  return surface;
}

Rigidbody_List *build_rigidbody_list_from_level_walls(State *s) {
  Level *l = s->level;
  Rigidbody_List *rigidbody_list;

  if (l->wall_count == 0)
    return NULL;
  else {
    rigidbody_list = new_rigidbody_list();
    rigidbody_list->rigidbody = new_rigidbody(l->walls[0]->definition);
    for (int i = 1; i < l->wall_count; i++) {
      rigidbody_list =
          add_member_to_start_of_list(rigidbody_list, l->walls[i]->definition);
    }
  }
  return rigidbody_list;
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
  s->rigidbody_list = build_rigidbody_list_from_level_walls(s);
  if (s->rigidbody_list != NULL) {
    s->rigidbody_list =
        add_member_to_start_of_list(s->rigidbody_list, s->player->definition);
    link_rigidbody_to_player(s->player, s->rigidbody_list->rigidbody);
    s->rigidbody_list->rigidbody->can_move = true;
    s->rigidbody_list->rigidbody->weight = 0.5f;
    s->rigidbody_list->rigidbody->energy_retain = 0.5f;
    set_border_collision_computing(true, s->rigidbody_list->rigidbody);
  }
  return s;
}