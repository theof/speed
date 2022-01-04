#include "speed.h"

Start *new_start(char *line) {
  Start *start = malloc(sizeof(Start));
  start->position = (Vector_2d) {0., 0.};

  start->position.y = atoi(strtok(line, ","));
  start->position.x = atoi(strtok(NULL, ","));
  return start;
}

void add_start(Start *start, Level *level) { level->start = start; }

void destroy_start(Start *start) {
  free(start);
}