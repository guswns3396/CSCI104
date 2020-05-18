CC = g++
CF = -g -Wall -std=c++11
GT = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread
TEST = tests
COM = company
VAL = valgrind --tool=memcheck --leak-check=yes

cave: cave.o cave_main.cpp
	$(CC) $(CF) $^ -o $@
cave.o: cave.cpp cave.h
	$(CC) $(CF) -c $< -o $@

$(COM)/company.o: $(COM)/company.cpp $(COM)/company.hpp
	$(CC) $(CF) -c $< -o $@
$(TEST)/companyTest.o: $(TEST)/$(COM)/companyTest.cpp
	$(CC) $(CF) -c $< -o $@
companyTest: $(COM)/company.o $(TEST)/$(COM)/companyTest.o
	$(CC) $(CF) $^ $(GT) -o $@


clean:
	rm cave.o cave