#include "gtest/gtest.h"
#include "bst.h"
#include <utility>
#include <iostream>
#include <vector>

using namespace std;

TEST(structure, insert_simple) {
    BinarySearchTree<int, char> bst;
    bst.insert(make_pair(5,'B'));
    bst.insert(make_pair(3,'A'));
    bst.insert(make_pair(7,'C'));
    
    bst.print();
}

TEST(structure, insert_complex) {
    BinarySearchTree<int, char> bst;
    int arr[10] = {44,17,62,78,50,32,30,54,70,88};
    char j = 'A';
    for (int i=0; i < 10; ++i) {
        bst.insert(make_pair(arr[i],j));
        ++j;
    }

    bst.print();
}

TEST(structure, insert_simple_update) {
	BinarySearchTree<int, char> bst;
    bst.insert(make_pair(5,'B'));
    bst.insert(make_pair(3,'A'));
    bst.insert(make_pair(7,'C'));

    bst.print();
    cout<<"updating 7 to Z"<<endl;
    bst.insert(make_pair(7,'Z'));

    bst.print();
}

TEST(structure, insert_complex_update) {
    BinarySearchTree<int, char> bst;
    int arr[10] = {44,17,62,78,50,32,30,54,70,88};
    char j = 'A';
    for (int i=0; i < 10; ++i) {
        bst.insert(make_pair(arr[i],j));
        ++j;
    }

    bst.print();
    cout << "updating 50 to Z"<<endl;
    bst.insert(make_pair(50, 'Z'));

    bst.print();
}

TEST(structure, insert_nullroot) {
    BinarySearchTree<int, char> bst;
    cout <<"Before insert"<<endl;
    bst.print();
    bst.insert(make_pair(5,'B'));
    cout<<"After insert"<<endl;
    bst.print();
}

TEST(structure, clear_simple) {
	BinarySearchTree<int, char> bst;
    bst.insert(make_pair(5,'B'));
    bst.insert(make_pair(3,'A'));
    bst.insert(make_pair(7,'C'));
    
    cout << "Before clear" << endl;
    bst.print();

    bst.clear();

    cout << "After clear" << endl;
    bst.print();
}

TEST(structure, clear_complex) {
    BinarySearchTree<int, char> bst;
    int arr[10] = {44,17,62,78,50,32,30,54,70,88};
    char j = 'A';
    for (int i=0; i < 10; ++i) {
        bst.insert(make_pair(arr[i],j));
        ++j;
    }

    cout << "Before clear" << endl;
    bst.print();

    bst.clear();

    cout << "After clear" << endl;
    bst.print();
}

TEST(structure, clear_nullroot) {
	BinarySearchTree<int, char> bst;

    cout << "Before clear" << endl;
    bst.print();

    bst.clear();

    cout << "After clear" << endl;
    bst.print();
}

TEST(iterator, begin_to_end_simple) {
	BinarySearchTree<int, char> bst;
    bst.insert(make_pair(5,'B'));
    bst.insert(make_pair(3,'A'));
    bst.insert(make_pair(7,'C'));

    bst.print();

    BinarySearchTree<int, char>::iterator it;
    int i = 3;
    char j = 'A';
    for (it = bst.begin(); it != bst.end(); ++it) {
    	EXPECT_EQ(it->first, i);
    	EXPECT_EQ(it->second, j);
    	i += 2;
    	++j;
    }
    cout << "Passed" << endl;
}

TEST(iterator, begin_to_end_complex) {
    BinarySearchTree<int, char> bst;
    int arr[10] = {8,2,14,18,10,6,4,12,16,20};
    char j = 'A';
    for (int i=0; i < 10; ++i) {
        bst.insert(make_pair(arr[i],j));
        ++j;
    }

    bst.print();

    BinarySearchTree<int, char>::iterator it;
    int i = 2;
    for (it = bst.begin(); it != bst.end(); ++it) {
        EXPECT_EQ(it->first, i);
        i += 2;
    }
    cout << "Passed" << endl;
}

TEST(iterator, begin_to_end_nullroot) {
	BinarySearchTree<int, char> bst;
	BinarySearchTree<int, char>::iterator it;
	it = bst.begin();
	EXPECT_TRUE(it==bst.end());
	cout << "Passed"<<endl;
}

TEST(iterator, find_simple) {
	BinarySearchTree<int, char> bst;
    bst.insert(make_pair(5,'B'));
    bst.insert(make_pair(3,'A'));
    bst.insert(make_pair(7,'C'));

    bst.print();

    cout << "trying to find 3" << endl;
    BinarySearchTree<int, char>::iterator it = bst.find(3);
    EXPECT_EQ(it->first, 3);
    EXPECT_EQ(it->second, 'A');

    cout << "Passed" <<endl;
}

TEST(iterator, find_complex) {
    BinarySearchTree<int, char> bst;
    int arr[10] = {44,17,62,78,50,32,30,54,70,88};
    char j = 'A';
    for (int i=0; i < 10; ++i) {
        bst.insert(make_pair(arr[i],j));
        ++j;
    }

    bst.print();

    cout << "trying to find 50" << endl;
    BinarySearchTree<int, char>::iterator it = bst.find(50);
    EXPECT_EQ(it->first, 50);
    EXPECT_EQ(it->second, 'E');

    cout << "Passed" <<endl;
}

