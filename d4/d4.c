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
  free_char_array(lines, size);
  return result;
}

int check_x_pattern(char **lines, size_t x, size_t y, char t_left, char t_right,
                    char b_left, char b_right) {
  return (lines[x - 1][y - 1] == t_left && lines[x - 1][y + 1] == t_right &&
          lines[x + 1][y - 1] == b_left && lines[x + 1][y + 1] == b_right);
}

int p2_find_x_mas(const char *input_file) {
  size_t size = 0;
  char **lines = parse_file(input_file, &size);
  if (!lines) {
    fprintf(stderr, "Failed to parse file.\n");
    return -1;
  }

  int result = 0;
  for (size_t i = 1; i < size - 1; i++) {
    size_t line_len = strlen(lines[i]);
    for (size_t j = 1; j < line_len - 1; j++) {
      if (lines[i][j] == 'A') {
        if (check_x_pattern(lines, i, j, 'M', 'S', 'M', 'S') ||
            check_x_pattern(lines, i, j, 'M', 'M', 'S', 'S') ||
            check_x_pattern(lines, i, j, 'S', 'S', 'M', 'M') ||
            check_x_pattern(lines, i, j, 'S', 'M', 'S', 'M')) {
          result++;
        }
      }
    }
  }
  free_char_array(lines, size);
  return result;
}