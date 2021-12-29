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

void build_level(Level *level, char *full_path) {
  FILE *fptr;
  size_t len = 0;
  ssize_t read;
  char *line = NULL;

  fptr = open_csv(full_path);
  while ((read = getline(&line, &len, fptr)) != -1) {

    if (strstr(line, "wall") != NULL) {
      add_wall(new_wall(line), level);
    } else if (strstr(line, "lever") != NULL) {
      add_lever(new_lever(line), level);
    } else if (strstr(line, "end") != NULL) {
      add_end(new_end(line), level);
    } else if (strstr(line, "start") != NULL) {
      add_start(new_start(line), level);
    } else {
      printf("Dafuk ???\n");
    }
  }
  free(line);
  pclose(fptr);
}

Level *parse_level(char *filename) {
  char *full_path = malloc(strlen(BASE_PATH) + strlen(filename) + 1);
  int i;

  strcpy(full_path, BASE_PATH);
  strcat(full_path, filename);

  Level *level = new_level();
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
