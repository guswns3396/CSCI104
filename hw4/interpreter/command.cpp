#include "command.h"
#include <sstream>
#include <iostream>

using namespace std;

// implementation of JumpLine
JumpLine::JumpLine(size_t jlnum){
	this->jlnum = jlnum;
}
string JumpLine::format() const{
	stringstream ss;
	string s;
	ss << this->jlnum;
	ss >> s;

	return "<" + s + ">";
}
size_t JumpLine::getLine() const {
	return this->jlnum;
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
void Command_Print::execute(map<size_t, Command*>::iterator &it) const {
	cout << this->nexp->getValue() << endl;
	++it;
	return;
}

// implementation of Command_Let
Command_Let::Command_Let(Variable* var, NumericExpression* nexp){
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
void Command_Let::execute(map<size_t, Command*>::iterator &it) const {
	// set variable to certain value
	int val = this->nexp->getValue();
	this->var->setValue(val);
	++it;
	return;
}

// implementation of Command_Goto
Command_Goto::Command_Goto(JumpLine* jlnum, map<size_t, Command*>* commands){
	this->jlnum = jlnum;
	this->commands = commands;
}
Command_Goto::~Command_Goto(){
	delete this->jlnum;
}
string Command_Goto::format() const{
	return "GOTO " + this->jlnum->format();
}
void Command_Goto::execute(map<size_t, Command*>::iterator &it) const {
	// find jline in map
	it = this->commands->find(this->jlnum->getLine());
	// non-existent jlnum
	if (it == this->commands->end()) {
		stringstream ss;
		ss << jlnum->getLine();
		string s;
		ss >> s;
		throw runtime_error("GOTO to non-existent line " + s + ".");
	}
	return;
}

// implementation of Command_If
Command_If::Command_If(BooleanExpression* bexp, JumpLine* jlnum, map<size_t, Command*>* commands){
	this->bexp = bexp;
	this->jlnum = jlnum;
	this->commands = commands;
}
Command_If::~Command_If(){
	delete this->bexp;
	delete this->jlnum;
}
string Command_If::format() const{
	return "IF " + this->bexp->format() + " THEN " + this->jlnum->format();
}
void Command_If::execute(map<size_t, Command*>::iterator &it) const {
	// go to line if true
	if (this->bexp->getValue()) {
		it = this->commands->find(this->jlnum->getLine());
		// check if non existent
		if (it == this->commands->end()) {
			stringstream ss;
			ss << jlnum->getLine();
			string s;
			ss >> s;
			throw runtime_error("IF jump to non-existent line " + s + ".");
		}
	}
	// move onto next line if false
	else {
		++it;
		return;
	}
}

// implementation of Gosub
Command_Gosub::Command_Gosub(JumpLine* jlnum, map<size_t, Command*>* commands, stack<size_t>* gotos){
	this->jlnum = jlnum;
	this->commands = commands;
	this->gotos = gotos;
}
Command_Gosub::~Command_Gosub(){
	delete this->jlnum;
}
string Command_Gosub::format() const{
	return "GOSUB " + this->jlnum->format();
}
void Command_Gosub::execute(map<size_t, Command*>::iterator &it) const {
	// store originating line number
	this->gotos->push(it->first);
	// find jline in map
	it = this->commands->find(this->jlnum->getLine());
	// non-existent jlnum
	if (it == this->commands->end()) {
		// get rid of line stored in stack
		this->gotos->pop();
		// display error
		stringstream ss;
		ss << jlnum->getLine();
		string s;
		ss >> s;
		throw runtime_error("GOSUB to non-existent line " + s + ".");
	}
	return;
}

// implementation of Return
Command_Return::Command_Return(map<size_t, Command*>* commands, stack<size_t>* gotos){
	this->commands = commands;
	this->gotos = gotos;
}
Command_Return::~Command_Return(){

}
string Command_Return::format() const{
	return "RETURN";
}
void Command_Return::execute(map<size_t, Command*>::iterator &it) const {
	// if stack empty => no matching gosub
	if (this->gotos->size() == 0) {
		throw runtime_error("No matching GOSUB for RETURN.");
	}
	// get most recent gosub jlnum
	size_t jlnum = this->gotos->top();
	this->gotos->pop();
	it = this->commands->find(jlnum);
	// immediately after gosub line
	++it;
	return;
}

// implementation of End
Command_End::Command_End(map<size_t, Command*>* commands){
	this->commands = commands;
}
Command_End::~Command_End(){
	
}
string Command_End::format() const{
	return "END";
}
void Command_End::execute(map<size_t, Command*>::iterator &it) const {
	it = this->commands->end();
	return;
}