#ifndef linkedlist_H
#define linkedlist_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct int_node {
  int val;
  struct int_node* next;
} int_node_t;

typedef struct rule_item {
  int key;
  int_node_t* rules;
} rule_item_t;

typedef struct rules_node {
  rule_item_t val;
  struct rules_node* next;
} rules_node_t;

int_node_t* new_list(int val);
void print_list(int_node_t* head);
void push(int_node_t* head, int val);
int_node_t* find(int_node_t* head, int val);
void pop(int_node_t** node);

rules_node_t* new_rules_list(rule_item_t val);
void print_rules_list(rules_node_t* head);
void push_rule(rules_node_t* head, rule_item_t val);
rules_node_t* find_rule(rules_node_t* head, rule_item_t val);
void pop_rule(rules_node_t** node);

#endif