TEST(iterator, find_not_there_simple) {
	BinarySearchTree<int, char> bst;
    bst.insert(make_pair(5,'B'));
    bst.insert(make_pair(3,'A'));
    bst.insert(make_pair(7,'C'));

    bst.print();

    cout << "trying to find 11" << endl;

    BinarySearchTree<int, char>::iterator it = bst.find(11);
    
    EXPECT_TRUE(it == bst.end());

    cout<<"Passed"<<endl;
}

TEST(iterator, find_not_there_complex) {
    BinarySearchTree<int, char> bst;
    int arr[10] = {44,17,62,78,50,32,30,54,70,88};
    char j = 'A';
    for (int i=0; i < 10; ++i) {
        bst.insert(make_pair(arr[i],j));
        ++j;
    }

    bst.print();

    cout << "trying to find 11" << endl;

    BinarySearchTree<int, char>::iterator it = bst.find(11);
    
    EXPECT_TRUE(it == bst.end());

    cout<<"Passed"<<endl;
}

TEST(iterator, find_nullroot) {
	BinarySearchTree<int, char> bst;

	cout << "trying to find 11" << endl;

    BinarySearchTree<int, char>::iterator it = bst.find(11);
    
    EXPECT_TRUE(it == bst.end());

    cout<<"Passed"<<endl;
}

TEST(remove, remove_not_there) {
    BinarySearchTree<int, char> bst;
    bst.insert(make_pair(5,'B'));
    bst.insert(make_pair(3,'A'));
    bst.insert(make_pair(7,'C'));

    bst.remove(11);

    bst.print();
}

TEST(remove, remove_leaf) {
    BinarySearchTree<int, char> bst;
    bst.insert(make_pair(5,'B'));
    bst.insert(make_pair(3,'A'));
    bst.insert(make_pair(7,'C'));

    cout << "before remove" << endl;
    bst.print();
    bst.remove(7);
    cout << "after remove" << endl;
    bst.print();
}

TEST(remove, remove_leaf_root) {
    BinarySearchTree<int, char> bst;
    bst.insert(make_pair(5,'B'));
    
    cout << "before remove" << endl;
    bst.print();
    bst.remove(5);
    cout << "after remove" << endl;
    bst.print();
}

TEST(remove, remove_onel) {
    BinarySearchTree<int, char> bst;
    bst.insert(make_pair(5,'B'));
    bst.insert(make_pair(3,'A'));
    bst.insert(make_pair(7,'C'));
    bst.insert(make_pair(2,'D'));

    cout << "before remove" << endl;
    bst.print();
    bst.remove(3);
    cout << "after remove" << endl;
    bst.print();
}

TEST(remove, remove_oner) {
    BinarySearchTree<int, char> bst;
    bst.insert(make_pair(5,'B'));
    bst.insert(make_pair(3,'A'));
    bst.insert(make_pair(7,'C'));
    bst.insert(make_pair(4,'D'));

    cout << "before remove" << endl;
    bst.print();
    bst.remove(3);
    cout << "after remove" << endl;
    bst.print();
}

TEST(remove, remove_one_longchild) {
    BinarySearchTree<int, char> bst;
    bst.insert(make_pair(50,'B'));
    bst.insert(make_pair(30,'A'));
    bst.insert(make_pair(70,'C'));
    bst.insert(make_pair(40,'D'));
    bst.insert(make_pair(35,'E'));
    bst.insert(make_pair(45,'F'));

    cout << "before remove" << endl;
    bst.print();
    bst.remove(30);
    cout << "after remove" << endl;
    bst.print();
}

TEST(remove, remove_one_root) {
    BinarySearchTree<int, char> bst;
    bst.insert(make_pair(5,'B'));
    bst.insert(make_pair(3,'A'));

    cout << "before remove" << endl;
    bst.print();
    bst.remove(5);
    cout << "after remove" << endl;
    bst.print();
}

TEST(remove, remove_two_longChild) {
    BinarySearchTree<int, char> bst;
    bst.insert(make_pair(50,'B'));
    bst.insert(make_pair(30,'A'));
    bst.insert(make_pair(70,'C'));
    bst.insert(make_pair(40,'D'));
    bst.insert(make_pair(20,'E'));
    bst.insert(make_pair(35,'F'));
    bst.insert(make_pair(45,'G'));

    cout << "before remove" << endl;
    bst.print();
    bst.remove(30);
    cout << "after remove" << endl;
    bst.print();
}

TEST(remove, remove_two_adj) {
    BinarySearchTree<int, char> bst;
    bst.insert(make_pair(50,'B'));
    bst.insert(make_pair(30,'A'));
    bst.insert(make_pair(70,'C'));
    bst.insert(make_pair(40,'D'));
    bst.insert(make_pair(20,'E'));

    cout << "before remove" << endl;
    bst.print();
    bst.remove(30);
    cout << "after remove" << endl;
    bst.print();
}

TEST(remove, remove_two_root) {
    BinarySearchTree<int, char> bst;
    bst.insert(make_pair(5,'B'));
    bst.insert(make_pair(3,'A'));
    bst.insert(make_pair(7,'C'));

    cout << "before remove" << endl;
    bst.print();
    bst.remove(5);
    cout << "after remove" << endl;
    bst.print();
}
