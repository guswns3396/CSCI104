#include "arithmetic.h"
#include <sstream>

using namespace std;


// implement Constant class
Constant::Constant(int value){
	this->value = value;
}
string Constant::format() const{
	stringstream ss;
	string s;
	ss << this->value;
	ss >> s;
	return s;
}




// implement Variable class
Variable::Variable(string name){
	this->name = name;
}
Variable::~Variable(){

}

// implement SingleVariable class
SingleVariable::SingleVariable(string name) : Variable(name){

}
string SingleVariable::format() const{
	return this->name;
}

// implement ArrayVariable class
ArrayVariable::ArrayVariable(string name, NumericExpression* nexp) : Variable(name){
	this->nexp = nexp;
}
ArrayVariable::~ArrayVariable(){
	// deallocate
	delete this->nexp;
}
string ArrayVariable::format() const{
	return this->name + "[" + this->nexp->format() + "]";
}




// implement BinaryExpression constructor
BinaryExpression::BinaryExpression(NumericExpression* left, NumericExpression* right){
	this->left = left;
	this->right = right;
}
BinaryExpression::~BinaryExpression(){
	
}

// implement AdditionExpression
AdditionExpression::AdditionExpression(NumericExpression* left, NumericExpression* right) : BinaryExpression(left, right) {

}
AdditionExpression::~AdditionExpression() {
    delete this->left;
    delete this->right;
}
string AdditionExpression::format() const {
    return "(" + this->left->format() + " + " + this->right->format() + ")";
}

// implement SubtractionExpression
SubtractionExpression::SubtractionExpression(NumericExpression* left, NumericExpression* right) : BinaryExpression(left, right){

}
SubtractionExpression::~SubtractionExpression(){
	delete this->left;
	delete this->right;
}
string SubtractionExpression::format() const{
	return "(" + this->left->format() + " - " + this->right->format() + ")";
}

// implement MultiplicationExpression
MultiplicationExpression::MultiplicationExpression(NumericExpression* left, NumericExpression* right) : BinaryExpression(left, right){

}
MultiplicationExpression::~MultiplicationExpression(){
	delete this->left;
	delete this->right;
}
string MultiplicationExpression::format() const{
	return "(" + this->left->format() + " * " + this->right->format() + ")";
}

// implement DivisionExpression
DivisionExpression::DivisionExpression(NumericExpression* left, NumericExpression* right) : BinaryExpression(left, right){

}
DivisionExpression::~DivisionExpression(){
	delete this->left;
	delete this->right;
}
string DivisionExpression::format() const{
	return "(" + this->left->format() + " / " + this->right->format() + ")";
}