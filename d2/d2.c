#include "d2.h"

int is_safe(int *numbers) {
  int increase = -1;
  int safe = 1;

  for (int i = 0; i < 9 && numbers[i + 1] != -1; i++) {
    int diff = numbers[i + 1] - numbers[i];

    if (diff > 0 && diff < 4) {
      if (increase == 0) {
        safe = 0;
        break;
      }
      increase = 1;
    } else if (diff < 0 && diff > -4) {
      if (increase == 1) {
        safe = 0;
        break;
      }
      increase = 0;
    } else {
      safe = 0;
      break;
    }
  }
  return safe;
}

int p1_safe_reports(const char *file) {
  size_t size = 0;
  char **lines = parse_file(file, &size);
  if (!lines) {
    fprintf(stderr, "Failed to parse file.\n");
    return -1;
  }

  int result = 0;
  for (size_t i = 0; i < size; i++) {
    printf("Line content %s\n", lines[i]);
    int numbers[10];
    for (int i = 0; i < 10; i++) {
      numbers[i] = -1;
    }

    char *token = strtok(lines[i], " ");
    size_t count = 0;
    while (token != NULL) {
      numbers[count] = atoi(token);
      token = strtok(NULL, " ");
      count++;
    }

    if (is_safe(numbers) == 1) {
      result++;
    }
  }
  free_char_array(lines, size);
  return result;
}

int p2_safe_reports(const char *file) {
  size_t size = 0;
  char **lines = parse_file(file, &size);
  if (!lines) {
    fprintf(stderr, "Failed to parse file.\n");
    return -1;
  }

  int result = 0;
  for (size_t i = 0; i < size; i++) {
    printf("Line content %s\n", lines[i]);
    int numbers[10];
    for (int i = 0; i < 10; i++) {
      numbers[i] = -1;
    }

    char *token = strtok(lines[i], " ");
    size_t count = 0;
    while (token != NULL) {
      numbers[count] = atoi(token);
      token = strtok(NULL, " ");
      count++;
    }

    if (is_safe(numbers) == 1) {
      result++;
    } else {
      // iterate through numbers and create a new array without the current
      // value, then call the is_safe function with new array
      for (int i = 0; i < 10; i++) {
        if (numbers[i] != -1) {
          int new_numbers[10];
          for (int j = 0; j < 10; j++) {
            new_numbers[j] = -1;
          }

          int index = 0;
          for (int j = 0; j < 10; j++) {
            if (numbers[j] != -1 && j != i) {
              new_numbers[index] = numbers[j];
              index++;
            }
          }

          if (is_safe(new_numbers) == 1) {
            result++;
            break;
          }
        }
      }
    }
  }
  free_char_array(lines, size);
  return result;
}