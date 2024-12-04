#include "file.h"

size_t count_lines(const char *path) {
  FILE *file = fopen(path, "r");
  if (!file) {
    fprintf(stderr, "File not found.\n");
    return 0;
  }

  size_t lines = 0;
  char buffer[256];
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

  char line[256];
  size_t index = 0;
  while (fgets(line, sizeof(line), file) && index < *size_out) {
    line[strcspn(line, "\n")] = '\0';
    lines[index] = strdup(line);
    index++;
  }

  fclose(file);
  return lines;
}

char *read_file(const char *path) {
  FILE *file = fopen(path, "r");
  if (!file) {
    fprintf(stderr, "File not found.\n");
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *content = malloc(file_size + 1);
  if (!content) {
    fprintf(stderr, "Memory allocation failed.\n");
    fclose(file);
    return NULL;
  }

  fread(content, 1, file_size, file);
  content[file_size] = '\0';

  fclose(file);
  return content;
}