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
int Constant::getValue() const {
	return this->value;
}




// implement Variable class
Variable::Variable(string name, map<string, int>* variables){
	this->name = name;
	this->variables = variables;
}
Variable::~Variable(){

}

// implement SingleVariable class
SingleVariable::SingleVariable(string name, map<string, int>* variables) : Variable(name, variables){

}
string SingleVariable::format() const{
	return this->name;
}
int SingleVariable::getValue() const {
	// look in the map
	return (*variables)[this->name];
}
void SingleVariable::setValue(int val) {
	(*variables)[this->name] = val;
	return;
}

// implement ArrayVariable class
ArrayVariable::ArrayVariable(string name, map<string, int>* variables, NumericExpression* nexp) : Variable(name, variables){
	this->nexp = nexp;
}
ArrayVariable::~ArrayVariable(){
	// deallocate
	delete this->nexp;
}
string ArrayVariable::format() const{
	return this->name + "[" + this->nexp->format() + "]";
}
int ArrayVariable::getValue() const {
	// evaluate nexp
	stringstream sstemp;
	sstemp << this->nexp->getValue();
	string stemp;
	sstemp >> stemp;
	return (*variables)[this->name + "[" + stemp + "]"];
}
void ArrayVariable::setValue(int val) {
	// evaluate nexp
	stringstream sstemp;
	sstemp << this->nexp->getValue();
	string stemp;
	sstemp >> stemp;
	(*variables)[this->name + "[" + stemp + "]"] = val;
	return;
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
int AdditionExpression::getValue() const {
	return this->left->getValue() + this->right->getValue();
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
int SubtractionExpression::getValue() const {
	return this->left->getValue() - this->right->getValue();
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
int MultiplicationExpression::getValue() const {
	return this->left->getValue() * this->left->getValue();
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
int DivisionExpression::getValue() const {
	int num = this->left->getValue();
	int den = this->right->getValue();

	stringstream ss;
	ss << num;
	string s;
	ss >> s;

	// make sure not dividing by zero
	if (den == 0) {
		throw runtime_error("Division by 0: " + left->format() + " = " + s +
			", " + right->format() + " = 0.");
	}
	else {
		return num / den;
	}
}