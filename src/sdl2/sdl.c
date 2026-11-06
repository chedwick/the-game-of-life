#include "sdl.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define NEAREST_PIXEL_SAMPLING "0"
#define DISABLE_HIGH_DPI_SCALING "1"

int sdl_initialization(void)
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, NEAREST_PIXEL_SAMPLING);    
    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, DISABLE_HIGH_DPI_SCALING);

    int sdl_flags = SDL_INIT_EVERYTHING | SDL_INIT_GAMECONTROLLER;
    if (SDL_Init(sdl_flags) < 0)
    {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    int img_flags = IMG_INIT_PNG;
    if (!(IMG_Init(img_flags) & img_flags))
    {
        printf("IMG_Init failed: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    if (TTF_Init() < 0)
    {
        printf("TTF_Init failed: %s\n", TTF_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    return 0;
}

int sdl_finalization(void)
{
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}

SDL_Window* sdl_window_create(const char* title,
                              uint16_t height, uint16_t width)
{
    int window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI;
    SDL_Window *window = SDL_CreateWindow(title,
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          width, height,
                                          window_flags);
    if (window)
        return window;

    printf("Window creation failed: %s\n", SDL_GetError());
    return NULL;
}

void sdl_window_destroy(SDL_Window *window)
{
    if (window)
        SDL_DestroyWindow(window);
}

SDL_Renderer* sdl_renderer_create(SDL_Window* window)
{
    int renderer_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, renderer_flags);
    if (renderer)
        return renderer;

    printf("Renderer creation failed: %s\n", SDL_GetError());
    return NULL;
}

void sdl_renderer_destroy(SDL_Renderer *renderer)
{
    if (renderer)
        SDL_DestroyRenderer(renderer);
}

// Loads a font located next to the executable (e.g. build/font.otf).
TTF_Font* sdl_font_load(const char *filename, int size)
{
    char path[1024];
    char *base_path = SDL_GetBasePath();
    snprintf(path, sizeof(path), "%s%s", base_path ? base_path : "", filename);
    SDL_free(base_path);

    TTF_Font *font = TTF_OpenFont(path, size);
    if (font)
        return font;

    printf("Font loading failed (%s): %s\n", path, TTF_GetError());
    return NULL;
}

void sdl_font_destroy(TTF_Font *font)
{
    if (font)
        TTF_CloseFont(font);
}

// Renders text into a texture; rect receives its size (position 0, 0).
SDL_Texture* sdl_text_create(SDL_Renderer *renderer, TTF_Font *font,
                             const char *text, SDL_Color color,
                             SDL_Rect *rect)
{
    if (!renderer || !font || !text)
        return NULL;

    SDL_Surface *surface = TTF_RenderUTF8_Solid(font, text, color);
    if (!surface)
    {
        printf("Text rendering failed: %s\n", TTF_GetError());
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture && rect)
        *rect = (SDL_Rect) {0, 0, surface->w, surface->h};
    else if (!texture)
        printf("Text texture creation failed: %s\n", SDL_GetError());

    SDL_FreeSurface(surface);
    return texture;
}

void sdl_text_destroy(SDL_Texture *texture)
{
    if (texture)
        SDL_DestroyTexture(texture);
}
