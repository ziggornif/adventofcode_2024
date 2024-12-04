#include "d3.h"

#include <assert.h>
#include <stdio.h>

int main() {
  const char *file = "d3/input_test.txt";
  int resp1 = p1_mull(file);
  printf("Result p1: %d\n", resp1);
  // int resp2 = p2_mull(file);
  // printf("Result p2: %d\n", resp2);
  return 0;
}
