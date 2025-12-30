#include "mainmenu.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>

void mainmenu_init(MainMenu* menu, SDL_Renderer* renderer)
{
    menu->start.texture = IMG_LoadTexture(renderer, "assets/startButton.png");
    menu->settings.texture = IMG_LoadTexture(renderer, "assets/nastaveniButton.png");
    menu->quit.texture = IMG_LoadTexture(renderer, "assets/quitButton.png");

    if (!menu->start.texture || !menu->settings.texture || !menu->quit.texture)
    {
        printf("Chyba pri nacitani menu textur: %s\n", IMG_GetError());
    }

    menu->start.rect    = (SDL_Rect){ 358, 200, 500, 120 };
    menu->settings.rect = (SDL_Rect){ 358, 350, 500, 120 };
    menu->quit.rect     = (SDL_Rect){ 358, 500, 500, 120 };
}

void mainmenu_handle_event(MainMenu* menu, SDL_Event* event, int* running, GameState* gameState)
{
    if (event->type == SDL_MOUSEBUTTONDOWN &&
        event->button.button == SDL_BUTTON_LEFT)
    {
        SDL_Point mouse = { event->button.x, event->button.y };

        if (SDL_PointInRect(&mouse, &menu->start.rect))
        {
            *gameState = STATE_GAME;
        }
        else if (SDL_PointInRect(&mouse, &menu->settings.rect))
        {
            *gameState = STATE_SETTINGS;
        }
        else if (SDL_PointInRect(&mouse, &menu->quit.rect))
        {
            *running = 0;
        }
    }
}

void mainmenu_render(MainMenu* menu, SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, menu->start.texture, NULL, &menu->start.rect);
    SDL_RenderCopy(renderer, menu->settings.texture, NULL, &menu->settings.rect);
    SDL_RenderCopy(renderer, menu->quit.texture, NULL, &menu->quit.rect);
}

void mainmenu_free(MainMenu* menu)
{
    SDL_DestroyTexture(menu->start.texture);
    SDL_DestroyTexture(menu->settings.texture);
    SDL_DestroyTexture(menu->quit.texture);
}
