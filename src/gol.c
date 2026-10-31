// implementation file for game of life
#include "gol.h"

#include <stdlib.h>
#include <string.h>

// Row-major order
#define CELL(b, col, row) ((b)->current[(row) * (b)->cols + (col)])

grid_s *grid_create(int col, int row)
{
    grid_s *g = malloc(sizeof *g);
    if (!g) return NULL;
    g->cols = col;
    g->rows = row;
    size_t size = (size_t) col * row;
    // one allocation holds both buffers:
    // buffer0 in the first half,
    // and buffer1 in the second half
    g->buffer0 = calloc(size * 2, 1);
    if (!g->buffer0)
    {
        free(g);
        return NULL;
    }
    g->buffer1 = g->buffer0 + size;
    g->current = g->buffer0;
    g->next = g->buffer1;
    return g;
}

void grid_destroy(grid_s *g)
{
    if (!g) return;
    free(g->buffer0);
    free(g);
}

void grid_randomize(grid_s *g, int percent_alive)
{
    for (int i = 0; i < g->cols * g->rows; i++)
    {
        g->current[i] = (rand() % 100) < percent_alive;
    }
}

void toggle_cell(grid_s *g, int x, int y)
{
    if (x < 0 || x >= g->cols || y < 0 || y >= g->rows) return;
    CELL(g, x, y) ^= 1;
}

void grid_clear(grid_s *g)
{
    memset(g->current, 0, (size_t) g->cols * g->rows);
}

/*
The universe **wraps** (it's a torus), so corner cells have 8 neighbors, not 3.

This happens in `count_neighbors`:

```c
int nx = (col + dx + g->cols) % g->cols;
int ny = (row + dy + g->rows) % g->rows;
```

Adding `g->cols` / `g->rows` before the modulo keeps the value non-negative when `x + dx` is `-1`, because C's `%` can return negative results. So:

- For the cell at (0, 0), the neighbor at `dx = -1` maps to `col = cols - 1`, the right edge.
- The neighbor at `dy = -1` maps to `row = rows - 1`, the bottom edge.
- The diagonal neighbor of the top-left corner is the bottom-right corner cell.

Every cell, including edges and corners, therefore checks all 8 surrounding positions.

If you want a hard-edged universe instead (corners with 3 neighbors, edges with 5), replace those two lines with a bounds check that skips out-of-range positions:

```c
int nx = col + dx, ny = row + dy;
if (nx < 0 || nx >= g->cols || ny < 0 || ny >= g->rows) continue;
```

One edge case with wrapping: if the width or height is 1 or 2, a cell can count the same neighbor more than once, or count itself. That doesn't matter for normal board sizes.
*/
static int count_neighbors(const grid_s *g, int col, int row)
{
    int n = 0;
    for (int dr = -1; dr <= 1; dr++)
        for (int dc = -1; dc <= 1; dc++)
        {
            if (dc == 0 && dr == 0) continue;
            int nc = (col + dc + g->cols) % g->cols;
            int nr = (row + dr + g->rows) % g->rows;
            n += CELL(g, nc, nr);
        }
    return n;
}

void grid_step(grid_s *g)
{
    unsigned char *next = g->next;

    for (int row = 0; row < g->rows; row++)
        for (int col = 0; col < g->cols; col++)
        {
            int n = count_neighbors(g, col, row);
            if (CELL(g, col, row))
                next[row * g->cols + col] = (n == 2 || n == 3);
            else
                next[row * g->cols + col] = (n == 3);
        }

    g->next = g->current;
    g->current = next;
}

void grid_draw(const grid_s *g, render_callback_t render, void *data)
{
    if (!render) return;
    for (int row = 0; row < g->rows; row++)
        for (int col = 0; col < g->cols; col++)
            render(col, row, CELL(g, col, row), data);
}
