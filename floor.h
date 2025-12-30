#pragma once
#include <SDL2/SDL_image.h>
typedef struct
{
    SDL_Texture* image;
    int height;
} Floor;

void floor_init(Floor* floor, SDL_Texture* image, int height);
void floor_draw(Floor*, SDL_Renderer* renderer);
void floor_free(Floor* floor);