#include "game.h"

#include "../gol.h"

#include "ncurses.h"

#include <stdlib.h>
#include <time.h>

#define ALIVE_PERCENT 25
#define INITIAL_DELAY_MS 100
#define MIN_DELAY_MS 10
#define DELAY_STEP_MS 10


static int delay_ms;
static int generation;
static int cx;
static int cy;
static bool paused;

game_s game;

static void render_cell(int x, int y, int alive, void *userdata)
{
    (void) userdata;
    ncurses_draw_cell(x, y, alive);
}

void initialization(void)
{
    if (ncurses_initialization() != 0)
        return;

    int screen_w = 0;
    int screen_h = 0;
    int width;
    int height;

    game.mode = GOL_MODE_STOPPED;
    game.update = false;
    game.output = true;

    srand((unsigned) time(NULL));
    ncurses_screen_size(&screen_w, &screen_h);

    width = screen_w < GRID_COLS ? screen_w : GRID_COLS;
    height = screen_h < GRID_ROWS ? screen_h : GRID_ROWS;
    if (width < 1 || height < 2)
        return;

    game.grid = grid_create(width, height - 1);
    if (!game.grid)
        return;

    grid_randomize(game.grid, ALIVE_PERCENT);
    delay_ms = INITIAL_DELAY_MS;
    generation = 0;
    paused = true;
    cx = game.grid->cols / 2;
    cy = game.grid->rows / 2;
    game.mode = GOL_MODE_RUNNING;
}

void finalization(void)
{
    grid_destroy(game.grid);
    game.grid = NULL;
    ncurses_finalization();
}

void input(void)
{
    input_e key = ncurses_poll_input(paused ? -1 : delay_ms);

    game.update = false;
    switch (key)
    {
        case GOL_INPUT_QUIT:
            game.mode = GOL_MODE_STOPPED;
            game.output = false;
            break;
        case GOL_INPUT_PAUSE:
            paused = !paused;
            break;
        case GOL_INPUT_STEP:
            game.update = true;
            break;
        case GOL_INPUT_RANDOMIZE:
            grid_randomize(game.grid, ALIVE_PERCENT);
            generation = 0;
            break;
        case GOL_INPUT_CLEAR:
            grid_clear(game.grid);
            generation = 0;
            break;
        case GOL_INPUT_FASTER:
            if (delay_ms > MIN_DELAY_MS)
                delay_ms -= DELAY_STEP_MS;
            break;
        case GOL_INPUT_SLOWER:
            delay_ms += DELAY_STEP_MS;
            break;
        case GOL_INPUT_UP:
            if (paused && cy > 0)
                cy--;
            break;
        case GOL_INPUT_DOWN:
            if (paused && cy < game.grid->rows - 1)
                cy++;
            break;
        case GOL_INPUT_LEFT:
            if (paused && cx > 0)
                cx--;
            break;
        case GOL_INPUT_RIGHT:
            if (paused && cx < game.grid->cols - 1)
                cx++;
            break;
        case GOL_INPUT_TOGGLE:
            if (paused)
                toggle_cell(game.grid, cx, cy);
            break;
        case GOL_INPUT_TIMEOUT:
            if (!paused)
                game.update = true;
            break;
        default:
            break;
    }
}

void update(void)
{
    grid_step(game.grid);
    generation++;
}

void output(void)
{
    if (!game.grid)
        return;

    grid_draw(game.grid, render_cell, NULL);
    if (paused)
        ncurses_draw_cursor(cx, cy);
    ncurses_draw_status(game.grid->rows, generation, paused, delay_ms);
    ncurses_present();
}

void pacing(void)
{
    // No logic for pacing
}
