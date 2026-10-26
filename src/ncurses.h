#pragma once

/*
 * Terminal renderer. Game code talks only to this interface, so an SDL2
 * backend can replace the grid renderer by providing the same operations.
 */

typedef enum {
    INPUT_NONE = 0,
    INPUT_TIMEOUT,
    INPUT_QUIT,
    INPUT_PAUSE,
    INPUT_STEP,
    INPUT_RANDOMIZE,
    INPUT_CLEAR,
    INPUT_FASTER,
    INPUT_SLOWER,
    INPUT_UP,
    INPUT_DOWN,
    INPUT_LEFT,
    INPUT_RIGHT,
    INPUT_TOGGLE
} input_t;

int ncurses_initialization(void);
void ncurses_finalization(void);
void ncurses_screen_size(int *width, int *height);

void ncurses_draw_cell(int x, int y, int alive);
void ncurses_draw_cursor(int x, int y);
void ncurses_draw_status(int y, int generation, int paused, int delay_ms);
void ncurses_present(void);

/* timeout_ms < 0 waits forever. INPUT_TIMEOUT means the wait elapsed. */
input_t ncurses_poll_input(int timeout_ms);
