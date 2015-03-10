#include "./headers/main.h"


int main(int argc, char**argv) {

	char screen_mask[WINDOW_WIDTH][WINDOW_HEIGHT] = {0};

	struct Bike player1;
	player1.x_pos = 40;
	player1.y_pos = 40;
	player1.direction = RIGHT;
	player1.speed = 4;
	player1.deaths = 0;
	player1.blue = 0;
	player1.red = 0;
	player1.green = 255;

	struct Bike player2;
	player2.x_pos = WINDOW_HEIGHT-40;
	player2.y_pos = WINDOW_WIDTH-40;
	player2.direction = LEFT;
	player2.speed = 4;
	player2.deaths = 0;
	player2.blue = 0;
	player2.red = 255;
	player2.green = 0;

	/*Initializes SDL for graphical display*/
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		printf("Init failed\n");
		return 1;
	}

	/*Disables pesky screensavers while our wonderful graphics are beeing displayed*/
	SDL_DisableScreenSaver();

	/*Initializes a window to render graphics in*/
	SDL_Window *win = SDL_CreateWindow("EM", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (win == NULL){
		printf("Failed to create window\n");
		return 1;
	}

	/*Initializes the renderer to draw in*/
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL){
		printf("Failed to create renderer\n");
		return 1;
	}
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
	unsigned int done = 0;

	while(!done) {
		set_direction(&player1, &player2, &done);
		draw_player_line(&player1, ren, screen_mask, &done);
		draw_player_line(&player2, ren, screen_mask, &done);
		usleep(LOOP_DELAY_MICRO_SEC);
	}
	waitForEvent();
	return 0;
}