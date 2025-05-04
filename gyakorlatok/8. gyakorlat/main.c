// main.c
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "joint.h"

const int WIDTH = 800;
const int HEIGHT = 600;

int main() 
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Inga",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Joint pendulum;
    init_joint(&pendulum);

    Uint64 start_time = SDL_GetTicks64();
    bool running = true;
    SDL_Event event;

    while (running) 
    {
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT)
                running = false;
        }

        Uint64 current_time = SDL_GetTicks64();
        double elapsed_sec = (current_time - start_time) / 1000.0;

        animate_joint(&pendulum, elapsed_sec);

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        int cx = WIDTH / 2;
        int cy = 100;

        double len = 200;
        double angle = pendulum.rotation[0];
        int x2 = cx + (int)(len * sin(angle));
        int y2 = cy + (int)(len * cos(angle));

        SDL_SetRenderDrawColor(renderer, 200, 200, 255, 255);
        SDL_RenderDrawLine(renderer, cx, cy, x2, y2);
        SDL_Rect weight = { x2 - 10, y2 - 10, 20, 20 };
        SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
        SDL_RenderFillRect(renderer, &weight);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
