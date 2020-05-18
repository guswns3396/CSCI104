#include "gtest/gtest.h"
#include "avlbst.h"
#include <utility>
#include <iostream>
#include <vector>

using namespace std;

TEST(example, example) {
    AVLTree<int, char> avl;
    int arr[9] = {9,4,11,3,5,10,12,2,7};
    char j = 'A';
    for (int i=0; i < 9; ++i) {
        avl.insert(make_pair(arr[i],j));
        ++j;
    }
    avl.print();

    avl.insert(make_pair(1,'Z'));
    avl.print();

    avl.insert(make_pair(6,'Z'));
    avl.print();

    avl.insert(make_pair(8,'Z'));
    avl.print();
    avl.insert(make_pair(13,'Z'));
    avl.print();
    avl.remove(5);
    avl.print();
    avl.remove(1);
    avl.print();
}

TEST(insert, insert_simple) {
    AVLTree<int, char> avl;
    avl.insert(make_pair(5,'B'));
    avl.print();
    cout << endl;
    
    avl.insert(make_pair(3,'A'));
    avl.print();
    cout << endl;

    avl.insert(make_pair(7,'C'));
    avl.print();
}

// no T
TEST(insert, insert_srotR_simple) {
    AVLTree<int, char> avl;
    int arr[5] = {44,17,62,78,88};
    char j = 'A';
    for (int i=0; i < 5; ++i) {
        avl.insert(make_pair(arr[i],j));
        avl.print();
        cout << endl;
        ++j;
    }
}

TEST(insert, insert_srotR_complex) {
    AVLTree<int, char> avl;
    int arr[9] = {44,17,62,60,78,20,70,88,90};
    char j = 'A';
    for (int i=0; i < 9; ++i) {
        avl.insert(make_pair(arr[i],j));
        avl.print();
        cout << endl;
        ++j;
    }
}

TEST(insert, insert_srotR_root) {
    AVLTree<int, char> avl;
    int arr[3] = {44,62,78};
    char j = 'A';
    for (int i=0; i < 3; ++i) {
        avl.insert(make_pair(arr[i],j));
        avl.print();
        cout << endl;
        ++j;
    }
}

// no T
TEST(insert, insert_srotL_simple) {
    AVLTree<int, char> avl;
    int arr[5] = {44,17,62,16,15};
    char j = 'A';
    for (int i=0; i < 5; ++i) {
        avl.insert(make_pair(arr[i],j));
        avl.print();
        cout << endl;
        ++j;
    }
}

TEST(insert, insert_srotL_complex) {
    AVLTree<int, char> avl;
    int arr[9] = {40,62,30,60,35,25,26,20,17};
    char j = 'A';
    for (int i=0; i < 9; ++i) {
        avl.insert(make_pair(arr[i],j));
        avl.print();
        cout << endl;
        ++j;
    }
}

TEST(insert, insert_srotL_root) {
    AVLTree<int, char> avl;
    int arr[3] = {44,17,2};
    char j = 'A';
    for (int i=0; i < 3; ++i) {
        avl.insert(make_pair(arr[i],j));
        avl.print();
        cout << endl;
        ++j;
    }
}

// no T1, T2
TEST(insert, insert_drotLR_simple) {
    AVLTree<int, char> avl;
    int arr[5] = {44,17,78,70,72};
    char j = 'A';
    for (int i=0; i < 5; ++i) {
        avl.insert(make_pair(arr[i],j));
        avl.print();
        cout << endl;
        ++j;
    }
}

TEST(insert, insert_drotLR_complex) {
    AVLTree<int, char> avl;
    int arr[9] = {44,17,78,52,80,15,50,55,57};
    char j = 'A';
    for (int i=0; i < 9; ++i) {
        avl.insert(make_pair(arr[i],j));
        avl.print();
        cout << endl;
        ++j;
    }
}

TEST(insert, insert_drotLR_root) {
    AVLTree<int, char> avl;
    int arr[3] = {44,78,72};
    char j = 'A';
    for (int i=0; i < 3; ++i) {
        avl.insert(make_pair(arr[i],j));
        avl.print();
        cout << endl;
        ++j;
    }
}

// no T1, T2
TEST(insert, insert_drotRL_simple) {
    AVLTree<int, char> avl;
    int arr[5] = {44,17,78,40,20};
    char j = 'A';
    for (int i=0; i < 5; ++i) {
        avl.insert(make_pair(arr[i],j));
        avl.print();
        cout << endl;
        ++j;
    }
}

TEST(insert, insert_drotRL_complex) {
    AVLTree<int, char> avl;
    int arr[9] = {44,22,78,30,80,10,35,27,25};
    char j = 'A';
    for (int i=0; i < 9; ++i) {
        avl.insert(make_pair(arr[i],j));
        avl.print();
        cout << endl;
        ++j;
    }
}

TEST(insert, insert_drotRL_root) {
    AVLTree<int, char> avl;
    int arr[3] = {44,78,72};
    char j = 'A';
    for (int i=0; i < 3; ++i) {
        avl.insert(make_pair(arr[i],j));
        avl.print();
        cout << endl;
        ++j;
    }
}

TEST(remove, remove_srot) {
    AVLTree<int, char> avl;
    int arr[15] = {44,17,62,5,32,50,78,30,48,54,69,88,45,80,90};
    char j = 'A';
    for (int i=0; i < 15; ++i) {
        avl.insert(make_pair(arr[i],j));
        ++j;
    }

    cout << "before remove 54" << endl;
    avl.print();
    avl.remove(54);
    cout << "after remove & rotate" << endl;
    avl.print();
}

TEST(remove, remove_drot) {
    AVLTree<int, char> avl;
    int arr[15] = {44,17,62,5,32,50,78,30,48,54,69,88,52,80,90};
    char j = 'A';
    for (int i=0; i < 15; ++i) {
        avl.insert(make_pair(arr[i],j));
        ++j;
    }

    cout << "before remove 48" << endl;
    avl.print();
    avl.remove(48);
    cout << "after remove & rotate" << endl;
    avl.print();
}

TEST(remove, remove_multiple) {
    AVLTree<int, char> avl;
    int arr[15] = {44,17,62,5,32,50,78,30,48,54,69,88,45,80,90};
    char j = 'A';
    for (int i=0; i < 15; ++i) {
        avl.insert(make_pair(arr[i],j));
        ++j;
    }

    cout << "before remove 5" << endl;
    avl.print();
    avl.remove(5);
    cout << "after remove & rotate" << endl;
    avl.print();
}

TEST(remove, remove_root) {
    AVLTree<int, char> avl;
    avl.insert(make_pair(5,'A'));

    cout << "before remove 5" << endl;
    avl.print();
    avl.remove(5);
    cout << "after remove & rotate" << endl;
    avl.print();
}
