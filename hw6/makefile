CC = g++ -Wall -g -std=c++11
GT = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread
VAL = valgrind --tool=memcheck --leak-check=yes

test_all: bsttest avltest spltest
	$(VAL) ./bsttest
	$(VAL) ./avltest
	$(VAL) ./spltest

bsttest: bst/bsttest.cpp bst/bst.h bst/print_bst.h
	$(CC) $< $(GT) -o $@

avltest: avl/avltest.cpp avl/avlbst.h bst/bst.h bst/print_bst.h
	$(CC) $< $(GT) -o $@

spltest: splay/splaytest.cpp splay/splay.h bst/bst.h bst/print_bst.h
	$(CC) $< $(GT) -o $@

testbst: bsttest
	$(VAL) ./$<

testavl: avltest
	$(VAL) ./$<

testspl: spltest
	$(VAL) ./$<

clean:
	rm bsttest
	rm avltest
	rm spltest