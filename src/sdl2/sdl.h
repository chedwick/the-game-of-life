#pragma once

#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int sdl_initialization(void);
int sdl_finalization(void);

SDL_Window* sdl_window_create(const char* title,
                              uint16_t height, uint16_t width);
void sdl_window_destroy(SDL_Window *window);

SDL_Renderer* sdl_renderer_create(SDL_Window* window);
void sdl_renderer_destroy(SDL_Renderer *renderer);

TTF_Font* sdl_font_load(const char *filename, int size);
void sdl_font_destroy(TTF_Font *font);

SDL_Texture* sdl_text_create(SDL_Renderer *renderer, TTF_Font *font,
                             const char *text, SDL_Color color,
                             SDL_Rect *rect);
void sdl_text_destroy(SDL_Texture *texture);
