#include "d4.h"

int p1_find_xmas(const char *input_file) {
  size_t size = 0;
  char **lines = parse_file(input_file, &size);
  if (!lines) {
    fprintf(stderr, "Failed to parse file.\n");
    return -1;
  }

  int result = 0;
  for (size_t i = 0; i < size; i++) {
    size_t line_len = strlen(lines[i]);
    for (size_t j = 0; j < line_len; j++) {
      if (lines[i][j] == 'X') {
        // start search
        // horizontal right search
        if (j + 3 <= line_len && lines[i][j + 1] == 'M' &&
            lines[i][j + 2] == 'A' && lines[i][j + 3] == 'S') {
          result++;
        }
        // horizontal left search
        if (j >= 3 && lines[i][j - 1] == 'M' && lines[i][j - 2] == 'A' &&
            lines[i][j - 3] == 'S') {
          result++;
        }
        // vertical down search
        if (i + 3 < size && lines[i + 1][j] == 'M' && lines[i + 2][j] == 'A' &&
            lines[i + 3][j] == 'S') {
          result++;
        }
        // vertical up search
        if (i >= 3 && lines[i - 1][j] == 'M' && lines[i - 2][j] == 'A' &&
            lines[i - 3][j] == 'S') {
          result++;
        }
        // diagonal up left search
        if (i >= 3 && j >= 3 && lines[i - 1][j - 1] == 'M' &&
            lines[i - 2][j - 2] == 'A' && lines[i - 3][j - 3] == 'S') {
          result++;
        }
        // diagonal up right search
        if (i >= 3 && j + 3 <= line_len && lines[i - 1][j + 1] == 'M' &&
            lines[i - 2][j + 2] == 'A' && lines[i - 3][j + 3] == 'S') {
          result++;
        }
        // diagonal down left search
        if (i + 3 < size && j >= 3 && lines[i + 1][j - 1] == 'M' &&
            lines[i + 2][j - 2] == 'A' && lines[i + 3][j - 3] == 'S') {
          result++;
        }
        // diagonal down right search
        if (i + 3 < size && j + 3 <= line_len && lines[i + 1][j + 1] == 'M' &&
            lines[i + 2][j + 2] == 'A' && lines[i + 3][j + 3] == 'S') {
          result++;
        }
      }
    }
  }
  return result;
}