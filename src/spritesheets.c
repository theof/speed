#include <SDL_image.h>
#include "speed.h"

enum e_spritesheets_err {
	E_SPRITESHEETS_OK = 0,
};

typedef enum e_ss_loop_mode {
    E_SS_LOOP = 0, // make it the default
	E_SS_ONCE,
} t_ss_loop_mode;

typedef struct s_spritesheet {
	/* Mandatory attrs */
	char *path;
    char *name;
	unsigned int n_frames;
	unsigned int duration_ms;
	/* attrs with default values */
	t_ss_loop_mode mode;

	/* runtime attrs */
	SDL_Texture *texture;
	unsigned int w;
	unsigned int h;
} t_spritesheet;

t_spritesheet spritesheets[] = {
  {
	.path = "assets/7 Bird/Death.png",
	.name = "bird-death",
	.n_frames = 4,
    .duration_ms = 700,
	.mode = E_SS_ONCE
  },
  {
	.path = "assets/7 Bird/Hurt.png",
	.name = "bird-hurt",
	.n_frames = 2,
    .duration_ms = 500,
  },
  {
	.path = "assets/7 Bird/Idle.png",
	.name = "bird-idle",
	.n_frames = 4,
    .duration_ms = 1000,
  },
  {
	.path = "assets/7 Bird/Walk.png",
	.name = "bird-walk",
	.n_frames = 6,
    .duration_ms = 1500,
  },
};
// https://gigi.nullneuron.net/gigilabs/animations-with-sprite-sheets-in-sdl2/
// http://wiki.libsdl.org/SDL_SetRenderDrawColor

enum e_spritesheets_err spritesheets_init() {
	
	for (int i = 0; i < sizeof(spritesheets) / sizeof(*spritesheets); i++) {
		SDL_Image *i = IMG_Load(spritesheets[i]);
	}
	return E_SPRITESHEETS_OK;
}
