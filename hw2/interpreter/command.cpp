#include "command.h"
#include <sstream>

using namespace std;

// implementation of JumpLine
JumpLine::JumpLine(int jlnum){
	this->jlnum = jlnum;
}
string JumpLine::format() const{
	stringstream ss;
	string s;
	ss << this->jlnum;
	ss >> s;

	return "<" + s + ">";
}

// implementation of Command_Print
Command_Print::Command_Print(NumericExpression* nexp){
	this->nexp = nexp;
}
Command_Print::~Command_Print(){
	delete nexp;
}
string Command_Print::format() const{
	return "PRINT " + this->nexp->format();
}

// implementation of Command_Let
Command_Let::Command_Let(NumericExpression* var, NumericExpression* nexp){
	this->var = var;
	this->nexp = nexp;
}
Command_Let::~Command_Let(){
	delete this->var;
	delete this->nexp;
}
string Command_Let::format() const{
	return "LET " + this->var->format() + " " + this->nexp->format();
}

// implementation of Command_Goto
Command_Goto::Command_Goto(JumpLine* jlnum){
	this->jlnum = jlnum;
}
Command_Goto::~Command_Goto(){
	delete this->jlnum;
}
string Command_Goto::format() const{
	return "GOTO " + this->jlnum->format();
}

// implementation of Command_If
Command_If::Command_If(BooleanExpression* bexp, JumpLine* jlnum){
	this->bexp = bexp;
	this->jlnum = jlnum;
}
Command_If::~Command_If(){
	delete this->bexp;
	delete this->jlnum;
}
string Command_If::format() const{
	return "IF " + this->bexp->format() + " THEN " + this->jlnum->format();
}

// implementation of Gosub
Command_Gosub::Command_Gosub(JumpLine* jlnum){
	this->jlnum = jlnum;
}
Command_Gosub::~Command_Gosub(){
	delete this->jlnum;
}
string Command_Gosub::format() const{
	return "GOSUB " + this->jlnum->format();
}

// implementation of Return
Command_Return::Command_Return(){

}
Command_Return::~Command_Return(){

}
string Command_Return::format() const{
	return "RETURN";
}

// implementation of End
Command_End::Command_End(){

}
Command_End::~Command_End(){
	
}
string Command_End::format() const{
	return "END";
}