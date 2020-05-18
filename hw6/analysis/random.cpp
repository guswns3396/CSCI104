#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

int main(int argc, char** argv) {
	if (argc < 2) {
		return 0;
	}

	ofstream ofile(argv[1]);

	int n;
	int m;
	int random;
	cout << "n? ";
	cin >> n;
	cout << "m? ";
	cin >> m;
	cout << "rand? ";
	cin >> random;

	int curr = 0;
	string alphanumeric = "abcdefghijklmnopqrstuvwxyz0123456789";
	string s = "";

	srand(random);
	while (curr < n) {
		// until full
		for (int i=0; i<m; ++i) {
			// pick random number
			s += alphanumeric[rand()%36];
		}
		// store if full
		ofile << s << endl;
		++curr;
		s = "";
	}

	return 0;
}