#ifndef d6_H
#define d6_H

#include <stddef.h>

#include "../utils/file.h"
#include "../utils/free.h"

typedef struct guard_pos {
  int x;
  int y;
} guard_pos_t;

int patrol(const char *input_file, int debug);

#endif
