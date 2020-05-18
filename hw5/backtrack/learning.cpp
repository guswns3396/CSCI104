#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void getWork(vector<double> &result, double work, double learn, vector<double> &classes, int pos, double totWork) {
	bool isDone = true;
	// iterate through list and try to add
	for (int i = pos; i < (int)classes.size(); i += 2) {
		// recursive case
		if (work + classes[i] <= totWork) {
			isDone = false;
			getWork(result, work + classes[i], learn + classes[i+1], classes, i+2, totWork);
		}
	}
	// base case
	// only add if no other options work
	if (isDone) {
		// cout << work << endl;
		// cout << learn << endl;
		result.push_back(learn);
	}
}

int main(int argc, char** argv) {

	// check for command line input
	if (argc < 2) {
		cout << "No input file provided!" << endl;
		return 0;
	}
	// try opening file
	ifstream myFile(argv[1]);
	if (myFile.fail()) {
		cout << "Unable to open file!" << endl;
		return 0;
	}

	int totClass;
	double totWork;
	vector<double> result;

	// get total class & work, make sure they are valid
	myFile >> totClass >> totWork;
	if (myFile.fail()) {
		cout << "Invalid format" << endl;
		return 0;
	}
	if (totClass < 1) {
		cout << "Invalid number of classes" << endl;
		return 0;
	}

	// store work & learn into vector of double => allow for backtracking
	// even index => work; odd index => learn
	vector<double> classes;
	while (!myFile.eof()) {
		string name; double work; double learn;
		myFile >> name >> work >> learn;
		if (myFile.fail()) {
			cout << "Something went wrong reading the file!" << endl;
			return 0;
		}
		// make sure they are positive
		if (work >= 0 && learn >= 0) {
			classes.push_back(work);
			classes.push_back(learn);
		}
		else {
			cout << "Negative number for work or learn!" << endl;
			return 0;
		}
	}
	myFile.close();

	// check totClass matches number of sizes
	if (2 * totClass != (int)classes.size()) {
		cout << "Total number of classes do not match!" << endl;
		return 0;
	}

	getWork(result, 0, 0, classes, 0, totWork);

	// find maximum learning
	double max = result[0];
	for (int i = 1; i < (int)result.size(); ++i) {
		if (result[i] > max) {
			max = result[i];
		}
	}
	// output result
	cout << max << endl;

	return 0;
}