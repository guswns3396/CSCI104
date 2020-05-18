#include <iostream>
#include <fstream>
#include "interpreter/interpreter.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Please provide an input file." << endl;
        return 1;
    }

    // see if give output file
    ofstream myFile;
    if(argc == 3){
        myFile.open(argv[2]);
    }

    ifstream input(argv[1]);
    Interpreter interpreter(input);

    // if given output file
    if(argc == 3){
        interpreter.write(myFile);
        myFile.close();
    }
    else{
        interpreter.write(cout);
    }

    return 0;
}
