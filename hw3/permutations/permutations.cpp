#include <string>
#include <vector>
#include <iostream>

using namespace std;

// function declaration
void permutations(string);
void helper(string, vector<char>, string, int, int);


void permutations(string in){
	// edge case
	if(in.size() == 0) return;

	// add each letter to vector
	vector<char> left;
	for(int i=0;i<(int)in.size();i++){
		left.push_back(in[i]);
	}

	string s = "";

	// call helper
	helper(in,left,s,-1,0);

}

void helper(string in, vector<char> left, string s, int del, int count){
	// base case
	if(count == (int)in.size()){
		cout << s << endl;
		return;
	}

	// erase the letter the previous call used
	if(del != -1){
		left.erase(left.begin()+del);
	}
	// branch for each remaining letter
	// update del
	for(int i=0;i<(int)left.size();i++){
		helper(in,left,s+left[i],i,count+1);
	}

}


// int main(){
// 	string input;
// 	cout << "What's the string? ";
// 	cin >> input;
// 	permutations(input);

// 	return 0;
// }