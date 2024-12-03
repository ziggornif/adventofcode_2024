#include "d3.h"

int parse_val(regmatch_t *pmatch, int index, const char *str) {
  char *val = NULL;
  int start = pmatch[index].rm_so;
  int end = pmatch[index].rm_eo;
  int result = 0;
  size_t size = end - start;
  val = malloc(sizeof(*val) * (size + 1));
  if (val) {
    strncpy(val, &str[start], size);
    val[size] = '\0';
    result = atoi(val);
    free(val);
  }
  return result;
}

int p1_mull(const char *input_file) {
  regex_t preg;
  const char *regex = "mul\\(([0-9]+),([0-9]+)\\)";
  char *content = read_file(input_file);

  int err = regcomp(&preg, regex, REG_EXTENDED);
  if (err != 0) {
    printf("Error while compiling regex\n");
    return -1;
  }

  int match = 0;
  int result = 0;
  while (match == 0) {
    size_t nmatch = 0;
    regmatch_t *pmatch = NULL;
    nmatch = 3;
    pmatch = malloc(sizeof(*pmatch) * nmatch);

    match = regexec(&preg, content, 3, pmatch, 0);
    int v1 = parse_val(pmatch, 1, content);
    int v2 = parse_val(pmatch, 2, content);

    result += v1 * v2;
    content += pmatch[0].rm_eo;
  }

  regfree(&preg);
  return result;
}
