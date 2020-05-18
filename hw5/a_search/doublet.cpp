#include "heap.h"
#include "word.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <utility>
#include <fstream>
#include <stack>

using namespace std;

// convert to all uppercase
string upper(string word) {
	string result = "";
	char letter;
	for (int i=0; i < (int)word.size(); ++i) {
		// only convert if lowercase
		if (word[i] >= 97 && word[i] <= 122) {
			int diff = word[i] - 'a';
			letter = 'A' + diff;
		}
		else {
			letter = word[i];
		}
		result += letter;
	}
	return result;
}

// gets the h value of given word
int getH(string word, string goal) {
	int count = 0;
	for (int i=0; i < (int)word.size(); ++i) {
		if (word[i] != goal[i]) {
			++count;
		}
	}
	return count;
}

// given a word, generates all combos
vector<string> generateCombo(string word) {
	vector<string> result;
	string temp = word;
	string start = "";
	string end = "";

	for (int i=0; i<(int)word.size(); ++i) {
		string start = "";
		string end = "";
		for (int j=0; j<i; ++j) {
			start += word[j];
		}
		for (int j=i+1; j<(int)word.size(); ++j) {
			end += word[j];
		}
		for (char j=65; j<=90; ++j) {
			if(j != word[i]) {
				temp = start + j + end;
				result.push_back(temp);
			}
		}
	}

	return result;
}


// create the adjacency list representing graph
void createGraph(vector<string> &wordlist, map<string, int> &wordmap, vector<vector<int> > &adjlist) {
	// iterate through every word & generate possible combos
	for (int i=0; i<(int)wordlist.size(); ++i) {
		std::vector<string> result = generateCombo(wordlist[i]);
		vector<int> temp;
		// verify valid combo
		for (int j=0; j<(int)result.size(); ++j) {
			if (wordmap.find(result[j]) != wordmap.end()) {
				temp.push_back(wordmap[result[j]]);
			}
		}
		adjlist.push_back(temp);
	}
}

int main(int argc, char* argv[]) {
	// check for command line input
	if (argc < 4) {
		cout << "Invalid number of command line arguments!" << endl;
		return 0;
	}
	// try opening file
	ifstream myFile(argv[3]);
	if (myFile.fail()) {
		cout << "Unable to open file!" << endl;
		return 0;
	}

	// get the start & end words
	string start = upper(argv[1]);
	string end = upper(argv[2]);

	// if dif length => error
	if (start.size() != end.size()) {
		cout << "Cannot transform when they are different lengths" << endl;
		return 0;
	}

	vector<string> wordlist;
	// map to store all words
	// maps words to index in wordlist
	map<string, int> wordmap;
	// vector to keep track of transformation
	// index => nth transformation
	// int => index of word in wordlist
	vector<int> transform;
	// keep track of nodes in heap
	// maps word to nth, priority
	map<string, pair<int, int> > inHeap;
	// heap to determine which node to visit next
	MinHeap<Word> mh(2);
	// adjacency list to represent graph
	// first index => represents index in wordlist
	// value => index of neighbor
	vector<vector<int> > adjlist;
	// stack to keep track of shortest path
	// sting => word
	stack<string> shortest;


	int nth = 0;

	// store all words in uppercase
	int n;
	myFile >> n;
	if (myFile.fail()) {
		cout << "Something went wrong with reading the first line!" << endl;
		return 0;;
	}
	for (int i=0; i < n; ++i) {
		string word;
		myFile >> word;
		if (myFile.fail()) {
			cout << "Something went wrong reading the file!" << endl;
			return 0;
		}
		word = upper(word);
		wordlist.push_back(word);
		wordmap[word] = i;
	}
	myFile.close();

	// create graph
	createGraph(wordlist, wordmap, adjlist);

	// get the first word
	Word startword(start, end);
	int prty = shortest.size() + startword.getH();
	nth = mh.add(startword, prty);
	inHeap[startword.getWord()] = make_pair(nth, prty);
	int prev = -1;

	while (!mh.isEmpty()) {
		// peek from heap to determine where to go next
		Word current = mh.peek();
		mh.remove();
		// add to transform
		transform.push_back(wordmap[current.getWord()]);

		// update stack
		int g = inHeap[current.getWord()].second - current.getH();
		if (g < (int)shortest.size()) {
			int length = (int)shortest.size() - g;
			for (int i=0; i< length; ++i) {
				shortest.pop();
			}
			prev = wordmap[shortest.top()];
		}
		shortest.push(current.getWord());

		// if reached destination
		if (current.getWord() == end) {
			break;
		}

		// iterate & add neighbors of current word
		for (int i=0; i<(int)adjlist[wordmap[current.getWord()]].size(); ++i) {
			int index = adjlist[wordmap[current.getWord()]][i];
			// check if in heap already
			// if not it heap => create word, add to heap
			// update nth, inHeap
			if (inHeap.find(wordlist[index]) == inHeap.end()) {	
				Word temp(wordlist[index], end);
				prty = shortest.size() + temp.getH();
				nth = mh.add(temp, prty);
				inHeap[temp.getWord()] = make_pair(nth, prty);
			}
			// update in heap
			else {
				// do not update words from whence you came
				if (prev == index || prev == -1) {
					continue;
				}

				// only update if g is smaller
				prty = shortest.size() + getH(wordlist[index], end);
				if (inHeap[wordlist[index]].second > prty) {
					inHeap[wordlist[index]].second = prty;
					mh.update(inHeap[wordlist[index]].first, prty);
				}
			}
		}
	}

	

	if (wordlist[transform[transform.size()-1]] == end) {
		cout << shortest.size() - 1 << endl;
	}
	else {
		cout << "No transformation" << endl;
	}
	cout << transform.size() - 1 << endl;

	/*for (int i=0; i<(int)transform.size(); ++i) {
		cout << wordlist[transform[i]] << endl;
	}*/
	return 0;
}