#ifndef PALETTA_H
#define PALETTA_H
#include "line.h"

#define MAX_COLORS 4

typedef struct 
{
    SDL_Rect rect;
    Color color;

} ColorButton;

void init_palette(ColorButton palette[]);

void draw_palette(SDL_Renderer* renderer, const ColorButton palette[], int count);

int handle_palette_click(const ColorButton palette[], int count, int x, int y, Color* selected);

#endif
