#include "SDL_stdinc.h"
#include "SDL_timer.h"
#include "SDL_video.h"
#include "speed.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

void draw(State *s) {
  SDL_FillRect(s->surface, NULL,
               SDL_MapRGB(s->surface->format, 0xFF, 0xFF, 0xFF));
  draw_player(s->player, s->surface, s->input);
  draw_level(s->level, s->surface);
  SDL_UpdateWindowSurface(s->window);
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

void loop(State *s) {
  EngineTimers *engine_timers = s->engine_timers;
  Player *player = s->player;
  Level *level = s->level;
  bool game_is_still_running = true;

  engine_timers->last_frame_ts = SDL_GetTicks();
  try_and_find_controller(s->input);
  if (level->start != NULL) {
    set_rectangle_position(s->player->definition, level->start->position);
  }
  while (game_is_still_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) { // poll until all events are handled!
      handle_event(&event, &game_is_still_running, s->input);
    }

    // update game s, draw the current frame
    engine_timers->new_frame_ts = SDL_GetTicks();
    engine_timers->millis_elapsed =
        engine_timers->new_frame_ts -
        engine_timers->last_frame_ts; // XXX might overflow
    update_player(player, engine_timers->millis_elapsed, s->input);
    compute_rigid_body_list_tick(s);
    draw(s);
    engine_timers->last_frame_ts = engine_timers->new_frame_ts;
    SDL_Delay(10);
  }
}

int main(int argc, char *args[]) {
  State *s = init_state();
  loop(s);
  destroy_state(s);
  return 0;
}
