#include "game.h"

#include "sdl.h"

int initialize_window(void)
{
    SDL_Window *window = construct_gfx_sdl_window(TITLE,
                                                  GRID_HEIGHT * ZOOM,
                                                  GRID_WIDTH * ZOOM);
    if (!window)
    {
        return 1;
    }    
    
    game.window = window;   
    return 0;
}

int initialize_renderer(void)
{
    SDL_Renderer *renderer = construct_gfx_sdl_renderer(game.window);
    if (!renderer)
    {
        return 1;
    }    
    
    game.renderer = renderer;   
    return 0;
}


// int initialize_fonts(void)
// {
//     gfx_font_s *font = construct_gfx_font("assets/gabs_pixel.ttf");
//     if (font)
//     {
//         SDL_Color color = {255, 255, 255, 255};
//         gfx_gpu_text_s *text_score =
//             gfx_gpu_text_render(game.renderer, font, "SCORE", color);
//         game.font = font;
//         game.text_score = text_score;
//     }
//     return 0;
// }
