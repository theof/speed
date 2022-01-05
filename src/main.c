#include "SDL_stdinc.h"
#include "SDL_timer.h"
#include "SDL_video.h"
#include "speed.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

Rigidbody_List *_debug_setup_additional_rigidbodies(State *s) {
  float object_amount = 3.0f;
  Rigidbody_List *db_object_list = NULL;

  for (float i = 0; i < object_amount; i += 1.0f) {
    float start = 100;
    float end = start + 5.0f;
    Rigidbody_List *new_member = add_member_to_end_of_list(
        s->rigidbody_list, new_rectangle(start, start * i, end, end * i));

    if (db_object_list == NULL) {
      db_object_list = new_member;
    }

    new_member->rigidbody->can_move = true;
    new_member->rigidbody->weight = 0.1f;
  }
  return db_object_list;
}

void _debug_draw_db_objects(State *s, Rigidbody_List *db_objects) {
  Rigidbody_List *pt = db_objects;

  while (pt != NULL) {
    SDL_Rect rect;
    Vector_2d wh = get_wh_from_rectangle(pt->rigidbody->definition);
    rect.w = wh.x;
    rect.h = wh.y;
    rect.x = pt->rigidbody->definition->top_left.x;
    rect.y = pt->rigidbody->definition->top_left.y;
    SDL_FillRect(s->surface, &rect,
                 SDL_MapRGB(s->surface->format, 0xAA, 0xAA, 0xAA));
    pt = pt->next;
  }
}

void draw(State *s, Rigidbody_List *_db_objects) {
  SDL_FillRect(s->surface, NULL,
               SDL_MapRGB(s->surface->format, 0xFF, 0xFF, 0xFF));
  draw_player(s->player, s->surface, s->input);
  draw_level(s->level, s->surface);
  _debug_draw_db_objects(s, _db_objects);
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
  Rigidbody_List *_db_objects = _debug_setup_additional_rigidbodies(s);

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
    _debug_draw_db_objects(s, _db_objects);
    draw(s, _db_objects);
    engine_timers->last_frame_ts = engine_timers->new_frame_ts;
    SDL_Delay(10);
  }
  while (_db_objects != NULL) {
    destroy_rectangle(_db_objects->rigidbody->definition);
    _db_objects = _db_objects->next;
  }
}

int main(int argc, char *args[]) {
  State *s = init_state();
  loop(s);
  destroy_state(s);
  return 0;
}
