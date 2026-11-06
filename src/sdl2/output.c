#include "output.h"
#include "game.h"

#include <SDL2/SDL.h>

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

    dest = game.text_menu_return_to_game_rect;
    dest.x = (WINDOW_WIDTH - dest.w) / 2;
    dest.y = TILE_HEIGHT * 18;
    SDL_RenderCopy(game.renderer, game.text_menu_return_to_game, NULL, &dest);

    dest = game.text_menu_set_unset_cell_rect;
    dest.x = (WINDOW_WIDTH - dest.w) / 2;
    dest.y = TILE_HEIGHT * 20;
    SDL_RenderCopy(game.renderer, game.text_menu_set_unset_cell, NULL, &dest);

    dest = game.text_menu_step_generation_rect;
    dest.x = (WINDOW_WIDTH - dest.w) / 2;
    dest.y = TILE_HEIGHT * 22;
    SDL_RenderCopy(game.renderer, game.text_menu_step_generation, NULL, &dest);

    dest = game.text_menu_clear_rect;
    dest.x = (WINDOW_WIDTH - dest.w) / 2;
    dest.y = TILE_HEIGHT * 24;
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
