#include "matrix.h"

#include <stdio.h>
#include <math.h>
#include <corecrt_math_defines.h>



void init_zero_matrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) 
    {
        for (j = 0; j < 3; ++j) 
        {
            matrix[i][j] = 0.0;
        }
    }
}

void print_matrix(const float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) 
    {
        for (j = 0; j < 3; ++j) 
        {
            printf("%4.4f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void add_matrices(const float a[3][3], const float b[3][3], float c[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) 
    {
        for (j = 0; j < 3; ++j) 
        {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

// 1.Egységmátrix
void init_identity_matrix(float matrix[3][3])
{
    for (int i = 0; i < 3; ++i) 
    {
        for (int j = 0; j < 3; ++j) 
        {
            matrix[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

// 2.Skalárszorzás
void multiply_scalar(float matrix[3][3], float scalar)
{
    for (int i = 0; i < 3; ++i) 
    {
        for (int j = 0; j < 3; ++j) 
        {
            matrix[i][j] *= scalar;
        }
    }
}

// 3.Mátrixszorzás
void multiply_matrices(const float a[3][3], const float b[3][3], float c[3][3])
{
    for (int i = 0; i < 3; ++i) 
    {
        for (int j = 0; j < 3; ++j) 
        {
            c[i][j] = 0.0f;
            for (int k = 0; k < 3; ++k) 
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

// 4.Ponttranszformáció
void transform_point(const float matrix[3][3], float point[3])
{
    float result[3] = {0.0f, 0.0f, 0.0f};
    for (int i = 0; i < 3; ++i) 
    {
        for (int j = 0; j < 3; ++j) 
        {
            result[i] += matrix[i][j] * point[j];
        }
    }
    for (int i = 0; i < 3; ++i) 
    {
        point[i] = result[i];
    }
}

// 5.Scaling
void scale(float matrix[3][3], float scaleX, float scaleY)
{
    float scaleMatrix[3][3] = 
    {
        {scaleX, 0.0f, 0.0f},
        {0.0f, scaleY, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };

    multiply_matrices(matrix, scaleMatrix, matrix);
}

// 6.Eltolás)
void shift(float matrix[3][3], float shiftX, float shiftY)
{
    float shiftMatrix[3][3] = 
    {
        {1.0f, 0.0f, shiftX},
        {0.0f, 1.0f, shiftY},
        {0.0f, 0.0f, 1.0f}
    };

    multiply_matrices(matrix, shiftMatrix, matrix);
}

// 7.Forgatás
void rotate(float matrix[3][3], float angle)
{
    float rad = angle * M_PI / 180.0f;
    float rotateMatrix[3][3] = 
    {
        {cos(rad), -sin(rad), 0.0f},
        {sin(rad), cos(rad), 0.0f},
        {0.0f, 0.0f, 1.0f}
    };

    multiply_matrices(matrix, rotateMatrix, matrix);
}
