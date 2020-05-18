CC = g++ -Wall -g -std=c++11
GT = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread
VAL = valgrind --tool=memcheck --leak-check=yes

analysis: analysis.cpp ../avl/avlbst.h ../splay/splay.h ../bst/bst.h ../bst/print_bst.h
	$(CC) $< -o $@

random: random.cpp
	$(CC) $< -o $@
	./$@ input

test: analysis input output random
	./random input
	$(VAL) ./analysis ./input ./output

clean:
	rm analysis
	rm random