/**
 @file main.c
 @brief Run the game loop. The grid renderer is ncurses today.
 */
#include <stdlib.h>

#include "game.h"
#include "ncurses.h"

int main(void)
{
    if (ncurses_initialization() != 0)
        return EXIT_FAILURE;

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
    ncurses_finalization();
    return EXIT_SUCCESS;
}
