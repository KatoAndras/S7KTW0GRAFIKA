#include "paletta.h"

void init_palette(ColorButton palette[]) 
{
    palette[0] = (ColorButton){{10, 10, 30, 30}, {255, 0, 0}};
    palette[1] = (ColorButton){{50, 10, 30, 30}, {0, 255, 0}};
    palette[2] = (ColorButton){{90, 10, 30, 30}, {0, 0, 255}};
    palette[3] = (ColorButton){{130, 10, 30, 30}, {255, 255, 0}};
}

void draw_palette(SDL_Renderer* renderer, const ColorButton palette[], int count) 
{
    for (int i = 0; i < count; ++i) 
    {
        SDL_SetRenderDrawColor(renderer, palette[i].color.r, palette[i].color.g, palette[i].color.b, 255);
        SDL_RenderFillRect(renderer, &palette[i].rect);
    }
}

int handle_palette_click(const ColorButton palette[], int count, int x, int y, Color* selected) 
{
    for (int i = 0; i < count; ++i) 
    {
        SDL_Rect r = palette[i].rect;
        if (x >= r.x && x <= r.x + r.w && y >= r.y && y <= r.y + r.h) 
        {
            *selected = palette[i].color;
            return 1;
        }
    }
    return 0;
}
