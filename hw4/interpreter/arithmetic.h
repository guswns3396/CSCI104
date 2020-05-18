#ifndef ARITHMETIC_HPP
#define ARITHMETIC_HPP

#include <string>
#include <map>

class NumericExpression {
public:
	// no constructor => compiler writes one for you
    virtual ~NumericExpression() {}
    virtual std::string format() const = 0;

    // every nexp has getValue function
    virtual int getValue() const = 0;
};




// a constant is a numeric expression
class Constant : public NumericExpression{
private:
	// constants always have a value
	int value;
public:
	// non default constructor => must be used
	Constant(int value);
	std:: string format() const;

	int getValue() const;
};




// variable is a numeric expression
class Variable : public NumericExpression{
// protected so that children can access
protected:
	// variables always have a string for name
	std::string name;
	// variables always have pointer to map to get value
	std::map<std::string, int>* variables;
public:
	// non default constructor => must be used
	Variable(std::string name, std::map<std::string, int>* variables);
	// use virtual destructor since inheritance
	virtual ~Variable();
	// cannot instantiate Variable class
	// format function implemented by children
	virtual std::string format() const = 0;

	virtual int getValue() const = 0;
	virtual void setValue(int val) = 0;
};

// single variable is a variable
class SingleVariable : public Variable{
public:
	// non default constructor
	SingleVariable(std::string name, std::map<std::string, int>* variables);
	std::string format() const;

	int getValue() const;
	void setValue(int val);
};

// array variable is a variable
class ArrayVariable : public Variable{
private:
	// array variables have pointer to numeric expression
	NumericExpression* nexp;
public:
	// non default constructor => must use
	ArrayVariable(std::string name, std::map<std::string, int>* variables, NumericExpression* nexp);
	// need specialized destructor for deallocation
	~ArrayVariable();
	std::string format() const;

	int getValue() const;
	void setValue(int val);
};




// binary expression is a numeric expression
class BinaryExpression : public NumericExpression{
// protected so child class can access
protected:
	// all binary expressions have pointers to 2 numeric expressions
	NumericExpression* left;
	NumericExpression* right;
public:
	// non default constructor => must be used
	BinaryExpression(NumericExpression* left, NumericExpression* right);
	// virtual destructor since inheritance
	virtual ~BinaryExpression();
	// cannot instantiate BinaryExpression class
	// format function must be implemented by children
	virtual std::string format() const = 0;

	virtual int getValue() const = 0;
};

// addition expression is a binary expression
class AdditionExpression : public BinaryExpression {
public:
	// non default constructor => must be used
	AdditionExpression(NumericExpression* left, NumericExpression* right);
	// need custom destructor since virtual
    ~AdditionExpression();
    
    std::string format() const;

    int getValue() const;
};

// subtraction expression is a binary expression
class SubtractionExpression : public BinaryExpression{
public:
	// non default constructor => must be used
	SubtractionExpression(NumericExpression* left, NumericExpression* right);
	// need custom destructor since virtual
	~SubtractionExpression();

	std::string format() const;

	int getValue() const;
};

// multiplication expression is a binary expression
class MultiplicationExpression : public BinaryExpression{
public:
	// non default constructor => must be used
	MultiplicationExpression(NumericExpression* left, NumericExpression* right);
	// need custom destructor since virtual
	~MultiplicationExpression();

	std::string format() const;

	int getValue() const;
};

// division expression is a binary expression
class DivisionExpression : public BinaryExpression{
public:
	// non default constructor => must be used
	DivisionExpression(NumericExpression* left, NumericExpression* right);
	// need custom destructor since virtual
	~DivisionExpression();

	std::string format() const;

	int getValue() const;
};

#endif
