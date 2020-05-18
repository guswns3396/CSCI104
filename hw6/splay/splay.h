#ifndef SPLAY_H
#define SPLAY_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include "../bst/bst.h"

/**
* A templated binary search tree implemented as a Splay tree.
*/
template <class Key, class Value>
class SplayTree : public BinarySearchTree<Key, Value>
{
public:
	// Methods for inserting/removing elements from the tree. You must implement
	// both of these methods.
	SplayTree();
	virtual ~SplayTree();
	virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
	void remove(const Key& key);
	int report() const;

private:
	/* You'll need this for problem 5. Stores the total number of inserts where the
	   node was added at level strictly worse than 2*log n (n is the number of nodes
	   including the added node. The root is at level 0). */
	int badInserts;
	// number of total nodes
	int size;

	/* Helper functions are encouraged. */
	void splay(Node<Key, Value>* n);
	// zig-zig
	Node<Key, Value>* dsrotL(Node<Key, Value>* z);
	Node<Key, Value>* dsrotR(Node<Key, Value>* z);
	// single rotation w 2 nodes
	Node<Key, Value>* srotL2(Node<Key, Value>* y);
	Node<Key, Value>* srotR2(Node<Key, Value>* y);

	void getLevel(Node<Key, Value>* n, int& level);
	// helper to calculate 2logn vs level
	bool isBadInsert(int n, int level);

};

/*
--------------------------------------------
Begin implementations for the SplayTree class.
--------------------------------------------
*/

template<typename Key, typename Value>
SplayTree<Key, Value>::SplayTree() : badInserts(0) {
	this->size = 0;
}

template<typename Key, typename Value>
SplayTree<Key, Value>::~SplayTree() {

}

template<typename Key, typename Value>
int SplayTree<Key, Value>::report() const {
	return badInserts;
}

/**
* Insert function for a key value pair. Finds location to insert the node and then splays it to the top.
*/
template<typename Key, typename Value>
void SplayTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
	// insert according to BST
	
	Node<Key, Value>* n = NULL;
	// edge case
	if (this->mRoot == NULL) {
		// create node
		Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
		this->mRoot = newNode;
		++size;
		return;
	}
	// update
	else if (this->mRoot->getKey() == keyValuePair.first) {
		this->mRoot->setValue(keyValuePair.second);
		return;
	}
	else{
		// check if already in tree
		if (this->internalFind(keyValuePair.first) == NULL) {
			++size;
		}
		n = this->helpInsert(keyValuePair, this->mRoot);
	}

	// get level of n (whether update or insert)
	// update can never be worse than 2logn
	int level = 0;
	getLevel(n, level);

	// calculate if bad insert
	if (isBadInsert(size, level)) {
		++badInserts;
	}

	// splay n to top
	splay(n);

}

/**
* Remove function for a given key. Finds the node, reattaches pointers, and then splays the parent
* of the deleted node to the top.
*/
template<typename Key, typename Value>
void SplayTree<Key, Value>::remove(const Key& key)
{
	// get the parent node of where removed node was swapped to
		// if n was leaf => n->parent
		// if n had 1 child => n->parent
		// if n has 2 children => 2 cases
			// adjacent => suc
			// if not => suc->parent
	Node<Key, Value>* parent = NULL;
	Node<Key, Value>* n = BinarySearchTree<Key,Value>::internalFind(key);
	// if not found
	if (n == NULL) {
		return;
	}

	if (n->getLeft() == NULL && n->getRight() == NULL) {
		parent = n->getParent();
	}
	else if (n->getLeft() == NULL || n->getRight() == NULL) {
		parent = n->getParent();
	}
	else {
		Node<Key, Value>* suc = this->findSuc(n);
		// if adjacent
		if (suc->getParent() == n) {
			parent = suc;
		}
		else {
			parent = suc->getParent();
		}
	}
	// remove according to BST
	BinarySearchTree<Key, Value>::remove(key);

	// splay
	splay(parent);
}

