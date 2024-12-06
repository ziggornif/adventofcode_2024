#include "d6.h"

#include <assert.h>
#include <stdio.h>

int main() {
  const char *file = "d6/input_test.txt";
  int resp1 = patrol(file, 0);
  printf("Result p1: %d\n", resp1);
  return 0;
}
