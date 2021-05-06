CC = gcc
CFLAGS = -g -Wall -lm

all: clean build

build: main.c exercitiul1.c exercitiul2.c exercitiul3.c exercitiul4.c lab10.h
	$(CC) main.c exercitiul1.c exercitiul2.c exercitiul3.c exercitiul4.c lab10.h -o lab10  $(CFLAGS)

.PHONY : clean
clean:
	rm -f lab10
