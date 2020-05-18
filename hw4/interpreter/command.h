#ifndef COMMAND_HPP
#define COMMAND_HPP

//#include <string>
//#include "arithmetic.h"
#include "boolean.h"
#include <stack>
#include <map>

class JumpLine{
private:
	// jump lines always have an int representing line number
	size_t jlnum;
public:
	// non default constructor => must use
	JumpLine(size_t jlnum);
	std::string format() const;

	size_t getLine() const;
};

class Command {
public:
    virtual std::string format() const = 0;
    // need virtual destructor since inheritance
    virtual ~Command() {}

    // all commands must execute
    virtual void execute(std::map<size_t, Command*>::iterator &it) const = 0;
};

// print command is a command
class Command_Print : public Command{
private:
	// print commands always have a numeric expression
	NumericExpression* nexp;
public:
	// non default constructor => must be used
	Command_Print(NumericExpression* nexp);
	// custom destructor since virtual
	~Command_Print();

	std::string format() const;

	void execute(std::map<size_t, Command*>::iterator &it) const;
};

// let command is a command
class Command_Let : public Command{
private:
	// let commands always have a variable and a numeric expression
	Variable* var;
	NumericExpression* nexp;
public:
	// non default constructor => must be used
	Command_Let(Variable* var, NumericExpression* nexp);
	// custom destructor since virtual
	~Command_Let();

	std::string format() const;

	void execute(std::map<size_t, Command*>::iterator &it) const;
};

// goto command is a command
class Command_Goto : public Command{
private:
	// goto commands have jump line
	JumpLine* jlnum;
	// need access to map for command
	std::map<size_t, Command*>* commands;
public:
	// non default constructor => must use
	Command_Goto(JumpLine* jlnum, std::map<size_t, Command*>* commands);
	~Command_Goto();

	std::string format() const;

	void execute(std::map<size_t, Command*>::iterator &it) const;
};

// if command is a command
class Command_If : public Command{
private:
	// if commands have boolean expression & jump line
	BooleanExpression* bexp;
	JumpLine* jlnum;
	// need access to map commands
	std::map<size_t, Command*>* commands;
public:
	// non default constructor => must use
	Command_If(BooleanExpression* bexp, JumpLine* jlnum, std::map<size_t, Command*>* commands);
	~Command_If();

	std::string format() const;

	void execute(std::map<size_t, Command*>::iterator &it) const;
};

// gosub command is a command
class Command_Gosub : public Command{
private:
	// gosub commands have jump line
	JumpLine* jlnum;
	// need access to map commands & stack
	std::map<size_t, Command*>* commands;
	std::stack<size_t>* gotos;
public:
	// non default constructor => must use
	Command_Gosub(JumpLine* jlnum, std::map<size_t, Command*>* commands, std::stack<size_t>* gotos);
	~Command_Gosub();

	std::string format() const;

	void execute(std::map<size_t, Command*>::iterator &it) const;
};

// return command is a command
class Command_Return : public Command{
private:
	// need access to map commands & stack
	std::map<size_t, Command*>* commands;
	std::stack<size_t>* gotos;
public:
	// non default constructor => must use
	Command_Return(std::map<size_t, Command*>* commands, std::stack<size_t>* gotos);
	~Command_Return();

	std::string format() const;

	void execute(std::map<size_t, Command*>::iterator &it) const;
};

// end command is a command
class Command_End : public Command{
private:
	// need access to map commands
	std::map<size_t, Command*>* commands;
public:
	// non default constructor => must use
	Command_End(std::map<size_t, Command*>* commands);
	~Command_End();

	std::string format() const;

	void execute(std::map<size_t, Command*>::iterator &it) const;
};

#endif
