#include "line.h"

void draw_line(SDL_Renderer* renderer, const Line* line) 
{
    SDL_SetRenderDrawColor(renderer, line->color.r, line->color.g, line->color.b, 100);

    SDL_RenderDrawLine(renderer, line->x1, line->y1, line->x2, line->y2);
}
