#include "game.h"
#include "game_initialization.h"
#include "game_finalization.h"

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
    .renderer = NULL,
};

int game_initialization(void)
{
    if (initialize_window() != 0)
    {
        return 1;
    }
    if (initialize_renderer() != 0)
    {
        return 1;
    }

    game.running = true;
    game.update = true;
    game.output = true;

    srand((unsigned) time(NULL));

    grid = grid_create(GRID_WIDTH, GRID_HEIGHT);
    if (!grid)
        return 1;

    grid_randomize(grid, ALIVE_PERCENT);
    return 0;
}

int game_finalization(void)
{
    if (finalize_window() != 0)
    {
        return 1;
    }
    if (finalize_renderer() != 0)
    {
        return 1;
    }
    return 0;
}

void game_output(void)
{
    Uint32 tick = SDL_GetTicks();
    // SDL: Clear screen
    // Not necessary because tiles blit the whole screen.
    SDL_SetRenderDrawColor(game.renderer, 63, 63, 116, 255);
    // What does it do?!
    SDL_RenderClear(game.renderer);
    /// ^^^

    // Update screen
    SDL_RenderPresent(game.renderer);

    // Consume the output tick event.
    // game.output = false;
}
