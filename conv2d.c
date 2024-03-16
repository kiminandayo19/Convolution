#include "./matrix.h"

typedef struct {
  int width;
  int height;
} OutShape;

void is_valid_conv(Matrix *mat_in, Matrix *ker)
{
  if (mat_in->shape.nrow < ker->shape.nrow ||
      mat_in->shape.ncol < ker->shape.ncol) {
    printf("Input shape must be greater or equal than kernel shape\n");
    exit(1);
  }
}

OutShape calculate_output_shape(int h_in, int w_in, Shape ker_size)
{
  /* Assumption used:
   * Padding = 0
   * Dilation = 1
   * Stride = 1 */
  OutShape shape;
  shape.width = floor((h_in + (2 * 0) - 1 * (ker_size.nrow - 1) - 1) + 1);
  shape.height = floor((w_in + (2 * 0) - 1 * (ker_size.ncol - 1) - 1) + 1);
  return shape;
}

Matrix element_wise_mul(Matrix *A, Matrix *B)
{
  is_shape_match(A, B);
  Matrix matrix = init(A->shape.nrow, A->shape.ncol);
  for (int i=0; i<matrix.shape.nrow * matrix.shape.ncol; i++)
    matrix.value[i] = A->value[i] * B->value[i];
  return matrix;
}

Matrix conv2d(Matrix *mat_in, Matrix *ker)
{
  is_valid_conv(mat_in, ker);
  OutShape ns = calculate_output_shape(mat_in->shape.nrow, mat_in->shape.ncol, ker->shape);
  Matrix matrix = init(ns.width, ns.height);

  for (int i=0; i<matrix.shape.nrow; i++) {
    for (int j=0; j<matrix.shape.ncol; j++) {
      for (int m=0; m<ker->shape.nrow; m++) {
        for (int n=0; n<ker->shape.ncol; n++) {
          int d_i = i * (1 + m) * 1;
          int d_j = j * (1 + n) * 1;
          int d_w = mat_in->shape.ncol;
          int d_h = mat_in->shape.nrow;
          matrix.value[i * matrix.shape.nrow + j] += mat_in->value[d_i * d_w + d_j] *\
                                                     ker->value[m * ker->shape.ncol + m];
        }
      }
    }
  }
  
  return matrix;
}
