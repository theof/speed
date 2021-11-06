#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "speed.h"

static const char BASE_PATH[] = "./levels/";


FILE*	open_csv(char* full_path) {
	FILE	*fptr;
	size_t	len = 0;
	ssize_t	read;
	char	*line = NULL;

	if ((fptr = fopen(full_path, "r")) == NULL)
	{
		printf("Failed to open %s\n", full_path);
		exit(read);
	}

	if ((read = getline(&line, &len, fptr)) == -1)
	{
		printf("Failed to read %s\n", full_path);
		exit(read);
	}

	free(line);
	return fptr;
}


int	 	get_object_count(char* full_path, char* object_type) {
	FILE*	fptr;
	int		obj_count = 0;
	size_t	len = 0;
	ssize_t	read;
	char	*line = NULL;

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

Wall*	build_wall(char* line) {
	Wall		*wall = malloc(sizeof(Wall));
	Rectangle	rectangle;
	Point		point;

	
	point.y = atoi(strtok(line, ","));
	point.x = atoi(strtok(line, ","));
	memcpy(&rectangle.top_left, &point, sizeof(Point));

	point.y = atoi(strtok(line, ","));
	point.x = atoi(strtok(line, ","));
	memcpy(&rectangle.bottom_right, &point, sizeof(Point));

	memcpy(&wall->position, &rectangle, sizeof(Rectangle));

	printf(
		"Wall (%d,%d), (%d,%d)\n",
		wall->position.top_left.y,
		wall->position.top_left.x,
		wall->position.bottom_right.y,		
		wall->position.bottom_right.x
	);

	return wall;
	
}

void	build_level(Level* level, char* full_path) {
	FILE*	fptr;
	size_t	len = 0;
	ssize_t	read;
	char*	line = NULL;
	Wall*	wall = NULL;

	fptr = open_csv(full_path);
	while ((read = getline(&line, &len, fptr)) != -1) {
		if (strstr(line, "wall") != NULL) {
			printf("building wall from %s", line);
			wall = build_wall(line);
		}
	}
}

void	parse_level(char* filename)
{
	char	*full_path = malloc(strlen(BASE_PATH)+strlen(filename)+1);
	int		wall_count;
	int 	lever_count;

	strcpy(full_path, BASE_PATH);
	strcat(full_path, filename);
	printf("reading level: %s\n", full_path);

	wall_count = get_object_count(full_path, "#wall");
	lever_count = get_object_count(full_path, "#lever");

	printf("levers: %d\nwalls: %d\n", lever_count, wall_count);

	Level	*level = malloc(
		(sizeof(int) * 2) +
		sizeof(Start) +
		sizeof(End) +
		sizeof(Wall) * wall_count +
		sizeof(Lever) * lever_count
	);

	build_level(level, full_path);
	
}






