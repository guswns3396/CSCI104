#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <cmath>

using namespace std;

class TheRani {
public:
    TheRani(char* input_path, char* output_path);
    ~TheRani();

    // Call execute and handles exceptions
    void main();

private:
    int experiment_count;       // You will need to track the number of experiments
    int* subject_counts;        // For each, the number of subjects
    string** subject_history;   // And for each subject, their history

    ifstream input;             // Input file stream
    ofstream output;            // Output file stream

    // to keep track of line number
    int lnum;
    // bool to keep track of heap allocation
    bool usedHeap;

    // Called in the main method
    void execute(const string& line);

    // function to deallocate / delete experiments
    void deleteExp(int* counts, string** exp, int numExp);

    // function to check input
    void checkInput(stringstream& ss, int& val);

};

TheRani::TheRani(char* input_path, char* output_path){
    // set private variables
    experiment_count = 0;
    subject_counts = 0;
    subject_history = 0;
    lnum = 0;
    usedHeap = false;

    output.open(output_path);
    input.open(input_path);
}

TheRani::~TheRani() {
	deleteExp(subject_counts, subject_history, experiment_count);
}

void TheRani::deleteExp(int* counts, string** exp, int numExp){
	// only deallocate memory if there was memory allocated
	if(!usedHeap){
		return;
	}

	// if just 1 experiment
	// deallocate counts & exp singly
	if(numExp == 0){
		// deallocate subject count singly
		delete counts;
		counts = 0;

		// deallocate exp[0]
		delete[] exp[0];
		exp[0] = 0;

		// deallocate exp singly
		delete exp;
		exp = 0;

	}
	// if more than 1 experiment
	// deallocate counts [] & exp []
	else{
		// deallocate previous subject count
	    delete[] counts;
	    counts = 0;

	    // deallocate subject history
	    for(int i=0;i<=numExp;i++){
	    	delete[] exp[i];
	    	exp[i] = 0;
	    }
	    
	    delete[] exp;
	    exp = 0;
	}

    return;
}

// Possible helper: read an integer argument from a stream
void TheRani::checkInput(stringstream& ss, int& val){
	double fraction;
	double integer;
	double number;

	ss >> number;
	// check if theres enough arguments
	if(ss.fail() && ss.eof()){
		throw invalid_argument("too few arguments");
	}
	// check if number
	if(ss.fail()){
		throw invalid_argument("expected number as argument");
	}
	// check if double
	fraction = modf(number, &integer);
	if(fraction > 0){
		throw invalid_argument("expected integer as argument");
	}

	// store integer
	val = (int)integer;
	
}

void TheRani::main() {
    // string to read in each line
    string line;

    // check if file correctly open
    if(!input.is_open()){
    	this->output << "unable to open file" << endl;
    	return;
    }

    // read input file line by line
    while (getline(input, line)) {
    	// update lnum
    	lnum++;
        // try to execute the line
        try {
            this->execute(line);
        } catch(exception& e) {
            // If you use exceptions, make sure the line number is printed here
            this->output << "Error on line " << lnum << ": " << e.what() << endl;


        }
    }

    // if file is empty => lnum = 0
    if(lnum == 0){
    	this->output << "file is empty" << endl;
    	return;
    }
}

