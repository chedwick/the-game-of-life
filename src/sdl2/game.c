#include "game.h"

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "input.h"
#include "update.h"
#include "output.h"
#include "sdl.h"

#include "../gol.h"

game_s game = {
    .grid = NULL,
    .cursor_row = 0,
    .cursor_col = 0,
    .mode = GOL_MODE_STOPPED,
    .window = NULL,
    .renderer = NULL,
    .font = NULL,
    .text_menu = NULL
};

static Uint64 frequency;
static double target_frame_time;
static Uint64 frame_start;

void initialization(void)
{
    sdl_initialization();

    SDL_Window *window = sdl_window_create(TITLE, WINDOW_HEIGHT, WINDOW_WIDTH);
    if (!window)
        return;
    game.window = window;
    sdl_window_set_icon(game.window, ICON_FILE);

    SDL_Renderer *renderer = sdl_renderer_create(game.window);
    if (!renderer)
        return;
    game.renderer = renderer;   

    TTF_Font *font = sdl_font_load(FONT_FILE, FONT_SIZE_MENU);
    if (!font)
        return;
    game.font = font;

    SDL_Color color = COLOR_TEXT;
    game.text_menu =
        sdl_text_create(game.renderer, game.font, TEXT_MENU,
                        color, &game.text_menu_rect);
    game.text_menu_escape =
        sdl_text_create(game.renderer, game.font, TEXT_MENU_ESCAPE,
                        color, &game.text_menu_escape_rect);
    game.text_menu_return_to_game =
        sdl_text_create(game.renderer, game.font, TEXT_MENU_RETURN_TO_GAME,
                        color, &game.text_menu_return_to_game_rect);
    game.text_menu_space =
        sdl_text_create(game.renderer, game.font, TEXT_MENU_SPACE,
                        color, &game.text_menu_space_rect);
    game.text_menu_randomize =
        sdl_text_create(game.renderer, game.font, TEXT_MENU_RANDOMIZE,
                        color, &game.text_menu_randomize_rect);
    game.text_menu_step =
        sdl_text_create(game.renderer, game.font, TEXT_MENU_STEP,
                        color, &game.text_menu_step_rect);
    game.text_menu_clear =
        sdl_text_create(game.renderer, game.font, TEXT_MENU_CLEAR,
                        color, &game.text_menu_clear_rect);
    game.text_menu_quit =
        sdl_text_create(game.renderer, game.font, TEXT_MENU_QUIT,
                        color, &game.text_menu_quit_rect);

    frequency = SDL_GetPerformanceFrequency();
    target_frame_time = 1.0 / FRAME_RATE;

    srand((unsigned) time(NULL));

    game.grid = grid_create(GRID_COLS, GRID_ROWS);
    if (!game.grid)
        return;

    grid_randomize(game.grid, ALIVE_PERCENT);

    game.mode = GOL_MODE_EDITING;
}

void finalization(void)
{
    grid_destroy(game.grid);
    game.grid = NULL;

    sdl_text_destroy(game.text_menu);
    game.text_menu = NULL;

    sdl_font_destroy(game.font);
    game.font = NULL;

    sdl_renderer_destroy(game.renderer);
    game.renderer = NULL;

    sdl_window_destroy(game.window);
    game.window = NULL;

    sdl_finalization();
}

void input(void)
{
    frame_start = SDL_GetPerformanceCounter();
    read_input_devices();
}

void update(void)
{
    switch (game.mode)
    {
        case GOL_MODE_RUNNING:
            update_running();
            break;
        case GOL_MODE_EDITING:
            update_editing();
            break;
        case GOL_MODE_PAUSED:
            update_paused();
            break;
        case GOL_MODE_STOPPED:
            update_stopped();
            break;
        default:
            // No default case
            break;
    }
}

void output(void)
{
    SDL_Color c = COLOR_BACKGROUND;
    SDL_SetRenderDrawColor(game.renderer, c.r, c.g, c.b, c.a);
    SDL_RenderClear(game.renderer);

    grid_draw(game.grid, render_cell, NULL);
    if (game.mode == GOL_MODE_EDITING)
    {
        render_cursor(game.cursor_col, game.cursor_row);
        render_menu();
    }

    SDL_RenderPresent(game.renderer);
}

// For FPS capping.
void pacing(void)
{
    Uint64 frame_end = SDL_GetPerformanceCounter();
    double elapsed = (double) (frame_end - frame_start) / frequency;

    if (elapsed < target_frame_time)
    {
        double remaining = target_frame_time - elapsed;
        SDL_Delay((Uint32) (remaining * 1000.0));
    }
}
