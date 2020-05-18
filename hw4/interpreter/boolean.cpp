#include "boolean.h"

using namespace std;


// implement BooleanExpression constructor
BooleanExpression::BooleanExpression(NumericExpression* left, NumericExpression* right){
	this->left = left;
	this->right = right;
}

// implement EqualExpression
EqualExpression::EqualExpression(NumericExpression* left, NumericExpression* right) : BooleanExpression(left, right) {

}
EqualExpression::~EqualExpression() {
    delete this->left;
    delete this->right;
}
string EqualExpression::format() const {
    return "[" + this->left->format() + " = " + this->right->format() + "]";
}
bool EqualExpression::getValue() const {
	if (this->left->getValue() == this->right->getValue()) {
		return true;
	}
	else {
		return false;
	}
}

// implement GreaterExpression
GreaterExpression::GreaterExpression(NumericExpression* left, NumericExpression* right) : BooleanExpression(left, right){

}
GreaterExpression::~GreaterExpression(){
	delete this->left;
	delete this->right;
}
string GreaterExpression::format() const{
	return "[" + this->right->format() + " < " + this->left->format() + "]";
}
bool GreaterExpression::getValue() const {
	if (this->left->getValue() > this->right->getValue()) {
		return true;
	}
	else {
		return false;
	}
}

// implement LessExpression
LessExpression::LessExpression(NumericExpression* left, NumericExpression* right) : BooleanExpression(left, right){

}
LessExpression::~LessExpression(){
	delete this->left;
	delete this->right;
}
string LessExpression::format() const{
	return "[" + this->left->format() + " < " + this->right->format() + "]";
}
bool LessExpression::getValue() const {
	if (this->left->getValue() < this->right->getValue()) {
		return true;
	}
	else {
		return false;
	}
}