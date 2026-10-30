#include "update.h"

#include "../gol.h"
#include "game.h"

void update_running(void)
{
    grid_step(game.grid);
}

void update_editing(void)
{
    if (game.key == KEY_SPACE)
    {
        toggle_cell(game.grid, game.cursor_col, game.cursor_row);
    }
    if (game.key == KEY_UP)
    {
        game.cursor_row--;
        if (game.cursor_row < 0)
            game.cursor_row = GRID_ROWS - 1;
    }
    else if (game.key == KEY_DOWN)
    {
        game.cursor_row++;
        if (game.cursor_row >= GRID_ROWS)
            game.cursor_row = 0;
    }
    else if (game.key == KEY_LEFT)
    {
        game.cursor_col--;
        if (game.cursor_col < 0)
            game.cursor_col = GRID_COLS - 1;
    }
    else if (game.key == KEY_RIGHT)
    {
        game.cursor_col++;
        if (game.cursor_col >= GRID_COLS)
            game.cursor_col = 0;
    }

    game.key = KEY_NONE;
}

void update_paused(void)
{
    // No logic for paused mode
}

void update_stopped(void)
{
    // No logic for stopped mode
}
