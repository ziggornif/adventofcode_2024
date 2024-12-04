#include "free.h"

void free_char_array(char **array, size_t size) {
  if (!array) return;
  for (size_t cpt = 0; cpt < size; cpt++) {
    free(array[cpt]);
  }
  free(array);
}