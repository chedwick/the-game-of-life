// implementation file for game of life
#include "gol.h"

#include <stdlib.h>
#include <string.h>

#define CELL(b, x, y) ((b)->current[(y) * (b)->width + (x)])

/*
The universe **wraps** (it's a torus), so corner cells have 8 neighbors, not 3.

This happens in `count_neighbors`:

```c
int nx = (x + dx + g->width) % g->width;
int ny = (y + dy + g->height) % g->height;
```

Adding `g->width` / `g->height` before the modulo keeps the value non-negative when `x + dx` is `-1`, because C's `%` can return negative results. So:

- For the cell at (0, 0), the neighbor at `dx = -1` maps to `x = width - 1`, the right edge.
- The neighbor at `dy = -1` maps to `y = height - 1`, the bottom edge.
- The diagonal neighbor of the top-left corner is the bottom-right corner cell.

Every cell, including edges and corners, therefore checks all 8 surrounding positions.

If you want a hard-edged universe instead (corners with 3 neighbors, edges with 5), replace those two lines with a bounds check that skips out-of-range positions:

```c
int nx = x + dx, ny = y + dy;
if (nx < 0 || nx >= g->width || ny < 0 || ny >= g->height) continue;
```

One edge case with wrapping: if the width or height is 1 or 2, a cell can count the same neighbor more than once, or count itself. That doesn't matter for normal board sizes.
*/
grid_s *grid_create(int width, int height)
{
    grid_s *g = malloc(sizeof *g);
    if (!g) return NULL;
    g->width = width;
    g->height = height;
    size_t size = (size_t) width * height;
    // one allocation holds both buffers: buffer0 in the first half,
    // buffer1 in the second half.
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
    for (int i = 0; i < g->width * g->height; i++)
    {
        g->current[i] = (rand() % 100) < percent_alive;
    }
}

void toggle_cell(grid_s *g, int x, int y)
{
    if (x < 0 || x >= g->width || y < 0 || y >= g->height) return;
    CELL(g, x, y) ^= 1;
}

void grid_clear(grid_s *g)
{
    memset(g->current, 0, (size_t) g->width * g->height);
}

static int count_neighbors(const grid_s *g, int x, int y)
{
    int n = 0;
    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            if (dx == 0 && dy == 0) continue;
            int nx = (x + dx + g->width) % g->width;
            int ny = (y + dy + g->height) % g->height;
            n += CELL(g, nx, ny);
        }
    }
    return n;
}

void grid_step(grid_s *g)
{
    unsigned char *next = g->next;

    for (int y = 0; y < g->height; y++)
    {
        for (int x = 0; x < g->width; x++)
        {
            int n = count_neighbors(g, x, y);
            if (CELL(g, x, y)) {
                next[y * g->width + x] = (n == 2 || n == 3);
            } else {
                next[y * g->width + x] = (n == 3);
            }
        }
    }

    g->next = g->current;
    g->current = next;
}

void grid_draw(const grid_s *g, render_callback_t cb, void *userdata)
{
    if (!cb) return;
    for (int y = 0; y < g->height; y++)
    {
        for (int x = 0; x < g->width; x++)
        {
            cb(x, y, CELL(g, x, y), userdata);
        }
    }
}
