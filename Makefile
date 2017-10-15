CC=gcc
CFLAGS=-Wall -std=c99 -Wextra -Werror -pedantic -g -lm
OBJECTS=main.o str.o scanner.o 

all: Project

Project: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o project

main.o: main.c define.h
	$(CC) $(CFLAGS) -c main.c

str.o: str.c str.h
	$(CC) $(CFLAGS) -c str.c

lex.o: scanner.c scanner.h define.h
	$(CC) $(CFLAGS) -c scanner.c
