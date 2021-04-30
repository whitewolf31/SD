#!/bin/bash

test_path="public_tests/task03/in/test"

for i in {1..20}
do
    echo "Test $i - no valgrind"
    echo -e "\n"
    time ./minimax -c3 "$test_path$i.in" editor.out
    echo "Test $i - valgrind"
    echo -e "\n"
    time valgrind --leak-check=full --track-origins=yes -q --log-file=rezultat_valgrind.txt ./minimax -c3 "$test_path$i.in" editor.out
done
