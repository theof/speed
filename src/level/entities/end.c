#include "speed.h"

End *new_end(char *line) {
  End *end = malloc(sizeof(End));
  end->position = new_vector_2d(0.0, 0.0);

  end->position->y = atoi(strtok(line, ","));
  end->position->x = atoi(strtok(NULL, ","));
  return end;
}

void add_end(End *end, Level *level) { level->end = end; }
void destroy_end(End *end) {
  destroy_vector_2d(end->position);
  free(end);
}