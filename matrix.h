#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
  int nrow;
  int ncol;
} Shape;

typedef struct {
  char dtype[8];
} Dtype;

typedef struct {
  Shape shape;
  Dtype dtype;
  float *value;
} Matrix;

void is_dim_valid(int nrow, int ncol);
void is_success_allocate(Matrix *matrix);
void is_row_col_match(int ncol, int nrow);
void is_shape_match(Matrix *matrix1, Matrix *matrix2);
Matrix init(int nrow, int ncol);
void set_entries(float value, Matrix *matrix);
Matrix zeros(int nrow, int ncol);
Matrix ones(int nrow, int ncol);
double generate_random_normal(void);
Matrix randn(int nrow, int ncol);
Matrix transpose(Matrix *matrix);
Matrix multiplication(Matrix *matrix1, Matrix *matrix2);
Matrix addition(Matrix *matrix1, Matrix *matrix2);
Matrix substract(Matrix *matrix1, Matrix *matrix2);
Matrix scalar_mul(double k, Matrix *matrix1);
double mean(Matrix *matrix);
double variance(Matrix *matrix);
void print_matrix(Matrix *matrix);

#endif
