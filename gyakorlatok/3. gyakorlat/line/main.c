#include <SDL2/SDL.h>
#include <stdio.h>
#include "line.h"
#include "paletta.h"

#define MAX_LINE_COUNT 100

int main(int argc, char* argv[]) 
{

    SDL_Window* window = SDL_CreateWindow("Szakasz", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Line lines[MAX_LINE_COUNT];
    int lineCount = 0;

    int clickState = 0;
    int tempX = 0, tempY = 0;

    Color currentColor = {255, 0, 0};

    ColorButton palette[MAX_COLORS];
    init_palette(palette);

    int running = 1;
    SDL_Event event;

    while (running) 
    {
        while (SDL_PollEvent(&event)) 
        {
            switch (event.type) 
            {
                case SDL_QUIT:
                    running = 0;
                    break;

                case SDL_MOUSEMOTION: 
                {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    printf("Egér: %d, %d\n", x, y);
                    break;
                }

                case SDL_MOUSEBUTTONDOWN: 
                {
                    int x = event.button.x;
                    int y = event.button.y;

                    if (handle_palette_click(palette, MAX_COLORS, x, y, &currentColor)) 
                    {
                        break;
                    }

                    if (y > 50) {
                        if (clickState == 0) 
                        {
                            tempX = x;
                            tempY = y;
                            clickState = 1;
                        } else 
                        {
                            if (lineCount < MAX_LINE_COUNT) 
                            {
                                lines[lineCount] = (Line){tempX, tempY, x, y, currentColor};
                                lineCount++;
                            }
                            clickState = 0;
                        }
                    }
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        draw_palette(renderer, palette, MAX_COLORS);

        for (int i = 0; i < lineCount; ++i) 
        {
            draw_line(renderer, &lines[i]);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
