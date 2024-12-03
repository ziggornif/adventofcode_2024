#ifndef file_H
#define file_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t count_lines(const char *path);
char **parse_file(const char *path, size_t *size_out);
char *read_file(const char *path);

#endif
