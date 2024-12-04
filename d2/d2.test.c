#include "d2.h"

#include <assert.h>
#include <stdio.h>

int main() {
  const char *file = "d2/input_test.txt";
  int resp1 = p1_safe_reports(file);
  printf("Result p1: %d\n", resp1);
  int resp2 = p2_safe_reports(file);
  printf("Result p2: %d\n", resp2);
  return 0;
}
