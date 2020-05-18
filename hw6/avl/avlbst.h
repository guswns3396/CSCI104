#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include "../bst/bst.h"

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus 
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
	// Constructor/destructor.
	AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
	virtual ~AVLNode();

	// Getter/setter for the node's height.
	int getHeight() const;
	void setHeight(int height);

	// Getters for parent, left, and right. These need to be redefined since they 
	// return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
	// for more information.
	virtual AVLNode<Key, Value>* getParent() const override;
	virtual AVLNode<Key, Value>* getLeft() const override;
	virtual AVLNode<Key, Value>* getRight() const override;

protected:
	int mHeight;
};

/*
--------------------------------------------
Begin implementations for the AVLNode class.
--------------------------------------------
*/

/**
* Constructor for an AVLNode. Nodes are initialized with a height of 0.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
	: Node<Key, Value>(key, value, parent)
	, mHeight(0)
{

}

/**
* Destructor.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* Getter function for the height. 
*/
template<typename Key, typename Value>
int AVLNode<Key, Value>::getHeight() const
{
	return mHeight;
}

/**
* Setter function for the height. 
*/
template<typename Key, typename Value>
void AVLNode<Key, Value>::setHeight(int height)
{
	mHeight = height;
}

/**
* Getter function for the parent. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
	return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
	return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
	return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*
------------------------------------------
End implementations for the AVLNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an AVL tree.
*/
template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
	// Methods for inserting/removing elements from the tree. You must implement
	// both of these methods. 
	virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
	void remove(const Key& key);
	virtual ~AVLTree();

private:
	/* Helper functions are strongly encouraged to help separate the problem
	   into smaller pieces. You should not need additional data members. */
	Node<Key, Value>* helpInsert(const std::pair<Key, Value>& pair, Node<Key, Value>* root);
	Node<Key, Value>* update(AVLNode<Key, Value>* leaf);
	bool isBalanced(AVLNode<Key, Value>* parent);
	void updateHeight(AVLNode<Key, Value>* root);

	AVLNode<Key, Value>* avlrotate(AVLNode<Key, Value>* z);
};

/*
--------------------------------------------
Begin implementations for the AVLTree class.
--------------------------------------------
*/
template<typename Key, typename Value>
AVLTree<Key, Value>::~AVLTree() {
	
}

