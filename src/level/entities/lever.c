#include "speed.h"

Lever *new_lever(char *line) {
  Lever *lever = malloc(sizeof(Lever));
  Vector_2d point = (Vector_2d) {0., 0.};

  point.y = atoi(strtok(line, ","));
  point.x = atoi(strtok(NULL, ","));
  lever->position = point;
  lever->activated = false;

  return lever;
}

void add_lever(Lever *lever, Level *level) {
  int i = 0;

  while (level->levers[i] != NULL) {
    i += 1;
  }
  level->levers[i] = lever;
}

void destroy_lever(Lever *lever) {
  free(lever);
}