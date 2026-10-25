#include <stdlib.h>
#include <time.h>
#include <ncurses/curses.h>
#include "gol.h"

static void draw_cell(int x, int y, int alive, void *userdata)
{
    (void) userdata;
    mvaddch(y, x, alive ? '#' : ' ');
}

// Keys: space = pause/resume, n = single step, r = randomize,
//       c = clear, +/- = speed, arrows + enter = edit cells, q = quit.
int main(void)
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    srand((unsigned) time(NULL));

    int height, width;
    getmaxyx(stdscr, height, width);
    height = 80;
    width = 80;

    grid_s *grid = grid_create(width, height - 1);
    if (!grid)
    {
        endwin();
        return 1;
    }
    grid_randomize(grid, 25);

    int delay_ms = 100;
    int paused = 1;
    int cx = width / 2, cy = height / 2;
    int generation = 0;
    int running = 1;

    while (running) {
        grid_draw(grid, draw_cell, NULL);
        if (paused) mvaddch(cy, cx, 'X'); // cursor
        mvprintw(10, 0,
                 "gen %d | %s | %d ms | space:pause n:step r:rand c:clear +/-:speed q:quit",
                 generation, paused ? "PAUSED" : "running", delay_ms);
        refresh();

        timeout(paused ? -1 : delay_ms);
        int ch = getch();
        switch (ch) {
            case 'q': running = 0; break;
            case ' ': paused = !paused; break;
            case 'r': grid_randomize(grid, 25); generation = 0; break;
            case 'c': grid_clear(grid); generation = 0; break;
            case '+': if (delay_ms > 10) delay_ms -= 10; break;
            case '-': delay_ms += 10; break;
            case 'n': grid_step(grid); generation++; break;
            case KEY_UP:    if (paused && cy > 0) cy--; break;
            case KEY_DOWN:  if (paused && cy < height - 1) cy++; break;
            case KEY_LEFT:  if (paused && cx > 0) cx--; break;
            case KEY_RIGHT: if (paused && cx < width - 1) cx++; break;
            case '\n': 
            case KEY_ENTER: if (paused) toggle_cell(grid, cx, cy); break;
            case ERR:
                if (!paused) {
                    grid_step(grid);
                    generation++;
                }
                break;
            default: break;
        }
    }

    grid_destroy(grid);
    endwin();
    return 0;
}
