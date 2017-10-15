CC=gcc
CFLAGS=-Wall -std=c99 -Wextra -Werror -pedantic -g -lm
OBJECTS=main.o

all: Project

Project: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o project

main.o: main.c 
	$(CC) $(CFLAGS) -c main.c


