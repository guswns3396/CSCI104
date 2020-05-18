#ifndef BOOLEAN_HPP
#define BOOLEAN_HPP

//#include <string>
#include "arithmetic.h"

class BooleanExpression {
// protected so the child class can access
protected:
	// boolean expressions always have 2 pointers to numeric expressions
	NumericExpression* left;
	NumericExpression* right;
public:
	// custom constructor
	BooleanExpression(NumericExpression* left, NumericExpression* right);
	// virtual destructor since inheritance
    virtual ~BooleanExpression() {}
    // cannot instantiate this class
    // child classes must implement format()
    virtual std::string format() const = 0;
};

// equal expression is a boolean expression
class EqualExpression : public BooleanExpression{
public:
	// custom constructor
	EqualExpression(NumericExpression* left, NumericExpression* right);
	// custom destructor since virtual
	~EqualExpression();

	std::string format() const;
};

// greater than expression is a boolean expression
class GreaterExpression : public BooleanExpression{
public:
	// custom constructor
	GreaterExpression(NumericExpression* left, NumericExpression* right);
	// custom destructor since virutal
	~GreaterExpression();

	std::string format() const;
};

// less than expression is a boolean expression
class LessExpression : public BooleanExpression{
public:
	// custom constructor
	LessExpression(NumericExpression* left, NumericExpression* right);
	// custom destructor since virtual
	~LessExpression();

	std::string format() const;
};

#endif
