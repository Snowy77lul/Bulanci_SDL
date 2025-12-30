#pragma once
#include <SDL2/SDL.h>
#include "gamestate.h"

typedef struct
{
    SDL_Texture* texture;
    SDL_Rect rect;
} Button;

typedef struct
{
    Button start;
    Button settings;
    Button quit;
} MainMenu;

void mainmenu_init(MainMenu* menu, SDL_Renderer* renderer);
void mainmenu_handle_event(MainMenu* menu, SDL_Event* event, int* running, GameState* gameState);
void mainmenu_render(MainMenu* menu, SDL_Renderer* renderer);
void mainmenu_free(MainMenu* menu);
