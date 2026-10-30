#include "game.h"
#include "sdl.h"

#include "../gol.h"

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

static grid_s *grid;

game_s game = {
    .running = false,
    .update = false,
    .output = false,
    .window = NULL,
    .renderer = NULL
};


static Uint64 frequency;
static double targetFrameTime;
static Uint64 frameStart;

static void draw_cell(int x, int y, int alive, void *userdata);

void game_initialization(void)
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

    game.running = true;
    game.update = true;
    game.output = true;

    frequency = SDL_GetPerformanceFrequency();
    targetFrameTime = 1.0 / FRAME_RATE;

    srand((unsigned) time(NULL));

    grid = grid_create(GRID_COLS, GRID_ROWS);
    if (!grid)
        return;

    grid_randomize(grid, ALIVE_PERCENT);
}

void game_finalization(void)
{
    sdl_window_destroy(game.window);
    game.window = NULL;

    sdl_renderer_destroy(game.renderer);
    game.renderer = NULL;

    sdl_finalization();
}

void game_input(void)
{
    frameStart = SDL_GetPerformanceCounter();
    game_tick();
    game_pool_events();
}

void game_update(void)
{
    grid_step(grid);
}

void game_output(void)
{
    // Clear screen
    SDL_SetRenderDrawColor(game.renderer, 63, 63, 116, 255);
    // What does it do?!
    SDL_RenderClear(game.renderer);
    /// ^^^

    grid_draw(grid, draw_cell, NULL);

    // Update screen
    SDL_RenderPresent(game.renderer);

    // For FPS capping.
    Uint64 frameEnd = SDL_GetPerformanceCounter();
    double elapsed = (double)(frameEnd - frameStart) / frequency;

    if (elapsed < targetFrameTime) {
        double remaining = targetFrameTime - elapsed;
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

static void draw_cell(int x, int y, int alive, void *userdata)
{
    (void) userdata;
    SDL_Rect rect = { x * TILE_WIDTH, y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };
    if (alive)
    {
        SDL_SetRenderDrawColor(game.renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(game.renderer, &rect);
    }
}
