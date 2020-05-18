#include "heap.h"
#include <iostream>

using namespace std;

int main() {
	MinHeap<int> mh(1);
	int c;
	/*mh.add(12,12);
	mh.add(18,18);
	mh.add(9,9);
	mh.add(8,8);
	mh.add(6,6);

	mh.iterate();
	cout << endl;

	mh.add(5,5);
	mh.add(9,9);
	mh.add(20,20);
	mh.add(10,10);
	mh.add(3,3);

	mh.iterate();
	cout << endl;
	mh.remove();
	mh.iterate();
	cout << endl;
	mh.remove();
	mh.iterate();
	cout << endl;
	mh.update(8, 0);
	mh.iterate();
	cout << endl;
	mh.update(5, -1);
	mh.iterate();
	cout << endl;
	c = mh.add(9, 0);
	mh.iterate();*/


	//cout << c << endl;

	for (int i=0; i< 9; ++i) {
		mh.remove();
	}
	cout << mh.isEmpty() << endl;
	mh.peek();
}