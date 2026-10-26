/**
 @file main.c
 @brief Run the game loop. The renderer is selected by the makefile (-DNCURSES, -DSDL2, -DSFML, -DSDL3, or -DRAYLIB). NCURSES is the default.
 */
#include <stdlib.h>

#if defined(SDL2)
#include "sdl2/game.h"
#elif defined(SFML)
#include "sfml/game.h"
#elif defined(SDL3)
#include "sdl3/game.h"
#elif defined(RAYLIB)
#include "raylib/game.h"
#elif defined(NCURSES)
#include "ncurses/game.h"
#else
#include "ncurses/game.h"
#endif

int main(int argc, char *argv[])
{
    game_initialization();

    while (game.running)
    {
        game_input();
        if (game.update)
            game_update();
        if (game.output)
            game_output();
    }

    game_finalization();
    return EXIT_SUCCESS;
}
