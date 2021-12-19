#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "speed.h"

static const char BASE_PATH[] = "./levels/";

FILE *open_csv(char *full_path) {
  FILE *fptr;
  size_t len = 0;
  ssize_t read;
  char *line = NULL;

  if ((fptr = fopen(full_path, "r")) == NULL) {
    printf("Failed to open %s\n", full_path);
    exit(read);
  }

  if ((read = getline(&line, &len, fptr)) == -1) {
    printf("Failed to read %s\n", full_path);
    exit(read);
  }

  free(line);
  return fptr;
}

int get_object_count(char *full_path, char *object_type) {
  FILE *fptr;
  int obj_count = 0;
  size_t len = 0;
  ssize_t read;
  char *line = NULL;

  fptr = open_csv(full_path);
  while ((read = getline(&line, &len, fptr)) != -1) {
    if (strstr(line, object_type) != NULL) {
      obj_count += 1;
    }
  }

  fclose(fptr);
  free(line);

  return obj_count;
}

Wall *build_wall(char *line) {
  Wall *wall = malloc(sizeof(Wall));
  Rectangle rectangle;
  Point point;

  point.y = atoi(strtok(line, ","));
  point.x = atoi(strtok(NULL, ","));
  rectangle.top_left = point;

  point.y = atoi(strtok(NULL, ","));
  point.x = atoi(strtok(NULL, ","));
  rectangle.bottom_right = point;

  wall->position = rectangle;
  return wall;
}

void add_wall(Wall *wall, Level *level) {
  int i = 0;

  while (level->walls[i] != NULL) {
    i += 1;
  }
  level->walls[i] = wall;
}

Lever *build_lever(char *line) {
  Lever *lever = malloc(sizeof(Lever));
  Point point;

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

End *build_end(char *line) {
  End *end = malloc(sizeof(End));
  Point point;

  point.x = atoi(strtok(line, ","));
  point.y = atoi(strtok(NULL, ","));
  end->position = point;

  return end;
}

void add_end(End *end, Level *level) { level->end = end; }

Start *build_start(char *line) {
  Start *start = malloc(sizeof(Start));
  Point point;

  point.x = atoi(strtok(line, ","));
  point.y = atoi(strtok(NULL, ","));
  start->position = point;

  return start;
}

void add_start(Start *start, Level *level) { level->start = start; }

void build_level(Level *level, char *full_path) {
  FILE *fptr;
  size_t len = 0;
  ssize_t read;
  char *line = NULL;

  fptr = open_csv(full_path);
  while ((read = getline(&line, &len, fptr)) != -1) {

    if (strstr(line, "wall") != NULL) {
      add_wall(build_wall(line), level);
    } else if (strstr(line, "lever") != NULL) {
      add_lever(build_lever(line), level);
    } else if (strstr(line, "end") != NULL) {
      add_end(build_end(line), level);
    } else if (strstr(line, "start") != NULL) {
      add_start(build_start(line), level);
    } else {
      printf("Dafuk ???\n");
    }
  }
  free(line);
  pclose(fptr);
}

void destroy_level(Level *level) {
  int i;

  for (i = 0; i < level->wall_count; i += 1) {
    free(level->walls[i]);
  }
  free(level->walls);
  for (i = 0; i < level->lever_count; i += 1) {
    free(level->levers[i]);
  }
  free(level->levers);
  free(level->start);
  free(level->end);
  free(level);
}

Level *parse_level(char *filename) {
  char *full_path = malloc(strlen(BASE_PATH) + strlen(filename) + 1);
  int i;

  strcpy(full_path, BASE_PATH);
  strcat(full_path, filename);

  Level *level = malloc(sizeof(Level));
  level->wall_count = get_object_count(full_path, "#wall");
  level->lever_count = get_object_count(full_path, "#lever");

  level->walls = calloc(level->wall_count, sizeof(Wall));
  for (i = 0; i < level->wall_count; i += 1) {
    level->walls[i] = NULL;
  }

  level->levers = calloc(level->lever_count, sizeof(Lever));
  for (i = 0; i < level->lever_count; i += 1) {
    level->levers[i] = NULL;
  }

  build_level(level, full_path);
  free(full_path);
  return level;
}
