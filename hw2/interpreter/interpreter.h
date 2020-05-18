#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <vector>
#include <iostream>
#include "command.h"

class Interpreter {
public:
    Interpreter(std::istream& in);
    ~Interpreter();

    void write(std::ostream& out);

private:
	// vector to keep track of all the command pointers
	std::vector<Command*> commands;
	std::vector<size_t> lines;

    void parse(std::istream& in);

    // gets rid of leading & trailing whitespace
    std::string strip_expression(std::string line);

    // checks which command parser function to use
    Command* parse_command(std::string line);
    Command* parse_command_print(std::string line);
    Command* parse_command_let(std::string line);
    Command* parse_command_goto(std::string line);
    Command* parse_command_if(std::string line);
    Command* parse_command_gosub(std::string line);

    BooleanExpression* parse_bexp(std::string line);
    
    NumericExpression* parse_nexp(std::string line);
    NumericExpression* check_number(std::string s);
    NumericExpression* check_variable(std::string s);
    NumericExpression* check_binop(std::string s);
};

#endif
