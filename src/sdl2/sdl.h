#pragma once

#include <stdint.h>
#include <SDL2/SDL.h>

int sdl_initialization(void);
int sdl_finalization(void);

SDL_Window* sdl_window_create(char* window_title,
                                     uint16_t height, uint16_t width);
void sdl_window_destroy(SDL_Window *window);

SDL_Renderer* sdl_renderer_create(SDL_Window* window);
void sdl_renderer_destroy(SDL_Renderer *renderer);
