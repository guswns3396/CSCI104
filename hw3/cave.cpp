
#include "cave.h"
#include <stack>
#include <iostream>
#include <map>

using namespace std;

int cave(ifstream& in){
	// create a map to match corresponding pairs
	map<char,char> match;
	match['N'] = 'S';
	match['S'] = 'N';
	match['W'] = 'E';
	match['E'] = 'W';

	char dir;
	stack<char> s;

	// get input until end of file
	while(!in.eof()){
		in >> dir;
		// break if at eof
		if(in.fail()){
			break;
		}
		// push to stack if size zero
		// otherwise check if top of stack is a match
		if((int)s.size() == 0){
			s.push(dir);
		}
		else{
			// if match => pop
			if(s.top() == match[dir]){
				s.pop();			
			}
			// if not => push
			else{
				s.push(dir);
			}
		}
	}

	// close the file
	in.close();

	// while(s.size()!=0){
	// 	cout << s.top() << endl;
	// 	s.pop();
	// }

	return (int)s.size();
}