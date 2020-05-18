#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
* A templated class for a Node in a search tree. The getters for parent/left/right are virtual so that they
* can be overridden for future kinds of search trees, such as Red Black trees, Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node
{
public:
	Node(const Key& key, const Value& value, Node<Key, Value>* parent);
	virtual ~Node();

	const std::pair<Key, Value>& getItem() const;
	std::pair<Key, Value>& getItem();
	const Key& getKey() const;
	const Value& getValue() const;
	Key& getKey();
	Value& getValue();

	virtual Node<Key, Value>* getParent() const;
	virtual Node<Key, Value>* getLeft() const;
	virtual Node<Key, Value>* getRight() const;

	void setParent(Node<Key, Value>* parent);
	void setLeft(Node<Key, Value>* left);
	void setRight(Node<Key, Value>* right);
	void setValue(const Value &value);

protected:
	std::pair<Key, Value> mItem;
	Node<Key, Value>* mParent;
	Node<Key, Value>* mLeft;
	Node<Key, Value>* mRight;
};

/* 
	-----------------------------------------
	Begin implementations for the Node class.
	-----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent)
	: mItem(key, value)
	, mParent(parent)
	, mLeft(NULL)
	, mRight(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the destructor in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<Key, Value>& Node<Key, Value>::getItem() const
{
	return mItem;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& Node<Key, Value>::getItem()
{
	return mItem;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
	return mItem.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
	return mItem.second;
}

/**
* A non-const getter for the key.
*/
template<typename Key, typename Value>
Key& Node<Key, Value>::getKey()
{
	return mItem.first;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
	return mParent;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
	return mLeft;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
	return mRight;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
	mParent = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
	mLeft = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
	mRight = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
	mItem.second = value;
}

/* 
	---------------------------------------
	End implementations for the Node class.
	---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();

	virtual void insert(const std::pair<Key, Value>& keyValuePair);
	void clear();
	void print() const;
	virtual void remove(const Key& key);

public:
	/**
	* An internal iterator class for traversing the contents of the BST.
	*/
	class iterator
	{
	public:
		iterator(Node<Key,Value>* ptr);
		iterator();

		std::pair<Key,Value>& operator*();
		std::pair<Key,Value>* operator->();

		bool operator==(const iterator& rhs) const;
		bool operator!=(const iterator& rhs) const;
		iterator& operator=(const iterator& rhs);

		iterator& operator++();

	protected:
		Node<Key, Value>* mCurrent;
		friend class BinarySearchTree<Key, Value>;
	};

public:
	iterator begin() const;
	iterator end() const;
	iterator find(const Key& key) const;

protected:
	Node<Key, Value>* internalFind(const Key& key) const;
	Node<Key, Value>* getSmallestNode() const;
	void printRoot (Node<Key, Value>* root) const;

	/* Helper functions are strongly encouraged to help separate the problem
	   into smaller pieces. You should not need additional data members. */

	// helper function for clear()
	void helpClear(Node<Key, Value>* root);
	// helper function for internalFind()
	Node<Key, Value>* helpInternalFind(Node<Key, Value>* root, const Key& key) const;
	// helper function for insert()
	virtual Node<Key, Value>* helpInsert(const std::pair<Key, Value>& pair, Node<Key, Value>* root);
	
	Node<Key, Value>* findSuc(Node<Key, Value>* root) const;
	void removeLeaf(Node<Key, Value>* n, bool hasP);
	void removeOne(Node<Key, Value>* child, bool hasP);
	void removeTwo(Node<Key, Value>* n);
	void swapNodes(Node<Key, Value>* a, Node<Key, Value>* b);
	void edgeSwap(Node<Key, Value>* n, Node<Key, Value>* s);
	void normalSwap(Node<Key, Value>* n, Node<Key, Value>* s);

	Node<Key, Value>* srotL(Node<Key, Value>* z);
	Node<Key, Value>* srotR(Node<Key, Value>* z);
	Node<Key, Value>* drotLR(Node<Key, Value>* z);
	Node<Key, Value>* drotRL(Node<Key, Value>* z);

