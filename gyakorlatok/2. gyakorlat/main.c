#include "matrix.h"
#include "stdio.h"

int main(int argc, char* argv[])
{
	float a[3][3] = 
    {
        { 1.0f, -2.0f,  3.0f},
        { 5.0f, -3.0f,  0.0f},
        {-2.0f,  1.0f, -4.0f}
    };
	float b[3][3];
	float c[3][3];

    init_zero_matrix(b);
    b[1][1] =  8.0f;
    b[2][0] = -3.0f;
    b[2][2] =  5.0f;

    print_matrix(a);
    print_matrix(b);
    
    add_matrices(a, b, c);

    print_matrix(c);

    init_identity_matrix(c);

    print_matrix(c);

    multiply_scalar(c, 2.0f);

    print_matrix(c);

    multiply_matrices(a, b, c);

    print_matrix(c);


    scale(c, 2.0f, 3.0f);
    print_matrix(c);


    shift(c, 1.0f, -1.0f);
    print_matrix(c);


    rotate(c, 45.0f);
    print_matrix(c);


    float point[3] = {1.0f, 2.0f, 1.0f};

    transform_point(c, point);

    printf("A pontok transzformacio utan: (%.4f, %.4f, %.4f)\n", point[0], point[1], point[2]);

	return 0;
}



