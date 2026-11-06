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

// Icon
#define ICON_FILE "icon.png"

// Font
#define FONT_FILE "font.otf"
#define FONT_SIZE_MENU 24

// UI labels
#define TEXT_MENU "MENU"
#define TEXT_MENU_ESCAPE "<ESC> RETURN TO GAME"
#define TEXT_MENU_RETURN_TO_GAME "<ENTER> RETURN TO GAME"
#define TEXT_MENU_SPACE "<SPACE> SET/UNSET CELL"
#define TEXT_MENU_RANDOMIZE "<R> RANDOMIZE"
#define TEXT_MENU_STEP "<S> STEP GENERATION"
#define TEXT_MENU_CLEAR "<C> CLEAR THE BOARD"
#define TEXT_MENU_QUIT "<Q> QUIT THE GAME"

typedef struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    TTF_Font *font;
    SDL_Texture *text_menu;
    SDL_Rect text_menu_rect;

    SDL_Texture *text_menu_escape;
    SDL_Rect text_menu_escape_rect;

    SDL_Texture *text_menu_space;
    SDL_Rect text_menu_space_rect;

    SDL_Texture *text_menu_randomize;
    SDL_Rect text_menu_randomize_rect;

    SDL_Texture *text_menu_step;
    SDL_Rect text_menu_step_rect;

    SDL_Texture *text_menu_clear;
    SDL_Rect text_menu_clear_rect;

    SDL_Texture *text_menu_quit;
    SDL_Rect text_menu_quit_rect;

    SDL_Texture *text_menu_return_to_game;
    SDL_Rect text_menu_return_to_game_rect;

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
