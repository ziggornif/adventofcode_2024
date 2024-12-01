#include "d1.h"

#include <stdio.h>
#include <stdlib.h>

void parse_line(const char *line, int *left, int *right) {
  sscanf(line, "%d   %d", left, right);
}

int comp(const void *a, const void *b) { 
  return (*(int *)a - *(int *)b); 
}

size_t count_lines(const char *path) {
  FILE *file = fopen(path, "r");
  if (!file) {
    fprintf(stderr, "File not found.\n");
    return 0;
  }

  size_t lines = 0;
  char buffer[32];
  while (fgets(buffer, sizeof(buffer), file)) {
    lines++;
  }

  fclose(file);
  return lines;
}

void parse_file(const char *path, int **left_arr, int **right_arr) {
  size_t size = count_lines(path);
  if (size == 0) {
    left_arr = NULL;
    right_arr = NULL;
    return;
  }

  FILE *file = fopen(path, "r");
  if (!file) {
    fprintf(stderr, "File not found.\n");
    return;
  }

  *left_arr = malloc(size * sizeof(int));
  *right_arr = malloc(size * sizeof(int));

  char line[32];
  size_t index = 0;
  while (fgets(line, sizeof(line), file) && index < size) {
    parse_line(line, &(*left_arr)[index], &(*right_arr)[index]);
    index++;
  }

  qsort(*left_arr, size, sizeof(int), comp);
  qsort(*right_arr, size, sizeof(int), comp);

  fclose(file);
}

int p1_distance(const char *file) {
  int *l_array = NULL;
  int *r_array = NULL;

  size_t count = count_lines(file);
  parse_file(file, &l_array, &r_array);

  int result = 0;
  for (size_t i = 0; i < count; i++) {
    result += abs(l_array[i] - r_array[i]);
  }

  free(l_array);
  free(r_array);

  return result;
}

int p2_similarity(const char *file) {
  int *l_array = NULL;
  int *r_array = NULL;

  size_t nb_lig = count_lines(file);
  parse_file(file, &l_array, &r_array);

  int result = 0;
  for (size_t i = 0; i < nb_lig; i++) {
    int count = 0;
    for (size_t j = 0; j < nb_lig; j++) {
      if (r_array[j] == l_array[i]) {
        count++;
      }
    }
    result += l_array[i] * count;
  }

  free(l_array);
  free(r_array);

  return result;
}