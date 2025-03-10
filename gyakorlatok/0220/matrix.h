#ifndef MATRIX_H
#define MATRIX_H

/**
 * Initializes all elements of the matrix to zero.
 */
void init_zero_matrix(float matrix[3][3]);

/**
 * Print the elements of the matrix.
 */
void print_matrix(const float matrix[3][3]);

/**
 * Add matrices.
 */
void add_matrices(const float a[3][3], const float b[3][3], float c[3][3]);



/**
 * Task 1.
 */
void init_identity_matrix(float matrix[3][3]);

/**
 * Task 2.
 */
void multiply_scalar(float matrix[3][3], float scalar);

/**
 * Task 3.
 */
void multiply_matrices(const float a[3][3], const float b[3][3], float c[3][3]);

/**
 * Task 4.
 */
void transform_point(const float matrix[3][3], float point[3]);

/**
 * Task 5a.
 */
void scale(float matrix[3][3], float scaleX, float scaleY);

/**
 * Task 5b.
 */
void shift(float matrix[3][3], float shiftX, float shiftY);

/**
 * Task 5c.
 */
void rotate(float matrix[3][3], float angle);


#endif // MATRIX_H

