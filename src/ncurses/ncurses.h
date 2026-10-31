#pragma once

#include "../gol.h"

int ncurses_initialization(void);
void ncurses_finalization(void);
void ncurses_screen_size(int *width, int *height);

void ncurses_draw_cell(int x, int y, int alive);
void ncurses_draw_cursor(int x, int y);
void ncurses_draw_status(int y, int generation, int paused, int delay_ms);
void ncurses_present(void);

// timeout_ms < 0 waits forever. GOL_INPUT_TIMEOUT means the wait elapsed
input_e ncurses_poll_input(int timeout_ms);
