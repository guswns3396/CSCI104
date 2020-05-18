#include "word.h"

using namespace std;

Word::Word(string word, string goal) {
	// store word
	this->word = word;
	// calculate h
	int count = 0;
	for (int i=0; i < (int)word.size(); ++i) {
		if (word[i] != goal[i]) {
			++count;
		}
	}
	this->h = count;
}

string Word::getWord() const {
	return word;
}

int Word::getH() const {
	return this->h;
}

bool Word::operator<(const Word& other) {
	if (h < other.h) {
		return true;
	}
	else if (h == other.h && word < other.word) {
		return true;
	}
	else {
		return false;
	}
}

bool Word::operator>(const Word& other) {
	if (h > other.h) {
		return true;
	}
	else if (h == other.h && word > other.word) {
		return true;
	}
	else {
		return false;
	}
}