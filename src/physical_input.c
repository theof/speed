#include "speed.h"

Input *new_input() {
  Input *input = (Input *)malloc(sizeof(Input));

  input->direction.x = 0.0;
  input->direction.y = 0.0;
  input->action = false;
  return input;
}

void destroy_input(Input *input) { free(input); }

void handle_keydown(SDL_Keycode keycode, Input *input) {
  switch (keycode) {
  case SDLK_LEFT:
    input->direction.x = -1.0;
    break;
  case SDLK_RIGHT:
    input->direction.x = 1.0;
    break;
  case SDLK_UP:
    input->direction.y = -1.0;
    break;
  case SDLK_DOWN:
    input->direction.y = 1.0;
    break;
  case SDLK_SPACE:
    input->action = true;
    break;
  }
}

void handle_keyup(SDL_Keycode keycode, Input *input) {
  switch (keycode) {
  case SDLK_LEFT:
    input->direction.x = 0.0;
    break;
  case SDLK_RIGHT:
    input->direction.x = 0.0;
    break;
  case SDLK_DOWN:
    input->direction.y = 0.0;
    break;
  case SDLK_UP:
    input->direction.y = 0.0;
    break;
  case SDLK_SPACE:
    input->action = false;
    break;
  }
}

void update_input(Input *input, SDL_Event *event) {
  switch (event->type) {
  case SDL_KEYDOWN:
    handle_keydown(event->key.keysym.sym, input);
    break;
  case SDL_KEYUP:
    handle_keyup(event->key.keysym.sym, input);
    break;
  }
}