#include "speed.h"

// TODO got to determine the correct button
#define ACTION_BUTTON (Uint8)0

#define JOYSTICK_X_AXIS (Uint8)0
#define JOYSTICK_Y_AXIS (Uint8)1

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

void handle_button_up(Input *input, SDL_JoyButtonEvent event) {
  switch (event.button) {
  case ACTION_BUTTON:
    input->action = true;
    break;
  }
}

void handle_button_down(Input *input, SDL_JoyButtonEvent event) {
  switch (event.button) {
  case ACTION_BUTTON:
    input->action = false;
    break;
  }
}

void handle_joystick_motion(Input *input, SDL_JoyAxisEvent event) {
  switch (event.axis) {
  case JOYSTICK_X_AXIS:
    input->direction.x =
        (float)event.value /
        (float)SDL_JOYSTICK_AXIS_MAX; // Normalize to -1.0 ~ 1.0
    break;
  case JOYSTICK_Y_AXIS:
    input->direction.y =
        (float)event.value /
        (float)SDL_JOYSTICK_AXIS_MAX; // Normalize to -1.0 ~ 1.0
    break;
  }
}

Input *new_input() {
  Input *input = (Input *)malloc(sizeof(Input));

  input->direction.x = 0.0;
  input->direction.y = 0.0;
  input->action = false;
  return input;
}

void destroy_input(Input *input) { free(input); }

void update_input(Input *input, SDL_Event *event) {
  switch (event->type) {
  case SDL_KEYDOWN:
    handle_keydown(event->key.keysym.sym, input);
    break;
  case SDL_KEYUP:
    handle_keyup(event->key.keysym.sym, input);
    break;
  case SDL_JOYAXISMOTION:
    handle_joystick_motion(input, event->jaxis);
    break;
  case SDL_JOYBUTTONDOWN:
    handle_button_down(input, event->jbutton);
    break;
  case SDL_JOYBUTTONUP:
    handle_button_up(input, event->jbutton);
    break;
  }
}