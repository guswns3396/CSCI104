#include "cave.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
	// check for valid input
	if(argc < 2){
		cout << "Must provide an input file" << endl;
		return 0;
	}
	ifstream in(argv[1]);

	if(in.fail()){
		cout << "Failed to open file" << endl;
		return 0;
	}

	cout << cave(in) << endl;

	return 0;
}