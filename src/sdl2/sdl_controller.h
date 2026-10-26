#pragma once

#include <stddef.h>

#include <SDL2/SDL.h>

extern SDL_GameController *gGameController;

int sdl_initialize_controller();

void handle_controller_events(SDL_Event* event);
