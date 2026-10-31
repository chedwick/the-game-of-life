#include "update.h"

#include "../gol.h"
#include "game.h"

void update_running(void)
{
    grid_step(game.grid);
}

void update_editing(void)
{
    switch (game.key)
    {
        case GOL_INPUT_SPACE:
            toggle_cell(game.grid, game.cursor_col, game.cursor_row);
            break;
        case GOL_INPUT_UP:
            game.cursor_row--;
            if (game.cursor_row < 0)
                game.cursor_row = GRID_ROWS - 1;
            break;
        case GOL_INPUT_DOWN:
            game.cursor_row++;
            if (game.cursor_row >= GRID_ROWS)
                game.cursor_row = 0;
            break;
        case GOL_INPUT_LEFT:
            game.cursor_col--;
            if (game.cursor_col < 0)
                game.cursor_col = GRID_COLS - 1;
            break;
        case GOL_INPUT_RIGHT:
            game.cursor_col++;
            if (game.cursor_col >= GRID_COLS)
                game.cursor_col = 0;
            break;
        case GOL_INPUT_CLEAR:
            grid_clear(game.grid);
            break;
        case GOL_INPUT_RANDOMIZE:
            grid_randomize(game.grid, ALIVE_PERCENT);
            break;
        case GOL_INPUT_STEP:
            grid_step(game.grid);
            break;
        default:
            // No default case
            break;
    }

    game.key = GOL_INPUT_NONE;
}

void update_paused(void)
{
    // No logic for paused mode
}

void update_stopped(void)
{
    // No logic for stopped mode
}
