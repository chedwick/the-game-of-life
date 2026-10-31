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

// Font sizes
#define FONT_SIZE_SCORE 24



typedef struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    grid_s *grid;
    mode_e mode;
    
    int key;
    int cursor_row;
    int cursor_col;
} game_s;
 
extern game_s game;

void initialization(void);
void input(void);
void update(void);
void output(void);
void pacing(void);
void finalization(void);
