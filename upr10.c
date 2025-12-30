#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "mainmenu.h"
#include "gamestate.h"


int main(int argc, char* argv[])
{
    // ================= INIT =================
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow(
        "Bulanic",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1216, 800,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    // ================= GAME STATE =================
    int running = 1;
    GameState gameState = STATE_MENU;

    // ================= MENU =================
    MainMenu menu;
    mainmenu_init(&menu, renderer);

    // ================= GAME ASSETS =================
    SDL_Texture* BG_BACK  = IMG_LoadTexture(renderer, "assets/MapBG.png");
    SDL_Texture* BG_FRONT = IMG_LoadTexture(renderer, "assets/MapBGFront.png");



    // ================= TIME =================
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;

    SDL_Event event;

    // ================= GAME LOOP =================
    while (running)
    {
        // ---------- INPUT ----------
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;

            if (gameState == STATE_MENU)
            {
                mainmenu_handle_event(&menu, &event, &running, &gameState);
            }
            else if (gameState == STATE_GAME)
            {
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                {
                    gameState = STATE_MENU;
                }
            }
        }

        // ---------- UPDATE ----------
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        double deltaTime = (double)(NOW - LAST) / SDL_GetPerformanceFrequency();
        (void)deltaTime; // zatím nevyužito

        // ---------- RENDER ----------
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (gameState == STATE_MENU)
        {
            mainmenu_render(&menu, renderer);
        }
        else if (gameState == STATE_GAME)
        {
            // BACKGROUND
            SDL_RenderCopy(renderer, BG_BACK, NULL, NULL);

            // TODO: hráč, NPC, objekty

            // FRONT
            SDL_RenderCopy(renderer, BG_FRONT, NULL, NULL);
        }
        else if (gameState == STATE_SETTINGS)
        {
            // TODO: settings menu
        }

        SDL_RenderPresent(renderer);
    }

    // ================= CLEANUP =================
    mainmenu_free(&menu);

    SDL_DestroyTexture(BG_BACK);
    SDL_DestroyTexture(BG_FRONT);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return 0;
}
