CC = gcc
CFLAGS = -g -Wall -lm

all: clean build

build: editor.c
	$(CC) -o editor editor.c $(CFLAGS)

.PHONY : clean
clean:
	rm -f editor
	rm -f *.out
