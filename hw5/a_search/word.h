#include <string>

class Word {
private:
	std::string word;
	int h;

public:
	Word(std::string word, std::string goal);

	std::string getWord() const;

	int getH() const;

	// for comparing words (priority)
	bool operator<(const Word& other);
	bool operator>(const Word& other);
};