template<typename Key, typename Value>
void SplayTree<Key, Value>::splay(Node<Key, Value>* x) {
	// check if n is NULL
	if (x == NULL) {
		return;
	}
	// base case
	if (x == this->mRoot) {
		return;
	}

	// find y
	Node<Key, Value>* y = x->getParent();
	// see if z exists
	Node<Key, Value>* z = y->getParent();
	// new node to be splayed
	Node<Key, Value>* n = NULL;

	// if z exists => determine zig-zag or zig-zig
	if (z) {
		// a => first left (0) or right (1)
		// b => second left (0) or right (1)
		int a;
		int b;
		if (z->getLeft() == y) {
			a = 0;
		}
		else {
			a = 1;
		}
		if (y->getLeft() == x) {
			b = 0;
		}
		else {
			b = 1;
		}

		// single rotation
		if (a == b) {
			// left
			if (a == 0) {
				n = dsrotL(z);
			}
			// right
			else {
				n = dsrotR(z);
			}
		}
		// double rotation
		else {
			// left-right
			if (a == 0) {
				n = this->drotLR(z);
			}
			// right-left
			else {
				n = this->drotRL(z);
			}
		}

	}
	// single rotation w x,y
	else {
		// determine which side
		if (y->getLeft() == x) {
			n = srotL2(y);
		}
		else {
			n = srotR2(y);
		}
	}

	splay(n);

}

template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::dsrotL(Node<Key, Value>* z) {
	Node<Key, Value>* y = z->getLeft();
	Node<Key, Value>* x = y->getLeft();
	// do not know if these exist
	Node<Key, Value>* T1 = x->getRight();
	Node<Key, Value>* T2 = y->getRight();
	Node<Key, Value>* P = z->getParent();

	x->setParent(P);
	if (P) {
		if (P->getRight() == z) {
			P->setRight(x);
		}
		else {
			P->setLeft(x);
		}
	}
	else {
		this->mRoot = x;
	}
	z->setParent(y);
	z->setLeft(T2);
	if (T2) {
		T2->setParent(z);
	}
	y->setRight(z);
	y->setParent(x);
	x->setRight(y);
	y->setLeft(T1);
	if (T1) {
		T1->setParent(y);
	}

	return x;
}

template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::dsrotR(Node<Key, Value>* z) {
	Node<Key, Value>* y = z->getRight();
	Node<Key, Value>* x = y->getRight();
	// do not know if these exist
	Node<Key, Value>* T1 = x->getLeft();
	Node<Key, Value>* T2 = y->getLeft();
	Node<Key, Value>* P = z->getParent();

	x->setParent(P);
	if (P) {
		if (P->getRight() == z) {
			P->setRight(x);
		}
		else {
			P->setLeft(x);
		}
	}
	else {
		this->mRoot = x;
	}
	z->setParent(y);
	z->setRight(T2);
	if (T2) {
		T2->setParent(z);
	}
	y->setLeft(z);
	y->setParent(x);
	x->setLeft(y);
	y->setRight(T1);
	if (T1) {
		T1->setParent(y);
	}

	return x;
}

template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::srotL2(Node<Key, Value>* y) {
	Node<Key, Value>* x = y->getLeft();
	Node<Key, Value>* T = x->getRight();

	// y is root
	x->setParent(NULL);
	this->mRoot = x;
	y->setParent(x);
	x->setRight(y);
	y->setLeft(T);
	if (T) {
		T->setParent(y);
	}

	return x;
}

template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::srotR2(Node<Key, Value>* y) {
	Node<Key, Value>* x = y->getRight();
	Node<Key, Value>* T = x->getLeft();

	// y is root
	x->setParent(NULL);
	this->mRoot = x;
	y->setParent(x);
	x->setLeft(y);
	y->setRight(T);
	if (T) {
		T->setParent(y);
	}

	return x;
}

template<typename Key, typename Value>
void SplayTree<Key, Value>::getLevel(Node<Key, Value>* n, int& level) {
	// edge case
	if (n == NULL) {
		return;
	}
	// base case
	if (n == this->mRoot) {
		return;
	}

	++level;
	getLevel(n->getParent(), level);
}

template<typename Key, typename Value>
bool SplayTree<Key, Value>::isBadInsert(int n, int level) {
	int val = (int)(2 * std::log2(n));
	if (level > val) {
		return true;
	}
	else {
		return false;
	}
}
/*
------------------------------------------
End implementations for the SplayTree class.
------------------------------------------
*/

#endif
