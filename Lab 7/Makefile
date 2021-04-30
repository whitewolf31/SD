CC=g++
CFLAGS=-Wall -g --std=c++11 -Wwrite-strings

tested = exercitiul*.cpp
tests = exercitiul*_teste.cpp

all: build run clean

build: lab

helpers.o: helpers.cpp helpers.h

bst_node.o: bst_node.cpp bst_node.h

trie.o: trie.cpp trie.h

lab: check_lab.cpp helpers.o bst_node.o trie.o $(tested) $(tests)
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
