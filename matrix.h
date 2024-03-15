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

#endif
