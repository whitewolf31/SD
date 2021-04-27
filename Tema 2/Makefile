CC = gcc
CFLAGS = -g -Wall -lm

all: clean build

build: minimax.c cerinta1.c cerinta2.c cerinta3.c cerinta1.h tree.h
	$(CC) minimax.c cerinta1.c cerinta2.c cerinta3.c -o minimax  $(CFLAGS)

.PHONY : clean
clean:
	rm -f editor
	rm -f *.out
