#include "d7.h"

#include <assert.h>
#include <stdio.h>

int main() {
  const char *file = "d7/input_test.txt";
  long resp1 = equations(file);
  printf("Result p1: %ld\n", resp1);
  return 0;
}
