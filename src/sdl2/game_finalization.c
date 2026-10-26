#include "game.h"

#include "sdl.h"

int finalize_window(void)
{
    destruct_gfx_sdl_window(game.window);
    game.window = NULL;
    return 0;
}

int finalize_renderer(void)
{
    destruct_gfx_sdl_renderer(game.renderer);
    game.renderer = NULL;
    return 0;
}
