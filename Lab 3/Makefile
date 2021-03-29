CC=g++
CFLAGS=-Wall -g

tested_files = exercitiul1.cpp exercitiul2.cpp exercitiul3.cpp exercitiul4.cpp exercitiul5.cpp exercitiul6.cpp
tests_files = exercitiul1_teste.cpp exercitiul2_teste.cpp exercitiul3_teste.cpp exercitiul4_teste.cpp exercitiul5_teste.cpp exercitiul6_teste.cpp

all: build run clean

build: lab

helpers.o: helpers.cpp helpers.h

lab: check_lab3.cpp list.h list.c $(tested_files) $(tests_files) helpers.o
	$(CC) $(CFLAGS) -o $@ $^

test: lab
	time ./lab 1 2 4 5 6

run: lab
	time ./lab

pack:
	zip arh.zip *.cpp *.h *.c  Makefile

.PHONY:
clean: lab
	rm -rf lab
