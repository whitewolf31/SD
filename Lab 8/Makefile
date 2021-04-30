CC=g++
CFLAGS=-Wall -g --std=c++11 -Wwrite-strings

tested = exercitiul*.cpp
tests = exercitiul*_teste.cpp

all: build run clean

build: lab

helpers.o: helpers.cpp helpers.h

heap.o: heap.cpp heap.h

scope_measurer.o: scope_measurer.cpp scope_measurer.h

lab: check_lab.cpp helpers.o heap.o scope_measurer.o $(tested) $(tests)
	$(CC) $(CFLAGS) -o $@ $^

test: lab
	./lab 1 2 3 4

run: lab
	./lab

pack:
	zip arh.zip *.cpp *.h  Makefile

.PHONY:
clean:
	rm -rf lab *.o
