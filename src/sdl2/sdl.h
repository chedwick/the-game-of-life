#pragma once

#include <stdint.h>
#include <SDL2/SDL.h>

int sdl_initialization(void);
int sdl_finalization(void);

SDL_Window* construct_gfx_sdl_window(char* window_title,
                                     uint16_t height, uint16_t width);
void destruct_gfx_sdl_window(SDL_Window *window);

SDL_Renderer* construct_gfx_sdl_renderer(SDL_Window* window);
void destruct_gfx_sdl_renderer(SDL_Renderer *renderer);
