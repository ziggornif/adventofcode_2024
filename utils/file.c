#include "file.h"

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

char **parse_file(const char *path, size_t *size_out) {
  *size_out = count_lines(path);
  if (size_out == 0) {
    return NULL;
  }

  FILE *file = fopen(path, "r");
  if (!file) {
    fprintf(stderr, "File not found.\n");
    *size_out = 0;
    return NULL;
  }

  char **lines = malloc(*size_out * sizeof(char *));

  char line[32];
  size_t index = 0;
  while (fgets(line, sizeof(line), file) && index < *size_out) {
    line[strcspn(line, "\n")] = '\0';
    lines[index] = strdup(line);
    index++;
  }

  fclose(file);
  return lines;
}