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

void output_score(void)
{
    // SDL_Color color = {255, 255, 255, 255};
    // char buffer[16];
    // snprintf(buffer, sizeof(buffer), "%d", game.score);
    // gfx_gpu_text_s *score_text =
    //     gfx_gpu_text_render(game.renderer, game.font, buffer, color);

    // SDL_Rect dest_rect = {0, 0, game.text_score->rect.w * 2,
    //                       game.text_score->rect.h * 2};
    // SDL_RenderCopy(game.renderer, game.text_score->texture,
    //                NULL, &dest_rect/*&game.text_score->rect*/);

    // dest_rect = (SDL_Rect) {game.text_score->rect.w * 3, 0,
    //                         score_text->rect.w * 2, score_text->rect.h * 2};
    // SDL_RenderCopy(game.renderer, score_text->texture, NULL,
    //                &dest_rect/*&game.text_score->rect*/);
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