protected:
	Node<Key, Value>* mRoot;

};

/* 
	---------------------------------------------------------------
	Begin implementations for the BinarySearchTree::iterator class.
	---------------------------------------------------------------
*/ 

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
	: mCurrent(ptr)
{

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
	: mCurrent(NULL)
{

}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*()
{
	return mCurrent->getItem(); 
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->()
{
	return &(mCurrent->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator& rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++()
{
	if(mCurrent->getRight() != NULL)
	{
		mCurrent = mCurrent->getRight();
		while(mCurrent->getLeft() != NULL)
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if(mCurrent->getRight() == NULL)
	{
		Node<Key, Value>* parent = mCurrent->getParent();
		while(parent != NULL && mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
	return *this;
}

/* 
	-------------------------------------------------------------
	End implementations for the BinarySearchTree::iterator class.
	-------------------------------------------------------------
*/

/* 
	-----------------------------------------------------
	Begin implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
	mRoot = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
	clear();
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin() const
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end() const
{
	BinarySearchTree<Key, Value>::iterator end(NULL);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& key) const
{
	Node<Key, Value>* curr = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(curr);
	return it;
}

/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when
* inserting.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
	// edge case
	if (mRoot == NULL) {
		// create node
		Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
		mRoot = newNode;
		return;
	}
	helpInsert(keyValuePair, mRoot);
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key) {
	// find node
	Node<Key, Value>* n = internalFind(key);

	// if not found
	if (n == NULL) {
		return;
	}

	// points of contact
	// deleting node => left, right, parent
	// child node(s) => parent
	// parent node => left/right

	bool hasP = n->getParent();

	// if leaf node => no child node to consider
	if (n->getLeft() == NULL && n->getRight() == NULL) {
		removeLeaf(n, hasP);
		return;
	}

	// if one node
	if (n->getLeft() == NULL) {
		removeOne(n->getRight(), hasP);
	}
	else if (n->getRight() == NULL) {
		removeOne(n->getLeft(), hasP);
	}
	// if two nodes
	else {
		removeTwo(n);
	}
	return;


}

/**
* A method to remove all contents of the tree and reset the values in the tree
* for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	// edge case
	if (mRoot == NULL) {
		return;
	}
	helpClear(mRoot);
	mRoot = NULL;
	return;
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const
{
	// edge case
	if (mRoot == NULL) {
		return NULL;
	}
	Node<Key, Value>* n = mRoot;
	while (n->getLeft()) {
		n = n->getLeft();
	}

	return n;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
	return helpInternalFind(mRoot, key);
}

/**
* Helper function to print the tree's contents
*/
/*template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::printRoot (Node<Key, Value>* root) const
{
	if (root != NULL)
	{
		std::cout << "[";
		printRoot (root->getLeft());
		std::cout << " (" << root->getKey() << ", " << root->getValue() << ") ";
		printRoot (root->getRight());
		std::cout << "]";
	}
}*/

// helper function for clear()
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::helpClear(Node<Key, Value>* root) {
	// base case
	// leaf node
	if (root->getLeft() == NULL && root->getRight() == NULL) {
		delete root;
		return;
	}
	// recursive case
	if (root->getLeft()) {
		helpClear(root->getLeft());
	}
	if (root->getRight()) {
		helpClear(root->getRight());
	}
	delete root;
}

// helper for internalFind()
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::helpInternalFind(Node<Key, Value>* root, const Key& key) const {
	// base case
	// key of root is equal to key or root is NULL
	if (root == NULL) {
		return root;
	}
	// recursive case
	if (root->getKey() < key) {
		return helpInternalFind(root->getRight(), key);
	}
	else if (root->getKey() > key) {
		return helpInternalFind(root->getLeft(), key);
	}
	// base case => root's key == key
	else {
		return root;
	}
}

// helper for insert()
// returns most recently inserted node
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::helpInsert(const std::pair<Key, Value>& pair, Node<Key, Value>* root) {
	// node has same key or node's child is appropriate spot
	if (root->getKey() < pair.first) {
		// base case
		if (root->getRight() == NULL) {
			// instantiate node (with root as parent)
			Node<Key, Value>* newNode = new Node<Key, Value>(pair.first, pair.second, root);
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
			Node<Key, Value>* newNode = new Node<Key, Value>(pair.first, pair.second, root);
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
Node<Key, Value>* BinarySearchTree<Key, Value>::findSuc(Node<Key, Value>* root) const {
	Node<Key, Value>* n = NULL;
	if (root->getRight()) {
		n = root->getRight();
		while (n->getLeft() != NULL) {
			n = n->getLeft();
		}
	}
	
	return n;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::removeLeaf(Node<Key, Value>* n, bool hasP) {
	// node NOT root
	// update left/right of parent
	if (hasP) {
		if (n->getParent()->getRight() == n) {
			n->getParent()->setRight(NULL);
		}
		else {
			n->getParent()->setLeft(NULL);
		}
	}
	// node root
	else {
		mRoot = NULL;
	}
	delete n;
	n = NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::removeOne(Node<Key, Value>* child, bool hasP) {
	Node<Key, Value>* n = child->getParent();
	// update parent
	if (hasP) {
		if (n->getParent()->getRight() == n) {
			n->getParent()->setRight(child);
		}
		else {
			n->getParent()->setLeft(child);
		}
	}
	// n is root
	else {
		mRoot = child;
	}
	// update child
	child->setParent(n->getParent());
	delete n;
	n = NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::removeTwo(Node<Key, Value>* n) {
	// find successor
	// swap with successor
		// successor either leaf node or only has 1 child
	// remove

	Node<Key, Value>* s = findSuc(n);
	swapNodes(n,s);

	bool hasP = n->getParent();

	// if leaf node => no child node to consider
	if (n->getLeft() == NULL && n->getRight() == NULL) {
		removeLeaf(n, hasP);
	}
	// if one node
	else {
		if (n->getLeft() == NULL) {
			removeOne(n->getRight(), hasP);
		}
		else {
			removeOne(n->getLeft(), hasP);
		}
	}

}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::swapNodes(Node<Key, Value>* n, Node<Key, Value>* s) {
	// n has 2 children!
		// s is somewhere on the right
	// s is either leaf node or has 1 child
		// if has child => on the right side
	// n's parent may be null

	// edge case
	// if n and s adjacent
		// n->getRight() == s
	if (s->getParent() == n) {
		edgeSwap(n,s);
	}
	// zig zag
	else {
		normalSwap(n,s);
	}
	return;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::edgeSwap(Node<Key, Value>* n, Node<Key, Value>* s) {
	Node<Key, Value>* c_n = n->getLeft();
	// may not exist!!
	Node<Key, Value>* c_s = s->getRight();

	// parent of n => update left/right to s
	if (n->getParent()) {
		if (n->getParent()->getRight() == n) {
			n->getParent()->setRight(s);
		}
		else {
			n->getParent()->setLeft(s);
		}
	}
	// n is root
	else {
		mRoot = s;
	}
	// s => update parent to n->parent
	s->setParent(n->getParent());

	s->setRight(n);
	s->setLeft(c_n);
	c_n->setParent(s);
	n->setParent(s);

	n->setLeft(NULL);
	n->setRight(c_s);
	if (c_s) {
		c_s->setParent(n);
	}

	return;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::normalSwap(Node<Key, Value>* n, Node<Key, Value>* s) {
	Node<Key, Value>* c_nl = n->getLeft();
	Node<Key, Value>* c_nr = n->getRight();
	Node<Key, Value>* p_s = s->getParent();
	// unkown if exists!!
	Node<Key, Value>* c_s = s->getRight();

	// parent of n => update left/right to s
	if (n->getParent()) {
		if (n->getParent()->getRight() == n) {
			n->getParent()->setRight(s);
		}
		else {
			n->getParent()->setLeft(s);
		}
	}
	// n is root
	else {
		mRoot = s;
	}
	// s => update parent to n->parent
	s->setParent(n->getParent());
	
	// update n's parent, ps's left
	n->setParent(p_s);
	p_s->setLeft(n);

	// update n's right, s's right
	n->setRight(c_s);
	if (c_s) {
		c_s->setParent(n);
	}

	// update cnr's parent, s's right
	c_nr->setParent(s);
	s->setRight(c_nr);

	// update cnl's parent, s's left
	c_nl->setParent(s);
	s->setLeft(c_nl);

	n->setLeft(NULL);

	return;
}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::srotL(Node<Key, Value>* z) {
	Node<Key, Value>* y = z->getLeft();
	Node<Key, Value>* T = y->getRight();
	Node<Key, Value>* P = z->getParent();

	y->setParent(P);
	if (P) {
		if (P->getRight() == z) {
			P->setRight(y);
		}
		else {
			P->setLeft(y);
		}
	}
	else {
		this->mRoot = y;
	}
	z->setParent(y);
	z->setLeft(T);
	if (T) {
		T->setParent(z);
	}
	y->setRight(z);

	return y;
}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::srotR(Node<Key, Value>* z) {
	Node<Key, Value>* y = z->getRight();
	Node<Key, Value>* T = y->getLeft();
	Node<Key, Value>* P = z->getParent();

	y->setParent(P);
	if (P) {
		if (P->getRight() == z) {
			P->setRight(y);
		}
		else {
			P->setLeft(y);
		}
	}
	else {
		this->mRoot = y;
	}
	z->setParent(y);
	z->setRight(T);
	if (T) {
		T->setParent(z);
	}
	y->setLeft(z);

	return y;
}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::drotLR(Node<Key, Value>* z) {
	Node<Key, Value>* y = z->getLeft();
	Node<Key, Value>* x = y->getRight();
	Node<Key, Value>* T1 = x->getLeft();
	Node<Key, Value>* T2 = x->getRight();
	Node<Key, Value>* P = z->getParent();

	if (T2) {
		T2->setParent(z);
	}
	if (T1) {
		T1->setParent(y);
	}
	x->setParent(P);
	if (P) {
		if (P->getLeft() == z) {
			P->setLeft(x);
		}
		else {
			P->setRight(x);
		}
	}
	else {
		this->mRoot = x;
	}
	y->setParent(x);
	z->setParent(x);
	y->setRight(T1);
	x->setLeft(y);
	z->setLeft(T2);
	x->setRight(z);

	return x;
}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::drotRL(Node<Key, Value>* z) {
	Node<Key, Value>* y = z->getRight();
	Node<Key, Value>* x = y->getLeft();
	Node<Key, Value>* T1 = x->getRight();
	Node<Key, Value>* T2 = x->getLeft();
	Node<Key, Value>* P = z->getParent();

	if (T2) {
		T2->setParent(z);
	}
	if (T1) {
		T1->setParent(y);
	}
	x->setParent(P);
	if (P) {
		if (P->getLeft() == z) {
			P->setLeft(x);
		}
		else {
			P->setRight(x);
		}
	}
	else {
		this->mRoot = x;
	}
	y->setParent(x);
	z->setParent(x);
	y->setLeft(T1);
	x->setRight(y);
	z->setRight(T2);
	x->setLeft(z);

	return x;
}

/* 
	---------------------------------------------------
	End implementations for the BinarySearchTree class.
	---------------------------------------------------
*/

#include "print_bst.h"

#endif
