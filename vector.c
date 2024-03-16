#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/vector.h"

Vector initialize_vector(int length, const char* dtype)
{
  if (length <= 0) {
    printf("Length must be greater than 0");
    exit(1);
  }

  Vector vector;
  vector.shape.nrow = length;
  vector.shape.ncol = 1;
  strcpy(vector.dtype.dtype, dtype);

  /* Allocate memory for initialize array */
  vector.value = (float*)malloc(length * sizeof(float));
  if(vector.value == NULL) {
    printf("Failed to allocate memory");
    exit(1);
  }

  return vector;
}

Vector zeros(int length)
{
  Vector vector = initialize_vector(length, "float");
  for (int i=0; i<length; i++)
    vector.value[i] = 0.0;
  return vector;
}

Vector ones(int length)
{
  Vector vector = initialize_vector(length, "float");
  for (int i=0; i<length; i++)
    vector.value[i] = 1.0;
  return vector;
}

Vector add(Vector *vector1, Vector *vector2)
{
  if (vector1->shape.nrow != vector2->shape.nrow) {
    printf("Mismatch dim for vector 1 and vector 2");
    exit(1);
  }
  
  Vector vector = initialize_vector(vector1->shape.nrow, "float");
  for (int i=0; i<vector.shape.nrow; i++)
    vector.value[i] = vector1->value[i] + vector2->value[i];
  return vector;
}

Vector substract(Vector *vector1, Vector *vector2)
{
  if (vector1->shape.nrow != vector2->shape.nrow) {
    printf("Mismatch dim between vector 1 and vector 2");
    exit(1);
  }

  Vector vector = initialize_vector(vector1->shape.nrow, "float");
  for (int i=0; i<vector.shape.nrow; i++)
    vector.value[i] = vector1->value[i] - vector2->value[i];
  return vector;
}

float dot_product(Vector *vector1, Vector *vector2)
{
  if (vector1->shape.nrow != vector2->shape.nrow) {
    printf("Mismatch dim between vector 1 and vector 2");
    exit(1);
  }

  float result = 0.0;
  for (int i=0; i<vector1->shape.nrow; i++)
    result = result + (vector1->value[i] * vector2->value[i]);
  return result;
}

Vector element_wise(Vector *vector1, Vector *vector2)
{
  if (vector1->shape.nrow != vector2->shape.nrow) {
    printf("Mismatch dim between vector 1 and vector 2");
    exit(1);
  }

  Vector vector = initialize_vector(vector1->shape.nrow, "float");
  for (int i=0; i<vector.shape.nrow; i++)
    vector.value[i] = vector1->value[i] * vector2->value[i];
  return vector;
}
