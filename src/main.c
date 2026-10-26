/**
 @file main.c
 @brief Run the game loop. The grid renderer is ncurses today.
 */
#include <stdlib.h>

#include "ncurses/game.h"

int main(void)
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
