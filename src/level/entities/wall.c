#include "speed.h"

Wall *new_wall(char *line) {
  Wall *wall = malloc(sizeof(Wall));
  Rectangle *rectangle = new_empty_rectangle();

  rectangle->top_left->y = atoi(strtok(line, ","));
  rectangle->top_left->x = atoi(strtok(NULL, ","));

  rectangle->bottom_right->y = atoi(strtok(NULL, ","));
  rectangle->bottom_right->x = atoi(strtok(NULL, ","));

  wall->definition = rectangle;
  return wall;
}

void add_wall(Wall *wall, Level *level) {
  int i = 0;

  while (level->walls[i] != NULL) {
    i += 1;
  }
  level->walls[i] = wall;
}

void destroy_wall(Wall *wall) {
  destroy_rectangle(wall->definition);
  free(wall);
}