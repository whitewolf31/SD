CC = gcc
CFLAGS = -g -Wall -lm

all: clean build

build team_1.c:
	$(CC) -o editor editor.c $(CFLAGS)

.PHONY : clean
clean:
	rm -f editor
	rm -f *.out
