#ifndef LINE_H
#define LINE_H
#include <SDL2/SDL.h>

typedef struct 
{
    Uint8 r, g, b;
} Color;

typedef struct 
{
    int x1, y1;
    int x2, y2;
    Color color;
} Line;

void draw_line(SDL_Renderer* renderer, const Line* line);

#endif // LINE_H
