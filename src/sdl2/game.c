#include "game.h"

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "output.h"
#include "sdl.h"
#include "update.h"

#include "../gol.h"

grid_s *grid;

game_s game = {
    .cursor_row = 0,
    .cursor_col = 0,
    .mode = GAME_MODE_STOPPED,
    .update = false,
    .output = false,
    .window = NULL,
    .renderer = NULL
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

    SDL_Renderer *renderer = sdl_renderer_create(game.window);
    if (!renderer)
        return;
    game.renderer = renderer;   

    game.mode = GAME_MODE_RUNNING;
    game.update = true;
    game.output = true;

    frequency = SDL_GetPerformanceFrequency();
    target_frame_time = 1.0 / FRAME_RATE;

    srand((unsigned) time(NULL));

    grid = grid_create(GRID_COLS, GRID_ROWS);
    if (!grid)
        return;

    grid_randomize(grid, ALIVE_PERCENT);
}

void finalization(void)
{
    grid_destroy(grid);
    grid = NULL;

    sdl_window_destroy(game.window);
    game.window = NULL;

    sdl_renderer_destroy(game.renderer);
    game.renderer = NULL;

    sdl_finalization();
}

void input(void)
{
    frame_start = SDL_GetPerformanceCounter();
    pool_events();
}

void update(void)
{
    switch (game.mode)
    {
        case GAME_MODE_RUNNING:
            update_running();
            break;
        case GAME_MODE_EDITING:
            update_editing();
            break;
        case GAME_MODE_PAUSED:
            update_paused();
            break;
        case GAME_MODE_STOPPED:
            update_stopped();
            break;
        default:
            // No default case
            break;
    }
}

void output(void)
{
    // Clear screen
    SDL_SetRenderDrawColor(game.renderer, 63, 63, 116, 255);
    // What does it do?!
    SDL_RenderClear(game.renderer);
    /// ^^^

    grid_draw(grid, render_cell, NULL);
    if (game.mode == GAME_MODE_EDITING)
    {
        render_cursor(game.cursor_col, game.cursor_row);
    }

    // Update screen
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

// int initialize_fonts(void)
// {
//     gfx_font_s *font = construct_gfx_font("assets/gabs_pixel.ttf");
//     if (font)
//     {
//         SDL_Color color = {255, 255, 255, 255};
//         gfx_gpu_text_s *text_score =
//             gfx_gpu_text_render(game.renderer, font, "SCORE", color);
//         game.font = font;
//         game.text_score = text_score;
//     }
//     return 0;
// }
