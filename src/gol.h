#pragma once

// Grid dimensions
#define GRID_ROWS 90
#define GRID_COLS 160

// Percentage of cells alive in the initial grid
#define ALIVE_PERCENT 25

typedef enum Mode {
    GOL_MODE_STOPPED,
    GOL_MODE_RUNNING,
    GOL_MODE_PAUSED,
    GOL_MODE_EDITING
} mode_e;

typedef enum Input {
    GOL_INPUT_NONE = 0,
    GOL_INPUT_TIMEOUT,
    GOL_INPUT_QUIT,
    GOL_INPUT_PAUSE,
    GOL_INPUT_STEP,
    GOL_INPUT_RANDOMIZE,
    GOL_INPUT_CLEAR,
    GOL_INPUT_FASTER,
    GOL_INPUT_SLOWER,
    GOL_INPUT_UP,
    GOL_INPUT_DOWN,
    GOL_INPUT_LEFT,
    GOL_INPUT_RIGHT,
    GOL_INPUT_TOGGLE,
    GOL_INPUT_SPACE
} input_e;

typedef struct Grid {
    // cols * rows, row-major
    int cols;
    int rows;
    unsigned char *buffer0;
    unsigned char *buffer1;
    unsigned char *current;
    unsigned char *next;

} grid_s;

grid_s* grid_create(int rows, int cols);
void grid_destroy(grid_s *g);

void grid_step(grid_s *g);
void grid_randomize(grid_s *g, int percent_alive);
void grid_clear(grid_s *g);

typedef void (*render_callback_t)(int x, int y, int alive, void *data);
void grid_draw(const grid_s *g, render_callback_t cb, void *data);

void toggle_cell(grid_s *g, int x, int y);