void TheRani::execute(const string& line) {
    string command;
    stringstream stream(line);  // Initialize the stream with the line
    stream >> command;          // Read the first word, which is the command

    // make it already has had a "START"
    if (subject_history == 0 && command != "START"){
    	throw invalid_argument("no subjects yet");
    }
    // commands
    if (command == "START") {   // This code should be edited for error checking
        int temp;
        int subject_pool_count;

        // check for valid input
        checkInput(stream, temp);
        subject_pool_count = temp;

        // make sure it's a valid number
        if (subject_pool_count <= 0) {
            throw out_of_range("expected number of subjects to be greater than 0");
        }

        // if already started, erase everything first
        if(subject_counts != 0 || subject_history != 0){
        	deleteExp(subject_counts, subject_history, experiment_count);
        	experiment_count = 0;
        	// denote there is no more heap memory usage
        	usedHeap = false;
        }

        // notify using heap
        usedHeap = true;

        // if everything's good
        // create initial subject history (exp 0 => subject pool)
        // and initialize their history
        subject_history = new string*;
        *subject_history = new string[subject_pool_count];
        for(int i=0;i<subject_pool_count;i++){
            subject_history[0][i]="";
        }

        // create array for number of subjects
        subject_counts = new int;
        *subject_counts = subject_pool_count;
    }
    // ADD command
    else if(command == "ADD"){
        // increment experiment
        experiment_count++;

        // temp to store previous subject_history
        string** history_temp = subject_history;
        // temp to store previous subject count
        int* counts_temp = subject_counts;

        // create new subject history
        subject_history = new string*[experiment_count+1];
        for(int i=0;i<=experiment_count;i++){
            // each experiment has at most total number of subjects
            subject_history[i] = new string[counts_temp[0]];
        }

        // create new subject count
        subject_counts = new int[experiment_count+1];

        // copy previous subject count to new subject count
        for(int i=0;i<experiment_count;i++){
            subject_counts[i] = counts_temp[i];
        }
        // the added element should be zero (no subjects)
        subject_counts[experiment_count] = 0;

        // copy previous subject history to new subject history
        for(int i=0;i<=experiment_count;i++){
            for(int j=0;j<subject_counts[i];j++){
                subject_history[i][j] = history_temp[i][j];
            }
        }

        // delete old
        deleteExp(counts_temp, history_temp, experiment_count-1);
    }
    // MOVE command
    else if(command == "MOVE"){
        // int array to store int from stream
        // 0=>x, 1=>y, 2=>n, 3=>m
        int args[3];
        int x,y,n,m;

        // check for valid input
        for(int i=0;i<4;i++){
        	checkInput(stream,args[i]);
        }
        x = args[0];
        y = args[1];
        n = args[2];
        m = args[3];

        // make sure the numbers are valid
        // check if any are negative
        if(x < 0 || y < 0 || n < 0 || m < 0){
        	throw out_of_range("argument out of range (negative number)");
        }
        // check if valid experiment
        if(x > experiment_count || y > experiment_count){
        	throw out_of_range("argument out of range (invalid experiment)");
        }
        // check if valid subject
        if(n >= subject_counts[x] || m >= subject_counts[x]){
        	throw out_of_range("argument out of range (invalid subject)");
        }
        // check if n is smaller than m
        if(n > m){
        	throw invalid_argument("invalid range of subjects to move");
        }

	    // stringstream and string for updating
    	stringstream update;
    	string s;
    	// convert to string
    	update << y;
    	update >> s;

        // if moving within same experiment
        if(x == y){
        	// if m is the last element in array => do not change positions
        	if(m == subject_counts[x]-1){
        		// just update n to m with added exp
        		for(int i =n;i<=m;i++){
        			subject_history[x][i] = subject_history[x][i] + " " + s;
        		}
        	}
        	// if m is not the last element => position change required from n to last
        	else{
        		// create a temp subject history
        		string* tempsh = new string[m-n+1];

        		// copy the elements getting moved through MOVE
        		for(int i=n;i<=m;i++){
        			tempsh[i-n] = subject_history[x][i];
        		}

        		// shift the elements getting shifted
        		for(int i=m+1;i<subject_counts[x];i++){
        			subject_history[x][i-n] = subject_history[x][i];
        		}

        		// put the elements back at the end with exp added
        		int shiftedIndex = n + subject_counts[x] - m - 1;
        		for(int i=shiftedIndex;i<subject_counts[x];i++){
        			subject_history[x][i] = tempsh[i - shiftedIndex] + " " + s;
        		}

        		// delete temp array
        		delete[] tempsh;
        		tempsh = 0;
        	}
        }


        // if moving betweeen experiments
        else{
	        // move the subjects by copying and updating
	        // update y subject counts & subject history
	        for(int i=n;i<=m;i++){
	        	// counter for adding subject to exp
	        	int counter = subject_counts[y];

	        	// copy
	        	subject_history[y][counter] = subject_history[x][i];

	        	// update subject history
	        	subject_history[y][counter] = subject_history[y][counter] + " " + s;


	        	// update counter & subject counts
	        	subject_counts[y]++;
	        }
	        
	        // update x subject counts & subject history
	        int count = 0;
	        for(int i=n;i<=m;i++){
	        	count++;
	        	// make sure within range
	        	if(m+count < subject_counts[x]){
	        		subject_history[x][n] = subject_history[x][m+count];
	        	}
	        }
	        // update subject history
	        subject_counts[x] -= count;
	    }
    }
    // QUERY command
    else if(command == "QUERY"){
    	// int array to store from command
    	int args[2];
    	int x,n;

    	// check for valid input
    	for(int i=0;i<2;i++){
    		checkInput(stream, args[i]);
    	}
        x = args[0];
        n = args[1];
        
		// make sure input is non negative
    	if(x < 0 || n < 0){
    		throw out_of_range("argument out of range");
    	}
    	// make sure input is valid
    	if(x > experiment_count || n >= subject_counts[x]){
    		throw out_of_range("argument out of range");
    	}

    	// stringstream to read each string
    	// string for output
    	stringstream exp;
    	string result;
    	// store subject exp history
    	exp << subject_history[x][n];
    	// output history except if exp 0
    	while(!exp.fail()){
    		exp >> result;
    		if(!exp.fail() && result != "0"){
    			 this->output << result << " ";
    		}
    	}
    	this->output << endl;
    }
    // any other invalid command
    else{
    	throw invalid_argument("command does not exist");
    }

}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Please provide an input and output file!" << endl;
        return 1;
    }

    TheRani tr(argv[1], argv[2]);
    tr.main();
    return 0;
}


// [DONE] must handle new START
// [DONE] must handle invalid argument types (doubles, strings, etc)
	// what if last input is double? => still works
// [DONE] must handle excess arguments
// [DONE] must handle too few arguments
// [DONE] must handle invalid commands
// [DONE] must handle out of range arguments
// [DONE] must handle if first line is not START
// [DONE] START 0?
// [DONE] try moving within same exp
// [DONE] continue executing after catch
// [DONE] no valgrind errors
// [DONE] must handle empty file
// [DONE] must handle no file