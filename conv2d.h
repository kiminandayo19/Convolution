#include "./matrix.h"

#ifndef CONV2D_H
#define CONV2D_H

typedef struct {
  int width;
  int height;
} OutShape;

void is_valid_conv(Matrix *mat_in, Matrix *ker);
OutShape calculate_output_shape(int h_in, int w_in, Shape ker_size);
Matrix element_wise_mul(Matrix *A, Matrix *B);
Matrix conv2d(Matrix *mat_in, Matrix *ker);

#endif
