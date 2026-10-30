#include "game.h"
#include "sdl_controller.h"

#include <stdbool.h>
#include <SDL2/SDL.h>

void pool_events(void)
{
    // Poll events
    while (SDL_PollEvent(&game.event))
    {
        handle_controller_events(&game.event);
        switch (game.event.type)
        {
            case SDL_QUIT:
                game.mode = GAME_MODE_STOPPED;
                break;
                // Key pressed
            case SDL_KEYDOWN:
                switch (game.event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        if (game.mode == GAME_MODE_RUNNING)
                            game.mode = GAME_MODE_STOPPED;
                        else
                            game.mode = GAME_MODE_RUNNING;
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
                        break;
                    case SDLK_RETURN:
                        if (game.mode == GAME_MODE_RUNNING)
                            game.mode = GAME_MODE_EDITING;
                        else
                            game.mode = GAME_MODE_RUNNING;
                        break;
                    default:
                        // No default case
                        break;
                }
                break;
                // Key released
            case SDL_KEYUP:
                break;
            case SDL_CONTROLLERBUTTONDOWN:
            {
                game.key = KEY_UP;
                // Handle button presses
                switch (game.event.cbutton.button)
                {
                    case SDL_CONTROLLER_BUTTON_A:
                        game.key = KEY_UP;
                        printf("A button pressed\n");
                        break;
                    case SDL_CONTROLLER_BUTTON_START:
                        printf("Start button pressed\n");
                        break;
                    // ... handle other buttons (X, Y, B, etc.)
                    default:
                        // No default case
                        break;
                }
            } 
        }
    }
}
