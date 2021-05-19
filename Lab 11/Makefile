CC = gcc
CFLAGS = -g -Wall -lm

all: clean build

build: main.c exercitiul1.c exercitiul2.c functii_adaugare_graf.c lab11.h
	$(CC) main.c exercitiul1.c exercitiul2.c functii_adaugare_graf.c lab11.h -o lab11  $(CFLAGS)

.PHONY : clean
clean:
	rm -f lab11
