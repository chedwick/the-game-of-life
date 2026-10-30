#include <stdlib.h>

#if defined(SDL2)
#include "sdl2/game.h"
#elif defined(SDL3)
#include "sdl3/game.h"
#elif defined(SFML)
#include "sfml/game.h"
#elif defined(RAYLIB)
#include "raylib/game.h"
#elif defined(NCURSES)
#include "ncurses/game.h"
#else
#include "ncurses/game.h"
#endif

int main(int argc, char *argv[])
{
    initialization();

    while (game.mode)
    {
        input();
        if (game.update)
            update();
        if (game.output)
            output();
        pacing();
    }

    finalization();
    return EXIT_SUCCESS;
}
