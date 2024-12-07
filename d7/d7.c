#include "d7.h"

bool evaluate(long* values, size_t size, long testValue, operation_t* operators,
              size_t operatorCount) {
  if (size == 1) {
    return values[0] == testValue;
  }

  for (size_t i = 0; i < operatorCount; i++) {
    long newValue = operators[i](values[0], values[1]);
    long* newValues = malloc((size - 1) * sizeof(long));
    if (!newValues) {
      perror("Failed to allocate memory");
      exit(EXIT_FAILURE);
    }

    newValues[0] = newValue;
    for (size_t j = 2; j < size; j++) {
      newValues[j - 1] = values[j];
    }

    bool result =
        evaluate(newValues, size - 1, testValue, operators, operatorCount);
    free(newValues);

    if (result) {
      return true;
    }
  }

  return false;
}

long addition(long a, long b) { return a + b; }

long multiplication(long a, long b) { return a * b; }

long concatenate(long a, long b) {
  long numDigits = b == 0 ? 1 : (long)log10(b) + 1;
  return a * pow(10, numDigits) + b;
}

long solve(const char* input, size_t* size) {
  char** lines = parse_file(input, size);
  operation_t operators[] = {addition, multiplication, concatenate};
  size_t operatorCount = sizeof(operators) / sizeof(operators[0]);
  long result = 0;

  for (size_t i = 0; i < *size; i++) {
    long testValue = 0;
    char rest[256];
    if (sscanf(lines[i], "%ld: %255[^\n]", &testValue, rest) != 2) {
      fprintf(stderr, "Invalid line format: %s\n", lines[i]);
      continue;
    }

    size_t valueCount = 0;
    long values[256];
    char* token = strtok(rest, " ");
    while (token) {
      char* endptr;
      values[valueCount++] = strtol(token, &endptr, 10);
      if (*endptr != '\0') {
        fprintf(stderr, "Invalid number: %s\n", token);
        continue;
      }
      token = strtok(NULL, " ");
    }

    if (evaluate(values, valueCount, testValue, operators, operatorCount)) {
      result += testValue;
    }
  }

  return result;
}

long equations(const char* input) {
  size_t size = 0;
  long result = solve(input, &size);
  return result;
}