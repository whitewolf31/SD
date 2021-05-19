CC = gcc
CFLAGS = -g -Wall -lm

all: clean build

build: main.c cerinta1.c cerinta2.c cerinta3.c graph.c tema3.h
	$(CC) main.c cerinta1.c cerinta2.c cerinta3.c graph.c tema3.h -o movies  $(CFLAGS)

.PHONY : clean
clean:
	rm -f movies
