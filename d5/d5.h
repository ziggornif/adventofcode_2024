#ifndef d5_H
#define d5_H

#include "../utils/file.h"
#include "../utils/free.h"
#include "linked_list.h"

struct RuleMap {
  int key;
  int rules[100];
  int last_index;
};

typedef struct RuleMap RuleMap;

void lines_updates(const char *input_order_file,
                   const char *input_updates_file);

#endif
