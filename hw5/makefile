CP = g++
CF = -Wall -g -std=c++11
BT = backtrack
HP = heap
AS = a_search
BIN = bin

all: learning doublet


.PHONY: clean
clean:
	rm learning
	rm d-ary
	rm $(BIN)/*
	rm doublet
learning: $(BT)/learning.cpp
	$(CP) $(CF) $< -o $@
d-ary: $(HP)/main.cpp $(HP)/heap.h
	$(CP) $(CF) $< -o $@
doublet: $(AS)/doublet.cpp $(BIN)/word.o $(AS)/heap.h
	$(CP) $(CF) $< $(BIN)/word.o -o $@
$(BIN)/word.o: $(AS)/word.cpp $(AS)/word.h
	$(CP) $(CF) -c $< -o $@
