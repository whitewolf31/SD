CC=g++
CFLAGS=-Wall -g --std=c++11 -Wwrite-strings -Wall

tested_files = exercitiul1.cpp exercitiul2.cpp exercitiul3.cpp exercitiul4.cpp exercitiul5.cpp
tests_files = exercitiul1_teste.cpp exercitiul2_teste.cpp exercitiul3_teste.cpp exercitiul4_teste.cpp exercitiul5_teste.cpp

all: build run clean

build: lab

helpers.o: helpers.cpp helpers.h

bst_node.o: bst_node.cpp bst_node.h

lab: check_lab.cpp  $(tested_files) $(tests_files) helpers.o bst_node.o
	$(CC) $(CFLAGS) -o $@ $^

test: lab
	time ./lab 1 2 3 4

run: lab
	time ./lab

pack:
	zip arh.zip *.cpp *.h  Makefile

.PHONY:
clean:
	rm -rf lab *.o
