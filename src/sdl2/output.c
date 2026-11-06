#include "output.h"
#include "game.h"

#include <SDL2/SDL.h>
// #include "gfx/gfx_font.h"

static void sdl_draw_rect(int col, int row, int r, int g, int b, int a);

void render_cell(int col, int row, int alive, void *data)
{
    (void) data; // Suppress unused parameter warning
    if (alive)
        sdl_draw_rect(col, row, 255, 0, 0, 255);
    // else
    //     sdl_draw_rect(row, col, 0, 0, 0, 255);
}

void render_cursor(int col, int row)
{
    sdl_draw_rect(col, row, 255, 128, 255, 255);
}

void render_menu(void)
{
    if (!game.text_menu)
        return;

    SDL_Rect dest = game.text_menu_rect;
    dest.x = (WINDOW_WIDTH - dest.w) / 2;
    dest.y = TILE_HEIGHT;
    SDL_RenderCopy(game.renderer, game.text_menu, NULL, &dest);
}

static void sdl_draw_rect(int col, int row, int r, int g, int b, int a)
{
    SDL_Rect rect = {
        col * TILE_WIDTH,
        row * TILE_HEIGHT,
        TILE_WIDTH,
        TILE_HEIGHT
    };
    SDL_SetRenderDrawColor(game.renderer, r, g, b, a);
    SDL_RenderFillRect(game.renderer, &rect);
}