/**
* Insert function for a key value pair. Finds location to insert the node and then balances the tree. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
	Node<Key, Value>* n = NULL;
	// edge case
	if (this->mRoot == NULL) {
		// create node
		AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
		this->mRoot = newNode;
		static_cast<AVLNode<Key, Value>*>(this->mRoot)->setHeight(1);
		return;
	}
	else if (this->mRoot->getKey() == keyValuePair.first) {
		this->mRoot->setValue(keyValuePair.second);
		return;
	}
	else {
		n = helpInsert(keyValuePair, this->mRoot);	
	}
	
	// updates tree
	update(static_cast<AVLNode<Key, Value>*>(n));
}

/**
* Remove function for a given key. Finds the node, reattaches pointers, and then balances when finished. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::remove(const Key& key)
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

	// update height
	updateHeight(static_cast<AVLNode<Key, Value>*>(parent));
	// update
		// updates height, checks imbalance, rotate if need
		// goes until root reached
	// inital check & update
	if (!isBalanced(static_cast<AVLNode<Key, Value>*>(parent))) {
		parent = avlrotate(static_cast<AVLNode<Key, Value>*>(parent));
		updateHeight(static_cast<AVLNode<Key, Value>*>(parent));
	}
	while (parent != this->mRoot) {
		parent = update(static_cast<AVLNode<Key, Value>*>(parent));
	}
}

// helper function to update tree
// updates height, checks imbalance, rotates
// returns parent node
template <typename Key, typename Value>
Node<Key, Value>* AVLTree<Key, Value>::update(AVLNode<Key, Value>* n) {
	// edge case
	// n is just inserted
	if (n->getLeft() == NULL && n->getRight() == NULL) {
		n->setHeight(1);	
	}

	// base case
	// n is root => done
	if (n == this->mRoot) {
		return this->mRoot;
	}

	// look at height of parent
	// if height of parent already greater than n 
	// make sure balanced => then return
	if (n->getParent()->getHeight() > n->getHeight()) {
		if (isBalanced(n->getParent())) {
			return n->getParent();
		}
	}
	// change height of parent
	else {
		n->getParent()->setHeight(n->getHeight() + 1);
	}

	// check if parent unbalanced
	// if not balanced => rotate then end
	// if balanced => check higher up
	if (isBalanced(n->getParent())) {
		return update(n->getParent());
	}
	else {
		AVLNode<Key, Value>* newRoot = avlrotate(static_cast<AVLNode<Key, Value>*>(n->getParent()));
		updateHeight(newRoot);
		return newRoot;
	}
}

// helper function to determine balance
// returns unbalanced node
// or NULL if balanced
template <typename Key, typename Value>
bool AVLTree<Key, Value>::isBalanced(AVLNode<Key, Value>* parent) {
	if (parent == NULL) {
		return true;
	}

	// compare height
	int h1 = 0;
	int h2 = 0;
	int diff;
	// make sure node exists
	if (parent->getLeft()) {
		h1 = parent->getLeft()->getHeight();
	}
	if (parent->getRight()) {
		h2 = parent->getRight()->getHeight();
	}

	if (h1 > h2) {
		diff = h1 - h2;
	}
	else {
		diff = h2 - h1;
	}

	// if balanced => return true
	// if not => return false
	if (diff > 1) {
		return false;;
	}
	else {
		return true;
	}

}

template<typename Key, typename Value>
Node<Key, Value>* AVLTree<Key, Value>::helpInsert(const std::pair<Key, Value>& pair, Node<Key, Value>* root) {
	// node has same key or node's child is appropriate spot
	if (root->getKey() < pair.first) {
		// base case
		if (root->getRight() == NULL) {
			// instantiate node (with root as parent)
			Node<Key, Value>* newNode = new AVLNode<Key, Value>(pair.first, pair.second, static_cast<AVLNode<Key, Value>*>(root));
			// update root
			root->setRight(newNode);
			return newNode;
		}
		// recursive case
		else {
			return helpInsert(pair, root->getRight());
		}
	}
	else if (root->getKey() > pair.first) {
		// base case
		if (root->getLeft() == NULL) {
			// instantiate node (with root as parent)
			Node<Key, Value>* newNode = new AVLNode<Key, Value>(pair.first, pair.second, static_cast<AVLNode<Key, Value>*>(root));
			// update root
			root->setLeft(newNode);
			return newNode;
		}
		// recusrive case
		else {
			return helpInsert(pair, root->getLeft());
		}
	}
	// base case
	else {
		root->setValue(pair.second);
		return root;
	}
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::avlrotate(AVLNode<Key, Value>* z) {
	// a => first left (0) or right (1)
	// b => second left (0) or right (1)
	int a;
	int b;
	AVLNode<Key, Value>* y = NULL;
	Node<Key, Value>* newRoot = NULL;

	int h1 = 0;
	int h2 = 0;
	// make sure child exists
	if (z->getLeft()) {
		h1 = z->getLeft()->getHeight();
	}
	if (z->getRight()) {
		h2 = z->getRight()->getHeight();
	}

	// find y
	if (h1 > h2) {
		y = static_cast<AVLNode<Key, Value>*>(z->getLeft());
		a = 0;
	}
	else {
		y = static_cast<AVLNode<Key, Value>*>(z->getRight());
		a = 1;
	}

	h1 = 0;
	h2 = 0;
	if (y->getLeft()) {
		h1 = y->getLeft()->getHeight();
	}
	if (y->getRight()) {
		h2 = y->getRight()->getHeight();
	}

	if (h1 > h2) {
		b = 0;
	}
	else if (h1 < h2) {
		b = 1;
	}
	// for removing => if tie => single rotation
	else {
		b = a;
	}

	// std::cout << "Before rotating" << std::endl;
	// this->print();

	// single rotation
	if (a == b) {
		// left
		if (a == 0) {
			newRoot = this->srotL(z);
		}
		// right
		else {
			newRoot = this->srotR(z);
		}
	}
	// double rotation
	else {
		// left-right
		if (a == 0) {
			newRoot = this->drotLR(z);
		}
		// right-left
		else {
			newRoot = this->drotRL(z);
		}
	}
	return static_cast<AVLNode<Key,Value>*>(newRoot);

}

template<typename Key, typename Value>
void AVLTree<Key, Value>::updateHeight(AVLNode<Key, Value>* root) {
	if (root == NULL) {
		return;
	}

	AVLNode<Key, Value>* left = root->getLeft();
	AVLNode<Key, Value>* right = root->getRight();

	int h_l = 0;
	int h_r = 0;

	int h1 = 0;
	int h2 = 0;

	if (left) {
		// make sure children exit
		if (left->getLeft()) {
			h1 = left->getLeft()->getHeight();
		}
		if (left->getRight()) {
			h2 = left->getRight()->getHeight();
		}
		// update height for left
		left->setHeight(std::max(h1, h2)+1);
		h_l = left->getHeight();
	}

	h1 = 0;
	h2 = 0;

	if (right) {
		if (right->getLeft()) {
			h1 = right->getLeft()->getHeight();
		}
		if (right->getRight()) {
			h2 = right->getRight()->getHeight();
		}
		// update height for right
		right->setHeight(std::max(h1, h2)+1);
		h_r = right->getHeight();
	}

	// update new "root"
	root->setHeight(std::max(h_l, h_r)+1);

	return;
}

/*
------------------------------------------
End implementations for the AVLTree class.
------------------------------------------
*/

#endif
