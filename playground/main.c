#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int parse_val(regmatch_t *pmatch, int index, const char *str) {
  char *val = NULL;
  int start = pmatch[index].rm_so;
  int end = pmatch[index].rm_eo;
  int result = 0;
  size_t size = end - start;
  val = malloc(sizeof(*val) * (size + 1));
  printf("start %d end %d size %zu\n", start, end, size);
  if (val) {
    strncpy(val, &str[start], size);
    val[size] = '\0';
    printf("Current str val %s\n", val);
    result = atoi(val);
    free(val);
  }
  return result;
}

int main() {
  int err;
  regex_t preg_do;
  regex_t preg;
  const char *str = read_file("./input.txt");
  const char *regex_do = "(do\(\)|^).*?(don't\(\)|$)";
  const char *regex = "mul\\(([0-9]+),([0-9]+)\\)";

  err = regcomp(&preg_do, regex_do, REG_EXTENDED);
  printf("err %d\n", err);
  err = regcomp(&preg, regex, REG_EXTENDED);
  printf("err %d\n", err);

  if (err != 0) {
    return 1;
  }

  // while (match == 0) {
  // }

  int match = 0;
  int result = 0;
  while (match == 0) {
    size_t nmatch = 0;
    regmatch_t *pmatch = NULL;
    nmatch = 3;
    pmatch = malloc(sizeof(*pmatch) * nmatch);

    match = regexec(&preg, str, 3, pmatch, 0);
    int v1 = parse_val(pmatch, 1, str);
    int v2 = parse_val(pmatch, 2, str);

    printf("first %d second %d sum %d", v1, v2, v1 + v2);
    result += v1 * v2;
    str += pmatch[0].rm_eo;
  }

  regfree(&preg);
  printf("result %d", result);
  return 0;
}