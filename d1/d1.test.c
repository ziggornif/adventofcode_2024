#include <stdio.h>
#include <assert.h>
#include "d1.h"

int main() {
  const char *file = "d1/input.txt";
  int result = p1_distance(file);
  printf("Result p1: %d\n", result);
  return 0;
}
