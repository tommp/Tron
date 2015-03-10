#ifndef MAIN_H
#define MAIN_H

/*Included headers*/
/*---------------------------------------------*/
/*---------------------------------------------*/

/*Included dependencies*/
/*---------------------------------------------*/
#include <SDL2/SDL.h>
#include <stdio.h>
#include <unistd.h>
/*---------------------------------------------*/

/*Header content*/
/*=============================================*/

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 700
#define LOOP_DELAY_MICRO_SEC 7000

#define UP 4
#define DOWN 2
#define LEFT 3
#define RIGHT 1


void pollevent(unsigned int *var) {
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch (event.type){
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_KEYDOWN:
				*var = 1;
				break;
			default:
				break;
		}
	}
}


void waitForEvent(){
	SDL_Event event;
	unsigned int done = 0;
	while((!done) && (SDL_WaitEvent(&event))) {
        switch(event.type) {
    
            case SDL_KEYDOWN:
                done = 1;
                break;


            case SDL_QUIT:
                done = 1;
                exit(0);
                break;
                
            default:
                break;
        } 
            
    }
}

struct Bike {
	int direction;
	int x_pos;
	int y_pos;
	unsigned int deaths;
	unsigned int speed;
	int blue;
	int red;
	int green;
};

int check_if_dead(struct Bike * player, char screen_mask[WINDOW_WIDTH][WINDOW_HEIGHT]) {
	if (player->x_pos < 0 || player->x_pos > WINDOW_WIDTH) {
		return 1;
	}
	else if (player->y_pos < 0 || player->y_pos > WINDOW_HEIGHT) {
		return 1;
	}
	else if(screen_mask[player->x_pos][player->y_pos] == 1) {
		return 1;
	}
	else{
		return 0;
	}
}

void increment_position(struct Bike * player) {
	switch(player->direction) {
		case RIGHT:
			player->x_pos++;
			break;
		case DOWN:
			player->y_pos++;
			break;
		case LEFT:
			player->x_pos--;
			break;
		case UP:
			player->y_pos--;
			break;
	}
}

void set_direction(struct Bike * player1, struct Bike * player2, unsigned int *done) {
	SDL_Event event;
	while( SDL_PollEvent( &event ) ){
        switch( event.type ){
            /* Look for a keypress */
            case SDL_KEYDOWN:
                /* Check the SDLKey values and move change the coords */
                switch( event.key.keysym.sym ){
                    case SDLK_LEFT:
                    	if(player1->direction == RIGHT){
                    		break;
                    	}
                        player1->direction = LEFT;
                        break;
                    case SDLK_RIGHT:
                    	if(player1->direction == LEFT){
                    		break;
                    	}
                        player1->direction = RIGHT;
                        break;
                    case SDLK_UP:
                    	if(player1->direction == DOWN){
                    		break;
                    	}
                        player1->direction = UP;
                        break;
                    case SDLK_DOWN:
                    	if(player1->direction == UP){
                    		break;
                    	}
                        player1->direction = DOWN;
                        break;
                    case SDLK_a:
                    	if(player2->direction == RIGHT){
                    		break;
                    	}
                        player2->direction = LEFT;
                        break;
                    case SDLK_d:
                    	if(player2->direction == LEFT){
                    		break;
                    	}
                        player2->direction = RIGHT;
                        break;
                    case SDLK_w:
                    	if(player2->direction == DOWN){
                    		break;
                    	}
                        player2->direction = UP;
                        break;
                    case SDLK_s:
                    	if(player2->direction == UP){
                    		break;
                    	}
                        player2->direction = DOWN;
                        break;
                    default:
                        break;
                }
             	break;
            case SDL_QUIT:
                *done = 1;
                printf("Player one deaths: %d\n", player1->deaths);
                printf("Player two deaths: %d\n", player2->deaths);
                exit(0);
                break;
        }
    }
}

void draw_player_line(struct Bike * player, 
						SDL_Renderer *ren, 
						char screen_mask[WINDOW_WIDTH][WINDOW_HEIGHT],
						unsigned int * done) {
	int i;
	for (i = 0; i < player->speed; i++) {
		increment_position(player);
		if (check_if_dead(player, screen_mask)) {
			player->deaths++;
			player->x_pos = WINDOW_WIDTH/2;
			player->y_pos = WINDOW_HEIGHT/2;
			SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
			SDL_RenderClear(ren);
			int x;
			int y;
			for (x = 0; x < WINDOW_WIDTH; x++) {
				for (y = 0; y < WINDOW_HEIGHT; y++) {
					screen_mask[x][y] = 0;
				} 
			}
		}
		screen_mask[player->x_pos][player->y_pos] = 1;
		SDL_SetRenderDrawColor(ren, player->red, player->blue, player->green, 255);
		SDL_RenderDrawPoint(ren, player->x_pos, player->y_pos);
	}
	SDL_RenderPresent(ren);
}


/*=============================================*/

#endif