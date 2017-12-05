CC=gcc
CFLAGS=-Wall -std=c99 -Wextra -Werror -pedantic -g -lm
OBJECTS=main.o

all: Project

Project: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o project

main.o: main.c library/ifj17builtins.c
	$(CC) $(CFLAGS) -c main.c

clean:
	@rm -f $(PROGRAMS) *.o core

library/ifj17builtins.c: library/ifj17builtins.code
	printf '%s\n' '#include <stdio.h>' 'void print_builtins(FILE *f) {' 'fputs(' > $@
	sed 's/#.*$$//;/^\s*$$/d;s/^\s*//;s/^/"/;s/$$/\\n"/' < $< >> $@
	printf '%s\n' ', f);' '}' >> $@
