#include "gtest/gtest.h"
#include "splay.h"
#include <utility>
#include <iostream>
#include <vector>

using namespace std;

TEST(example, example) {
    SplayTree<int, char> spl;
    char j = 'A';
    for (int i=0; i < 8; ++i) {
        spl.insert(make_pair(i,j));
        ++j;
    }
    spl.print();

    spl.remove(0);
    spl.print();

    spl.insert(make_pair(8,'Z'));
    spl.print();

    spl.remove(4);
    spl.print();
}

// no T
TEST(splay, splay_srotR2_simple) {
    SplayTree<int, char> spl;
    spl.insert(make_pair(3,'A'));
    spl.print();
    cout << endl;
    
    spl.insert(make_pair(5,'B'));
    spl.print();
}

TEST(splay, splay_srotR2_complex) {
    SplayTree<int, char> spl;
    char j = 'A';
    for (int i=0; i < 8; ++i) {
        spl.insert(make_pair(i,j));
        ++j;
    }
    spl.remove(0);
    spl.print();

    spl.remove(7);
    spl.print();
}

TEST(splay, splay_dsrotL) {
    SplayTree<int, char> spl;
    char j = 'A';
    for (int i=0; i < 8; ++i) {
        spl.insert(make_pair(i,j));
        ++j;
    }
    spl.remove(0);
    spl.print();

    spl.remove(3);
    spl.print();
}

TEST(splay, splay_drotRL) {
    SplayTree<int, char> spl;
    char j = 'A';
    for (int i=0; i < 8; ++i) {
        spl.insert(make_pair(i,j));
        ++j;
    }
    spl.remove(0);
    spl.print();
    spl.remove(4);
    spl.print();
}

TEST(splay, splay_already_root) {
    SplayTree<int, char> spl;
    char j = 'A';
    for (int i=0; i < 8; ++i) {
        spl.insert(make_pair(i,j));
        ++j;
    }
    spl.remove(0);
    spl.remove(3);
    spl.print();

    spl.remove(2);
    spl.print();
}