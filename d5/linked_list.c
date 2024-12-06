#include "linked_list.h"

int_node_t* new_list(int val) {
  int_node_t* head = NULL;
  head = (int_node_t*)malloc(sizeof(int_node_t));
  if (head == NULL) {
    return NULL;
  }
  head->val = val;
  head->next = NULL;
  return head;
}

void print_list(int_node_t* head) {
  int_node_t* current = head;

  while (current != NULL) {
    printf("val %d\n", current->val);
    current = current->next;
  }
  printf("\n");
}

void push(int_node_t* head, int val) {
  int_node_t* current = head;
  if (current->val == val) {
    return;
  }

  while (current->next != NULL) {
    current = current->next;
    if (current->val == val) {
      return;
    }
  }

  current->next = (int_node_t*)malloc(sizeof(int_node_t));
  current->next->val = val;
  current->next->next = NULL;
}

int_node_t* find(int_node_t* head, int val) {
  int_node_t* current = head;
  if (current->val == val) {
    return current;
  }

  while (current->next != NULL) {
    current = current->next;
    if (current->val == val) {
      return current;
    }
  }
  return NULL;
}

void pop(int_node_t** node) {
  if (*node != NULL) {
    int_node_t* temp = *node;
    *node = (*node)->next;
    free(temp);
  }
}

rules_node_t* new_rules_list(rule_item_t val) {
  rules_node_t* head = NULL;
  head = (rules_node_t*)malloc(sizeof(rules_node_t));
  if (head == NULL) {
    return NULL;
  }
  head->val = val;
  head->next = NULL;
  return head;
}

void print_rule_items(rule_item_t* item) {
  printf("rule key %d\n", item->key);
  print_list(item->rules);
}

void print_rules_list(rules_node_t* head) {
  rules_node_t* current = head;

  while (current != NULL) {
    print_rule_items(&current->val);
    current = current->next;
  }
  printf("\n");
}

void push_rule(rules_node_t* head, rule_item_t val) {
  rules_node_t* current = head;
  if (current->val.key == val.key) {
    return;
  }

  while (current->next != NULL) {
    current = current->next;
    if (current->val.key == val.key) {
      return;
    }
  }

  current->next = (rules_node_t*)malloc(sizeof(rules_node_t));
  current->next->val = val;
  current->next->next = NULL;
}

rules_node_t* find_rule(rules_node_t* head, rule_item_t val) {
  rules_node_t* current = head;
  if (current->val.key == val.key) {
    return current;
  }

  while (current->next != NULL) {
    current = current->next;
    if (current->val.key == val.key) {
      return current;
    }
  }
  return NULL;
}

void pop_rule(rules_node_t** node) {
  if (*node != NULL) {
    rules_node_t* temp = *node;
    *node = (*node)->next;
    free(temp);
  }
}
