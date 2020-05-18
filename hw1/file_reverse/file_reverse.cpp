#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
	char *myArr = 0;
	int temp;
	// int variable to keep track of how many characters are stored
	int runningSize = 0;
	int characters;

	// open file
	ifstream iFile(argv[1]);

	// check if opening file succeeded
	if(iFile.fail()){
		cout << "unable to open file" << endl;
		return 0;
	}

	// if open success, get number of characters
	iFile >> temp;

	// check if first item is a number
	if(!iFile.fail()){
		characters = temp;
	}
	else{
		cout << "expected number as first input" << endl;
		return 0;
	}

	// dynamically allocate array
	myArr = new char[characters];

	// get text & store into string
	// must do twice since \n still in the input buffer
	string myLine;
	getline(iFile, myLine);

	// read in line by line
	while(getline(iFile, myLine)){

		// check if the line is too big for remaining space
		if((int)myLine.size() > characters - runningSize){
			// if text bigger than given size, output message, exit
			cout << "given number is smaller than actual length of text" << endl;
			delete[] myArr;
			return 0;
		}

		// fill in array
		for(int i=runningSize;i<runningSize+(int)myLine.size();i++){
			myArr[i] = myLine[i-runningSize];
		}

		// update runningSize
		runningSize += (int)myLine.size();

		// see if eof
		// if not eof => more lines need to be added => add new line to array
		if(!iFile.eof()){
			// check if there is enough remaining space
			if(characters - runningSize > 0){
				myArr[runningSize] = '\n';
				runningSize++;
			}
			else{
				cout << "given number is smaller than actual length of text" << endl;
				delete[] myArr;
				return 0;
			}
		}
	}

	// output
	for(int i=runningSize-1;i>=0;i--){
		cout << myArr[i];
	}
	cout << endl;

	// deallocate
	delete[] myArr;
	myArr = 0;

	return 0;
}


// [DONE] must handle multiple lines
// [DONE] must handle incorrect size
	// too small array => output error message & quit?
	// too large array => just output until valid
// [DONE] must handle if first item not a number
// [DONE] must handle if file empty
// [DONE] must handle if no file