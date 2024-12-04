CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = out

# Create files for a new avent of code day
# Usage: make create DAY=d1
create:
	mkdir -p $(DAY)
	touch $(DAY)/$(DAY).c $(DAY)/$(DAY).h $(DAY)/$(DAY).test.c
	echo "#include \"$(DAY).h\"" > $(DAY)/$(DAY).c
	echo "#ifndef $(DAY)_H\n#define $(DAY)_H\n\n#endif" > $(DAY)/$(DAY).h
	echo "#include <stdio.h>\n#include <assert.h>\n#include \"$(DAY).h\"\n\nint main() {\n  printf(\"Add tests here !\");\n  return 0;\n}" > $(DAY)/$(DAY).test.c

# Compile and run tests
# Usage: make test DAY=d1
test:
	cd $(DAY) && $(CC) $(CFLAGS) $(DAY).c $(DAY).test.c ../utils/file.c ../utils/free.c -I ../utils -o $(TARGET)
	./$(DAY)/$(TARGET)

# Clean output files
# Usage: make clean DAY=d1
clean:
	rm -rf $(DAY)/$(TARGET)
