COMPILE = g++ -g -Wall -std=c++11
BIN = ./interpreter/bin
LIB = ./interpreter
EX = ./examples
VAL = valgrind --tool=memcheck --leak-check=yes

all: basic_interpreter

basic_interpreter: main.cpp $(BIN)/interpreter.o $(BIN)/command.o $(BIN)/arithmetic.o \
	$(BIN)/boolean.o

	$(COMPILE) main.cpp $(BIN)/interpreter.o $(BIN)/command.o $(BIN)/arithmetic.o \
	$(BIN)/boolean.o -o ./basic_interpreter

$(BIN)/interpreter.o: $(LIB)/interpreter.h $(LIB)/interpreter.cpp
	$(COMPILE) -c $(LIB)/interpreter.cpp -o $(BIN)/interpreter.o

$(BIN)/command.o: $(LIB)/command.h $(LIB)/command.cpp
	$(COMPILE) -c $(LIB)/command.cpp -o $(BIN)/command.o

$(BIN)/boolean.o: $(LIB)/boolean.h $(LIB)/boolean.cpp
	$(COMPILE) -c $(LIB)/boolean.cpp -o $(BIN)/boolean.o

$(BIN)/arithmetic.o: $(LIB)/arithmetic.h $(LIB)/arithmetic.cpp
	$(COMPILE) -c $(LIB)/arithmetic.cpp -o $(BIN)/arithmetic.o

valgrind_file:
	echo input1.in
	$(VAL) ./basic_interpreter $(EX)/input1.in $(EX)/myoutput1.out
	echo input2.in
	$(VAL) ./basic_interpreter $(EX)/input2.in $(EX)/myoutput2.out
	echo input3.in
	$(VAL) ./basic_interpreter $(EX)/input3.in $(EX)/myoutput3.out
	echo input4.in
	$(VAL) ./basic_interpreter $(EX)/input4.in $(EX)/myoutput4.out
	echo input5.in
	$(VAL) ./basic_interpreter $(EX)/input5.in $(EX)/myoutput5.out
	echo input6.in
	$(VAL) ./basic_interpreter $(EX)/input6.in $(EX)/myoutput6.out
	echo input7.in
	$(VAL) ./basic_interpreter $(EX)/input7.in $(EX)/myoutput7.out
	echo input8.in
	$(VAL) ./basic_interpreter $(EX)/input8.in $(EX)/myoutput8.out
	echo test
	$(VAL) ./basic_interpreter testcases/test testcases/out

valgrind_cout:
	echo input1.in
	$(VAL) ./basic_interpreter $(EX)/input1.in
	echo input2.in
	$(VAL) ./basic_interpreter $(EX)/input2.in
	echo input3.in
	$(VAL) ./basic_interpreter $(EX)/input3.in
	echo input4.in
	$(VAL) ./basic_interpreter $(EX)/input4.in
	echo input5.in
	$(VAL) ./basic_interpreter $(EX)/input5.in
	echo input6.in
	$(VAL) ./basic_interpreter $(EX)/input6.in
	echo input7.in
	$(VAL) ./basic_interpreter $(EX)/input7.in
	echo input8.in
	$(VAL) ./basic_interpreter $(EX)/input8.in
	echo test
	$(VAL) ./basic_interpreter testcases/test

diff:
	diff $(EX)/output1.out $(EX)/myoutput1.out
	diff $(EX)/output2.out $(EX)/myoutput2.out
	diff $(EX)/output3.out $(EX)/myoutput3.out
	diff $(EX)/output4.out $(EX)/myoutput4.out
	diff $(EX)/output5.out $(EX)/myoutput5.out
	diff $(EX)/output6.out $(EX)/myoutput6.out
	diff $(EX)/output7.out $(EX)/myoutput7.out
	diff $(EX)/output8.out $(EX)/myoutput8.out

clean:
	rm $(BIN)/* ./basic_interpreter

