#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>

// Game labels
#define TITLE "THE GAME OF LIFE"

#define TILE_HEIGHT 32
#define TILE_WIDTH 32

#define GRID_ROWS 20
#define GRID_COLS 30
#define GRID_HEIGHT TILE_HEIGHT * GRID_ROWS
#define GRID_WIDTH TILE_WIDTH * GRID_COLS

#define SPEED 200
#define FRAME_RATE 100

#define ZOOM 2

// Temporary to make it compatible with NCURSES
#define KEY_DOWN	0402		/* down-arrow key */
#define KEY_UP		0403		/* up-arrow key */
#define KEY_LEFT	0404		/* left-arrow key */
#define KEY_RIGHT	0405		/* right-arrow key */

// Font sizes
#define FONT_SIZE_SCORE 24

// The Game of Life
#define ALIVE_PERCENT 25

typedef struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    time_t tick;
    time_t state_update_tick;
    time_t state_output_tick;
    int key;
    bool pause;
    bool running;
    bool update;
    bool output;
} game_s;
 
extern game_s game;

void game_initialization(void);
void game_finalization(void);

void game_input(void);
void game_update(void);
void game_output(void);

void game_tick(void);
void game_pool_events(void);
void game_output_score(void);
