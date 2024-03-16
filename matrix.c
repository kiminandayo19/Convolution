#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "./matrix.h"

void is_dim_valid(int nrow, int ncol)
{
  if (nrow <= 0 || ncol <= 0) {
    printf("Invalid row or col. Must be greater than 0\n");
    exit(1);
  }
}

void is_success_allocate(Matrix *matrix)
{
  if (matrix->value == NULL) {
    printf("Failed to allocate memory\n");
    exit(1);
  }
}

void is_row_col_match(int ncol, int nrow) {
  if (nrow != ncol) {
    printf("Row doesn't match col\n");
    exit(1);
  }
}

void is_shape_match(Matrix *matrix1, Matrix *matrix2)
{
  if (matrix1->shape.nrow != matrix2->shape.nrow && matrix1->shape.ncol != matrix2->shape.ncol) {
    printf("Shape doesn't match\n");
    exit(1);
  }
}

Matrix init(int nrow, int ncol)
{
  is_dim_valid(nrow, ncol);
  Matrix matrix;
  matrix.shape.nrow = nrow;
  matrix.shape.ncol = ncol;
  strcpy(matrix.dtype.dtype, "float");
  matrix.value = (float*)malloc(nrow * ncol * sizeof(float));
  is_success_allocate(&matrix);
  return matrix;
}

void set_entries(float value, Matrix *matrix)
{
  for (int i=0; i<matrix->shape.nrow * matrix->shape.ncol; i++)
    matrix->value[i] = value;
}

void set_values(Matrix *matrix, float *values)
{
  for (int i=0; i<matrix->shape.nrow * matrix->shape.ncol; i++)
    matrix->value[i] = values[i];
}

Matrix zeros(int nrow, int ncol) 
{
  Matrix matrix = init(nrow, ncol);
  set_entries(0.0, &matrix);
  return matrix;
}

Matrix ones(int nrow, int ncol)
{
  Matrix matrix = init(nrow, ncol);
  set_entries(1.0, &matrix);
  return matrix;
}

double generate_random_normal(void)
{
  static double z0, z1;
  static int generate;
  double mean = 0.0;
  double stdev = 1.0;
  generate = !generate;

  if (!generate)
    return z1 * stdev + mean;

  double u1, u2;
  do {
    u1 = rand() * (1.0 / RAND_MAX);
    u2 = rand() * (1.0 / RAND_MAX);
  } while (u1 <= 1e-7);

  double R = sqrt(-2.0 * log(u1));
  double theta = 2.0 * M_PI * u2;
  z0 = R * cos(theta);
  z1 = R * sin(theta);
  return z0 * stdev + mean;
}

Matrix randn(int nrow, int ncol)
{
  Matrix matrix = init(nrow, ncol);
  for (int i=0; i<nrow * ncol; i++)
    matrix.value[i] = generate_random_normal();
  return matrix;
}

Matrix transpose(Matrix *matrix)
{
  Matrix result = init(matrix->shape.nrow, matrix->shape.ncol);
  for (int i=0; i<matrix->shape.nrow; i++) {
    for (int j=0; j<matrix->shape.ncol; j++) {
      float temp = matrix->value[i * matrix->shape.ncol + j];
      result.value[i * matrix->shape.ncol + j] = matrix->value[j * matrix->shape.nrow + i];
      result.value[j * matrix->shape.nrow + i] = temp;
    }
  }
  return result;
}

Matrix multiplication(Matrix *matrix1, Matrix *matrix2)
{
  is_row_col_match(matrix1->shape.ncol, matrix2->shape.nrow);
  Matrix matrix = init(matrix1->shape.nrow, matrix2->shape.ncol);

  for (int i=0; i<matrix.shape.nrow; i++) {
    for (int j=0; j<matrix.shape.ncol; j++) {
      float sum = 0.0;
      for (int k=0; k<matrix1->shape.ncol; k++) {
        sum += matrix1->value[i * matrix1->shape.ncol + k] * matrix2->value[k * matrix2->shape.ncol + j];
      }
      matrix.value[i * matrix.shape.ncol + j] = sum;
    }
  }
  return matrix;
}

Matrix addition(Matrix *matrix1, Matrix *matrix2)
{
  is_shape_match(matrix1, matrix2);
  Matrix matrix = init(matrix1->shape.nrow, matrix1->shape.ncol);
  for (int i=0; i<matrix.shape.nrow * matrix.shape.ncol; i++)
    matrix.value[i] = matrix1->value[i] + matrix2->value[i];
  return matrix;
}

Matrix substract(Matrix *matrix1, Matrix *matrix2)
{
  is_shape_match(matrix1, matrix2);
  Matrix matrix = init(matrix1->shape.nrow, matrix1->shape.ncol);
  for (int i=0; i<matrix.shape.nrow * matrix.shape.ncol; i++)
    matrix.value[i] = matrix1->value[i] - matrix2->value[i];
  return matrix;
}

Matrix scalar_mul(double k, Matrix *matrix1)
{
  Matrix matrix = init(matrix1->shape.nrow, matrix1->shape.ncol);
  for (int i=0; i<matrix.shape.nrow * matrix.shape.ncol; i++)
    matrix.value[i] = k * matrix1->value[i];
  return matrix;
}

double sum_mat_value(Matrix *matrix)
{
  double sum = 0.0;
  for (int i=0; i<matrix->shape.nrow * matrix->shape.ncol; i++)
    sum += matrix->value[i];
  return sum;
}

double mean(Matrix *matrix)
{
  double sum = sum_mat_value(matrix);
  return sum / (matrix->shape.nrow * matrix->shape.ncol);
}

double variance(Matrix *matrix)
{
  double sum = 0.0;
  double mu = mean(matrix);
  for (int i=0; i<matrix->shape.nrow * matrix->shape.ncol; i++)
    sum += (matrix->value[i] - mu) * (matrix->value[i] - mu);
  return sum / ((matrix->shape.nrow * matrix->shape.ncol) - 1);
}

void print_matrix(Matrix *matrix)
{
  printf("[");
  for (int i=0; i<matrix->shape.nrow; i++) {
    printf("[");
    for (int j=0; j<matrix->shape.ncol; j++) {
      if (j == matrix->shape.ncol - 1) {
        printf("%1.4f ", matrix->value[i * matrix->shape.ncol + j]);
      } else {
        printf("%1.4f, ", matrix->value[i * matrix->shape.ncol + j]);
      }
    }
    printf(i == matrix->shape.nrow - 1 ? "]" : "]\n");
  }
  printf("]\n");
  printf("\n");
}

// int main()
// {
//   srand(time(NULL));
//   Matrix one = ones(3, 2);
//   Matrix mat1 = randn(2, 2);
//   Matrix mat2 = randn(2, 2);
//   Matrix mat3 = multiplication(&mat1, &mat2);
//   print_matrix(&one);
//   print_matrix(&mat1);
//   print_matrix(&mat2);
//   print_matrix(&mat3);
//   
//   return 0;
// }


