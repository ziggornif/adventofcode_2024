#include "d5.h"

#include <assert.h>
#include <stdio.h>

int main() {
  const char *input_order_test = "d5/input_order.txt";
  const char *input_updates_test = "d5/input_updates.txt";
  lines_updates(input_order_test, input_updates_test);
  return 0;
}
