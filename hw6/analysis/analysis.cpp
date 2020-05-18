#include "../avl/avlbst.h"
#include "../splay/splay.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <utility>
#include <ctime>

using namespace std;

void storeString(char* filename, vector<string>& v);
double getDuration(BinarySearchTree<string, int>* tree, vector<string>& v);

int main(int argc, char* argv[]) {
	// check to see if enough arguments
	if (argc < 3) {
		cout << "Not enough inputs!" << endl;
		return 0;
	}
	vector<string> v;
	// store string into vector
	storeString(argv[1], v);

	ofstream ofile(argv[2]);
	ofile << v.size() << " insertions" << endl;

	double avlsum = 0;
	double splsum = 0;
	int bads = 0;

	int r = 20;

	for (int i = 0; i < r; ++i) {
		// do avl
		AVLTree<string, int>* avl = new AVLTree<string, int>;
		avlsum += getDuration(avl, v);
		delete avl;
		avl = NULL;

		// do splay
		SplayTree<string, int>* spl = new SplayTree<string, int>;
		splsum += getDuration(spl, v);
		bads = spl->report();
		delete spl;
		spl = NULL;

	}

	ofile << "AVL: " << avlsum/r << " seconds" << endl;
	ofile << "Splay: " << splsum/r << " seconds" << endl;
	ofile << "Splay expensive: " << bads << endl;

	ofile.close();

	return 0;
}

void storeString(char* filename, vector<string>& v) {
	ifstream ifile(filename);
	string s;
	if (ifile.fail()) {
		cout << "Failed to open file" << endl;
		ifile.close();
		return;
	}
	while (!ifile.eof()) {
		ifile >> s;
		if (!ifile.fail()) {
			v.push_back(s);
		}
	}
	ifile.close();
	return;
}

double getDuration(BinarySearchTree<string, int>* tree, vector<string>& v) {
	clock_t start;
	double duration;

	// insert into tree & get time
	start = clock();
	for (int i = 0; i < (int)v.size(); ++i) {
		tree->insert(make_pair(v[i],i));
	}
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	return duration;
}

// input file nonexistent