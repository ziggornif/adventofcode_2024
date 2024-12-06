#include "d5.h"

#include <assert.h>
#include <stdio.h>

int main() {
  const char *input_order_test = "d5/input_order_test.txt";
  const char *input_updates_test = "d5/input_updates_test.txt";
  int resp1 = p1_updates(input_order_test, input_updates_test);
  printf("Result p1: %d\n", resp1);
  return 0;
}
