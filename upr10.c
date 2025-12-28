#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char* argv[])
{
    /* PRO CTENI ARGUMENTU V TERMINALU
    if (argc > 1)
    {
        for (int i = 1;i <argc; i++)
        printf("%s\n", argv[i]);
    }
    */

   // -lSDL2 do task.json
   // inicializace>
   SDL_Init(SDL_INIT_VIDEO); // | SDL_INIT_AUDIO); pro audio k videu
   IMG_Init(IMG_INIT_PNG);
   SDL_Window* Window = SDL_CreateWindow("Bulanic",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 1216, 800, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE); // pro kreace okna ||| (nazev okna), pozice, pozice, Rozmer, Rozmer, Visibilita
   SDL_Renderer* renderer = SDL_CreateRenderer(Window, -1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // jake okno? , monitor? -1 auto , nastaveni co renderuje GPU + VSYNC

   int quit = 0;

   SDL_Event event;


    int WindowWidth = 0;
    int WindowHeight = 0;
    SDL_GetWindowSize(Window,&WindowWidth,&WindowHeight); // nastavi window size

    WindowWidth--;
    WindowHeight--;

   //int no_rows = 10;

   SDL_Texture* Start_texture = IMG_LoadTexture(renderer,"startButton.png");

   while(!quit) // dokud nebude chtit odejit quit
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT: //krizek 
                {
                    quit = 1;
                    IMG_Quit();
                    break;
                }
            }
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    // case SDLK_m:
                    // {
                    //     no_rows++;
                    //     break;
                    // }
                    // case SDLK_l:
                    // {
                    //     if (no_rows > 0) no_rows--;
                    //     break;
                    // }
                    case SDLK_q: //off btn
                    {
                        quit = 1;
                        IMG_Quit();
                    }
                } 
            }
            
        }
        SDL_SetRenderDrawColor(renderer, 127, 30, 220, SDL_ALPHA_OPAQUE); // nebo misto xxx ALPHA xxx = 255
        SDL_RenderClear(renderer);

        //start BUTTON ->
        int StartbtnW = 500;
        int StartbtnH = 250;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_Rect StartCtverec = {
            .x = (WindowWidth - StartbtnW) / 2,
            .y = (WindowHeight - StartbtnH) / 2,
            .w = StartbtnW,
            .h = StartbtnH
        };

        //SDL_RenderFillRect(renderer, &StartCtverec); fill rect
        // textura na start button
        SDL_RenderCopy(renderer, Start_texture, NULL, &StartCtverec);
        //SDL_DestroyTexture(Start_texture); 
        //v�dy uvolnit image po pou�it�

        // SDL_SetRenderDrawColor(renderer, 255,255,255,SDL_ALPHA_OPAQUE);
        // SDL_RenderDrawLine(renderer,0,0,width,height);
        
        // if(no_rows>0)
        // {
        //     int step =  height/no_rows;

        //     SDL_RenderDrawLine(renderer,0,height,width,0);

        //     for(int i=1;i<no_rows;i++)
        //     {
        //         SDL_RenderDrawLine(renderer,0,i*step,width,i*step);
                
        //     }
        // }

        SDL_RenderPresent(renderer);
        
    }
    SDL_DestroyTexture(Start_texture); 
    IMG_Quit();
    SDL_Quit();

    return 0;
}