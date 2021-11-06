#include "speed.h"

#define Sint16Max 32767

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
    if (input->direction.x < 0)
      input->direction.x = 0.0;
    break;
  case SDLK_RIGHT:
    if (input->direction.x > 0)
      input->direction.x = 0.0;
    break;
  case SDLK_UP:
    if (input->direction.y < 0)
      input->direction.y = 0.0;
    break;
  case SDLK_DOWN:
    if (input->direction.y > 0)
      input->direction.y = 0.0;
    break;
  case SDLK_SPACE:
    input->action = false;
    break;
  }
}

void handle_button_up(Input *input, SDL_ControllerButtonEvent event) {
  switch (event.button) {
  case SDL_CONTROLLER_BUTTON_A:
    input->action = true;
    break;
  }
}

void handle_button_down(Input *input, SDL_ControllerButtonEvent event) {
  switch (event.button) {
  case SDL_CONTROLLER_BUTTON_A:
    input->action = false;
    break;
  }
}

void handle_controller_motion(Input *input, SDL_ControllerAxisEvent event) {
  switch (event.axis) {
  case SDL_CONTROLLER_AXIS_LEFTX:
    input->direction.x =
        (float)event.value / (float)Sint16Max; // Normalize to -1.0 ~ 1.0
    break;
  case SDL_CONTROLLER_AXIS_LEFTY:
    input->direction.y =
        (float)event.value / (float)Sint16Max; // Normalize to -1.0 ~ 1.0
    break;
  }
}

void init_gamepad(Input *input,
                  SDL_ControllerDeviceEvent controler_device_event) {
  input->controller = SDL_GameControllerOpen(controler_device_event.which);
}

Input *new_input() {
  Input *input = (Input *)malloc(sizeof(Input));

  input->direction.x = 0.0;
  input->direction.y = 0.0;
  input->action = false;
  // Wait for event to assign
  input->controller = NULL;
  return input;
}

void destroy_input(Input *input) {
  if (input->controller != NULL)
    SDL_GameControllerClose(input->controller);
  free(input);
}

void detect_controlers(Input *input, SDL_Event *event) {
  if (event->type == SDL_CONTROLLERDEVICEADDED)
    init_gamepad(input, event->cdevice);
}

void update_input(Input *input, SDL_Event *event) {
  switch (event->type) {
  case SDL_KEYDOWN:
    handle_keydown(event->key.keysym.sym, input);
    break;
  case SDL_KEYUP:
    handle_keyup(event->key.keysym.sym, input);
    break;
  case SDL_JOYAXISMOTION:
    handle_controller_motion(input, event->caxis);
    break;
  case SDL_CONTROLLERBUTTONDOWN:
    handle_button_down(input, event->cbutton);
    break;
  case SDL_CONTROLLERBUTTONUP:
    handle_button_up(input, event->cbutton);
    break;
  }
}