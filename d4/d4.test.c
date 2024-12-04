#include "d4.h"

#include <assert.h>
#include <stdio.h>

int main() {
  const char *file = "d4/input.txt";
  int resp1 = p1_find_xmas(file);
  printf("Result p1: %d\n", resp1);
  int resp2 = p2_find_x_mas(file);
  printf("Result p2: %d\n", resp2);
  return 0;
}
