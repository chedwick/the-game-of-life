#pragma once

#include "../gol.h"

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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

// Font
#define FONT_FILE "font.otf"
#define FONT_SIZE_MENU 24

// UI labels
#define TEXT_MENU "MENU"



typedef struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    TTF_Font *font;
    SDL_Texture *text_menu;
    SDL_Rect text_menu_rect;

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
