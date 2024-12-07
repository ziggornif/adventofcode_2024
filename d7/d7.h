#ifndef d7_H
#define d7_H

#include <math.h>
#include <stdbool.h>
#include <stddef.h>

#include "../utils/file.h"
#include "../utils/free.h"

typedef long (*operation_t)(long, long);

long equations(const char* input);

#endif
