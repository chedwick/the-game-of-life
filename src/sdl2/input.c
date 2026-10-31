#include "input.h"

#include <SDL2/SDL.h>
#include "game.h"


void read_input_devices(void)
{
    while (SDL_PollEvent(&game.event))
    {
        switch (game.event.type)
        {
            case SDL_QUIT:
                game.mode = GOL_MODE_STOPPED;
                break;
            case SDL_KEYDOWN:
                switch (game.event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        if (game.mode == GOL_MODE_RUNNING)
                            game.mode = GOL_MODE_STOPPED;
                        else
                            game.mode = GOL_MODE_RUNNING;
                        break;
                    case SDLK_UP:
                        game.key = KEY_UP;
                        break;
                    case SDLK_DOWN:
                        game.key = KEY_DOWN;
                        break;
                    case SDLK_LEFT:
                        game.key = KEY_LEFT;
                        break;
                    case SDLK_RIGHT:
                        game.key = KEY_RIGHT;
                        break;
                    case SDLK_SPACE:
                        game.key = KEY_SPACE;
                        break;
                    case SDLK_RETURN:
                        if (game.mode == GOL_MODE_RUNNING)
                            game.mode = GOL_MODE_EDITING;
                        else
                            game.mode = GOL_MODE_RUNNING;
                        break;
                    default:
                        // No default case
                        break;
                }
                break;
            case SDL_KEYUP:
                break;
            default:
                // No default case
                break;
        }
    }
}
