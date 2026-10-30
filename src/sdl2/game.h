#pragma once

#include "../gol.h"

#include <stdbool.h>
#include <SDL2/SDL.h>

// Game labels
#define TITLE "THE GAME OF LIFE"

#define TILE_HEIGHT 12
#define TILE_WIDTH 12
#define ZOOM 1

#define GRID_HEIGHT (TILE_HEIGHT * GRID_ROWS)
#define GRID_WIDTH (TILE_WIDTH * GRID_COLS)

#define WINDOW_HEIGHT (GRID_HEIGHT * ZOOM)
#define WINDOW_WIDTH (GRID_WIDTH * ZOOM)

#define SPEED 200
#define FRAME_RATE 10


// Temporary to make it compatible with NCURSES
#define KEY_DOWN    402    // down-arrow key
#define KEY_UP      403    // up-arrow key
#define KEY_LEFT    404    // left-arrow key
#define KEY_RIGHT   405    // right-arrow key
#define KEY_SPACE   32     // space key
#define KEY_NONE    0      // no key pressed

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
    mode_e mode;
    bool update;
    bool output;
    int cursor_row;
    int cursor_col;
} game_s;
 
extern game_s game;
extern grid_s *grid;

void initialization(void);
void input(void);
void update(void);
void output(void);
void pacing(void);
void finalization(void);


void pool_events(void);
void output_score(void);
