#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <stack>
#include "command.h"

class Interpreter {
public:
    Interpreter(std::istream& in);
    ~Interpreter();

    void write(std::ostream& out);

    // function to execute the program
    // must execute program according to the lines / command
    // catch errors if needed
    // terminate
    void execute();

private:
    // map to keep track of all the variables
    std::map<std::string, int> variables;
    // map to keep track of line number and command
    std::map<size_t, Command*> commands;
    // stack to keep track of goto
    std::stack<size_t> gotos;

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
    Constant* check_number(std::string s);
    Variable* check_variable(std::string s);
    BinaryExpression* check_binop(std::string s);
};

#endif
