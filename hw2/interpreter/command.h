#ifndef COMMAND_HPP
#define COMMAND_HPP

//#include <string>
//#include "arithmetic.h"
#include "boolean.h"

class JumpLine{
private:
	// jump lines always have an int representing line number
	int jlnum;
public:
	// non default constructor => must use
	JumpLine(int jlnum);
	std::string format() const;
};

class Command {
public:
    virtual std::string format() const = 0;
    // need virtual destructor since inheritance
    virtual ~Command() {}
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
};

// let command is a command
class Command_Let : public Command{
private:
	// let commands always have a variable and a numeric expression
	NumericExpression* var;
	NumericExpression* nexp;
public:
	// non default constructor => must be used
	Command_Let(NumericExpression* var, NumericExpression* nexp);
	// custom destructor since virtual
	~Command_Let();

	std::string format() const;
};

// goto command is a command
class Command_Goto : public Command{
private:
	// goto commands have jump line
	JumpLine* jlnum;
public:
	// non default constructor => must use
	Command_Goto(JumpLine* jlnum);
	~Command_Goto();

	std::string format() const;
};

// if command is a command
class Command_If : public Command{
private:
	// if commands have boolean expression & jump line
	BooleanExpression* bexp;
	JumpLine* jlnum;
public:
	// non default constructor => must use
	Command_If(BooleanExpression* bexp, JumpLine* jlnum);
	~Command_If();

	std::string format() const;
};

// gosub command is a command
class Command_Gosub : public Command{
private:
	// gosub commands have jump line
	JumpLine* jlnum;
public:
	// non default constructor => must use
	Command_Gosub(JumpLine* jlnum);
	~Command_Gosub();

	std::string format() const;
};

// return command is a command
class Command_Return : public Command{
public:
	// non default constructor => must use
	Command_Return();
	~Command_Return();

	std::string format() const;
};

// end command is a command
class Command_End : public Command{
public:
	// non default constructor => must use
	Command_End();
	~Command_End();

	std::string format() const;
};

#endif
