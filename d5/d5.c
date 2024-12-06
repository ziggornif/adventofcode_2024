#include "d5.h"

int validate_line(int *line, int line_length, rules_node_t *rules_list,
                  int *mid_index) {
  int valid = 0;
  for (int i = 0; i < line_length; i++) {
    if (line[i] == -1) {
      *mid_index = (i - 1) / 2;
      break;
    }
    rule_item_t rule = {.key = line[i]};
    rules_node_t *found = find_rule(rules_list, rule);
    if (!found) continue;

    int_node_t *current = found->val.rules;
    while (current != NULL) {
      for (int k = i + 1; k < line_length; k++) {
        if (current->val == line[k]) {
          valid = 1;
          break;
        }
      }
      if (valid) {
        break;
      }
      current = current->next;
    }
  }
  if (valid == 0) {
    if (*mid_index == 0) {
      *mid_index = line_length / 2;
    }
    printf("Line is valid and mid is %d\n", *mid_index);
  }
  return valid;
}

int *reorder_line(int *line, int line_length, rules_node_t *rules_list) {
  for (int i = 0; i < line_length; i++) {
    if (line[i] == -1) {
      break;
    }
    rule_item_t rule = {.key = line[i]};
    rules_node_t *found = find_rule(rules_list, rule);
    if (!found) continue;

    int_node_t *current = found->val.rules;
    while (current != NULL) {
      for (int k = i + 1; k < line_length; k++) {
        if (current->val == line[k]) {
          int tmp = line[i];
          line[i] = line[k];
          line[k] = tmp;
          break;
        }
      }
      current = current->next;
    }
  }
  return line;
}

void lines_updates(const char *input_order_file,
                   const char *input_updates_file) {
  size_t order_size = 0;
  size_t updates_size = 0;
  char **order_array = parse_file(input_order_file, &order_size);
  if (!order_array) {
    fprintf(stderr, "Failed to parse input_order_file.\n");
    return;
  }

  char **updates_array = parse_file(input_updates_file, &updates_size);
  if (!updates_array) {
    fprintf(stderr, "Failed to parse input_order_file.\n");
    return;
  };

  int updates_length = 23;
  int rules[order_size][2];
  int updates[updates_size][updates_length];

  for (size_t order_cpt = 0; order_cpt < order_size; order_cpt++) {
    int left = 0;
    int right = 0;
    sscanf(order_array[order_cpt], "%d|%d", &left, &right);
    rules[order_cpt][0] = left;
    rules[order_cpt][1] = right;
  }

  for (size_t update_cpt = 0; update_cpt < updates_size; update_cpt++) {
    char *pt;
    pt = strtok(updates_array[update_cpt], ",");
    int count = 0;
    for (int i = 0; i < updates_length; i++) {
      updates[update_cpt][i] = -1;
    }
    while (pt != NULL) {
      int a = atoi(pt);
      updates[update_cpt][count] = a;
      pt = strtok(NULL, ",");
      count++;
    }
  }

  rule_item_t rule = {};
  rules_node_t *rules_list = new_rules_list(rule);
  for (size_t i = 0; i < order_size; i++) {
    rule_item_t rule;
    rule.key = rules[i][1];

    rule.rules = new_list(rules[i][0]);

    for (size_t j = i + 1; j < order_size; j++) {
      if (rule.key == rules[j][1]) {
        push(rule.rules, rules[j][0]);
      }
    }
    push_rule(rules_list, rule);
  }
  pop_rule(&rules_list);

  int result = 0;
  int invalid_res = 0;
  for (size_t i = 0; i < updates_size; i++) {
    int mid_index = 0;
    int valid =
        validate_line(updates[i], updates_length, rules_list, &mid_index);
    if (valid == 0) {
      result += updates[i][mid_index];
    } else {
      printf("Line is invalid let's reorder: %zu\n", i);
      int *reordered_line = NULL;
      reordered_line = reorder_line(updates[i], updates_length, rules_list);
      while (validate_line(reordered_line, updates_length, rules_list,
                           &mid_index) == 1) {
        reordered_line =
            reorder_line(reordered_line, updates_length, rules_list);
      }
      invalid_res += reordered_line[mid_index];
    }
  }
  printf("P1 Result : %d\nP2 Result: %d\n", result, invalid_res);
}