#include "ncurses.h"

#include <ncurses/curses.h>

static int screen_cols;
static int screen_rows;

int ncurses_initialization(void)
{
    if (initscr() == NULL)
        return -1;

    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, screen_rows, screen_cols);
    return 0;
}

void ncurses_finalization(void)
{
    endwin();
}

void ncurses_screen_size(int *width, int *height)
{
    if (width)
        *width = screen_cols;
    if (height)
        *height = screen_rows;
}

void ncurses_draw_cell(int x, int y, int alive)
{
    mvaddch(y, x, alive ? '#' : ' ');
}

void ncurses_draw_cursor(int x, int y)
{
    mvaddch(y, x, 'X');
}

void ncurses_draw_status(int y, int generation, int paused, int delay_ms)
{
    mvprintw(y, 0,
             "gen %d | %s | %d ms | space:pause n:step "
             "r:rand c:clear +/-:speed q:quit",
             generation,
             paused ? "PAUSED" : "running",
             delay_ms);
    clrtoeol();
}

void ncurses_present(void)
{
    refresh();
}

input_e ncurses_poll_input(int timeout_ms)
{
    timeout(timeout_ms);
    switch (getch()) {
        case 'q':
            return GOL_INPUT_QUIT;
        case ' ':
            return GOL_INPUT_PAUSE;
        case 'n':
            return GOL_INPUT_STEP;
        case 'r':
            return GOL_INPUT_RANDOMIZE;
        case 'c':
            return GOL_INPUT_CLEAR;
        case '+':
            return GOL_INPUT_FASTER;
        case '-':
            return GOL_INPUT_SLOWER;
        case KEY_UP:
            return GOL_INPUT_UP;
        case KEY_DOWN:
            return GOL_INPUT_DOWN;
        case KEY_LEFT:
            return GOL_INPUT_LEFT;
        case KEY_RIGHT:
            return GOL_INPUT_RIGHT;
        case '\n':
        case KEY_ENTER:
            return GOL_INPUT_TOGGLE;
        case ERR:
            return GOL_INPUT_TIMEOUT;
        default:
            return GOL_INPUT_NONE;
    }
}
