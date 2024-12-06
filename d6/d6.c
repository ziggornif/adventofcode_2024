#include "d6.h"

void print_map(char** map, int size_x) {
  int size_y = strlen(map[0]);
  for (int i = 0; i < size_x; i++) {
    for (int j = 0; j < size_y; j++) {
      printf("%c", map[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

int patrol(const char* input, int debug) {
  size_t size = 0;
  char** lines = parse_file(input, &size);
  if (!lines) {
    fprintf(stderr, "Failed to parse file.\n");
    return -1;
  }

  int size_x = (int)size;
  int size_y = strlen(lines[0]);
  guard_pos_t guard_pos = {.x = 0, .y = 0};

  for (int i = 0; i < size_x; i++) {
    for (int j = 0; j < size_y; j++) {
      if (lines[i][j] == '^') {
        guard_pos.x = i;
        guard_pos.y = j;
      }
    }
  }

  int step_counter = 1;
  int exited = 0;

  char direction = 'N';
  while (!exited) {
    if (guard_pos.x == size_x - 1 || guard_pos.y == size_y - 1 ||
        guard_pos.x == 0 || guard_pos.y == 0) {
      exited = 1;
      break;
    }

    if (direction == 'N') {
      if (lines[guard_pos.x - 1][guard_pos.y] == '#') {
        guard_pos.y++;
        direction = 'E';
      } else {
        guard_pos.x--;
      }
    } else if (direction == 'S') {
      if (lines[guard_pos.x + 1][guard_pos.y] == '#') {
        guard_pos.y--;
        direction = 'W';
      } else {
        guard_pos.x++;
      }
    } else if (direction == 'W') {
      if (lines[guard_pos.x][guard_pos.y - 1] == '#') {
        guard_pos.x--;
        direction = 'N';
      } else {
        guard_pos.y--;
      }
    } else if (direction == 'E') {
      if (lines[guard_pos.x][guard_pos.y + 1] == '#') {
        guard_pos.x++;
        direction = 'S';
      } else {
        guard_pos.y++;
      }
    }
    if (lines[guard_pos.x][guard_pos.y] == '.') {
      step_counter++;
      lines[guard_pos.x][guard_pos.y] = 'X';
    }

    if (debug) {
      print_map(lines, size_x);
    }
  }

  free_char_array(lines, size_x);

  return step_counter;
}