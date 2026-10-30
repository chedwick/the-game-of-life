#pragma once

#define GRID_ROWS 90
#define GRID_COLS 160

typedef enum mode_e {
    GAME_MODE_STOPPED,
    GAME_MODE_RUNNING,
    GAME_MODE_PAUSED,
    GAME_MODE_EDITING
} mode_e;

typedef struct Grid {
    int width;
    int height;
    // width * height, row-major, 1 = alive
    unsigned char *buffer0;
    unsigned char *buffer1;
    unsigned char *current;
    unsigned char *next;

} grid_s;

grid_s* grid_create(int width, int height);
void grid_destroy(grid_s *g);

void grid_step(grid_s *g);
void grid_randomize(grid_s *g, int percent_alive);
void grid_clear(grid_s *g);

typedef void (*render_callback_t)(int x, int y, int alive, void *data);
void grid_draw(const grid_s *g, render_callback_t cb, void *data);

void toggle_cell(grid_s *g, int x, int y);
