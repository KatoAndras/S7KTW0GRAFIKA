#include "circle.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
	Circle circle;
	double area;
	
	set_circle_data(&circle, 5, 10, 8, "cyan");
	area = calc_circle_area(&circle);
	printf("Circle area: %lf\n", area);
	
	draw_circle_outline(&circle, 36);

	return 0;
}
