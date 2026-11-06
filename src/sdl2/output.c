#include "output.h"
#include "game.h"

#include <SDL2/SDL.h>

static void sdl_draw_rect(int col, int row, int r, int g, int b, int a);

void render_cell(int col, int row, int alive, void *data)
{
    (void) data; // Suppress unused parameter warning
    if (alive)
    {
        SDL_Color c = COLOR_CELL;
        sdl_draw_rect(col, row, c.r, c.g, c.b, c.a);
    }
    // else
    //     sdl_draw_rect(row, col, 0, 0, 0, 255);
}

void render_cursor(int col, int row)
{
    sdl_draw_rect(col, row, 255, 128, 255, 255);
}

void render_menu(void)
{
    SDL_Rect sized[] = {
        game.text_menu_rect,
        game.text_menu_escape_rect,
        game.text_menu_return_to_game_rect,
        game.text_menu_space_rect,
        game.text_menu_randomize_rect,
        game.text_menu_step_rect,
        game.text_menu_clear_rect,
        game.text_menu_quit_rect
    };
    int max_w = 0;
    int text_h = 0;
    for (int i = 0; i < (int) (sizeof sized / sizeof sized[0]); i++)
    {
        if (sized[i].w > max_w)
            max_w = sized[i].w;
        if (sized[i].h > text_h)
            text_h = sized[i].h;
    }

    int pad = TILE_HEIGHT / 2;
    int top = TILE_HEIGHT;
    int bottom = TILE_HEIGHT * 22 + text_h;
    SDL_Rect panel = {
        (WINDOW_WIDTH - max_w) / 2 - pad,
        top - pad,
        max_w + pad * 2,
        (bottom - top) + pad * 2
    };
    SDL_SetRenderDrawBlendMode(game.renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, (Uint8) (255 * 60 / 100));
    SDL_RenderFillRect(game.renderer, &panel);
    SDL_SetRenderDrawBlendMode(game.renderer, SDL_BLENDMODE_NONE);

    SDL_Rect dest = game.text_menu_rect;
    dest.x = (WINDOW_WIDTH - dest.w) / 2;
    dest.y = TILE_HEIGHT;
    SDL_RenderCopy(game.renderer, game.text_menu, NULL, &dest);

    dest = game.text_menu_escape_rect;
    dest.x = (WINDOW_WIDTH - dest.w) / 2;
    dest.y = TILE_HEIGHT * 4;
    SDL_RenderCopy(game.renderer, game.text_menu_escape, NULL, &dest);

    dest = game.text_menu_return_to_game_rect;
    dest.x = (WINDOW_WIDTH - dest.w) / 2;
    dest.y = TILE_HEIGHT * 6;
    SDL_RenderCopy(game.renderer, game.text_menu_return_to_game, NULL, &dest);

    dest = game.text_menu_space_rect;
    dest.x = (WINDOW_WIDTH - dest.w) / 2;
    dest.y = TILE_HEIGHT * 8;
    SDL_RenderCopy(game.renderer, game.text_menu_space, NULL, &dest);

    dest = game.text_menu_randomize_rect;
    dest.x = (WINDOW_WIDTH - dest.w) / 2;
    dest.y = TILE_HEIGHT * 10;
    SDL_RenderCopy(game.renderer, game.text_menu_randomize, NULL, &dest);

    dest = game.text_menu_step_rect;
    dest.x = (WINDOW_WIDTH - dest.w) / 2;
    dest.y = TILE_HEIGHT * 12;
    SDL_RenderCopy(game.renderer, game.text_menu_step, NULL, &dest);

    dest = game.text_menu_clear_rect;
    dest.x = (WINDOW_WIDTH - dest.w) / 2;
    dest.y = TILE_HEIGHT * 14;
    SDL_RenderCopy(game.renderer, game.text_menu_clear, NULL, &dest);

    dest = game.text_menu_quit_rect;
    dest.x = (WINDOW_WIDTH - dest.w) / 2;
    dest.y = TILE_HEIGHT * 16;
    SDL_RenderCopy(game.renderer, game.text_menu_quit, NULL, &dest);
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
