#include "speed.h"

void new_input() {
  Input *input = (Input *)malloc(sizeof(Input));

  input->left = 0.0;
  input->right = 0.0;
  input->bottom = 0.0;
  input->up= 0.0;
  input->action = false;
  input->action_delta = 0.0;
}

void destroy_input() {}

void update_input(Input *input, SDL_Event *event) {}