#include <iostream>
#include <fstream>
#include "interpreter/interpreter.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "No input file provided!" << endl;
        return 0;
    }

    // open file
    ifstream input;
    input.open(argv[1]);

    // check if failed
    if (input.fail()) {
        cout <<"File " << argv[1] << " cannot be opened." << endl;
    }

    // create interpreter
    Interpreter interpreter(input);
    // run program
    interpreter.execute();

    //interpreter.write(cout);

    // close file
    input.close();

    return 0;
}
