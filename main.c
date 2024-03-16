#include "./conv2d.h"

int main()
{
  Matrix input = randn(4, 4);
  Matrix input2 = init(4, 4);
  Matrix kernel2 = init(3, 3);

  set_entries(2.0, &input2);
  set_entries(1.0, &kernel2);

  Matrix conv_result2 = conv2d(&input2, &kernel2);

  Matrix kernel = init(3, 3);
  float value[] = {0.3333, 0.3333, 0.3333, 0.3333, 0.3333, 0.3333, 0.3333, 0.3333, 0.3333};
  set_values(&kernel, value);

  print_matrix(&input2);
  print_matrix(&kernel2);
  print_matrix(&conv_result2);
  return 0;
}
