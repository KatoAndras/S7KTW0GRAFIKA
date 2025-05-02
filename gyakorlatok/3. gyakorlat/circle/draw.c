#include "draw.h"
#include <stdio.h>
#include <math.h>

void draw_circle_outline(const Circle* circle, int segments)
{
    double angle_step = 2 * M_PI / segments;

    for (int i = 0; i < segments; ++i) 
    {
        double angle1 = i * angle_step;
        double angle2 = (i + 1) * angle_step;

        double x1 = circle->x + circle->radius * cos(angle1);
        double y1 = circle->y + circle->radius * sin(angle1);
        double x2 = circle->x + circle->radius * cos(angle2);
        double y2 = circle->y + circle->radius * sin(angle2);

        printf("Line: (%.2f, %.2f) -> (%.2f, %.2f)\n", x1, y1, x2, y2);
    }
}
