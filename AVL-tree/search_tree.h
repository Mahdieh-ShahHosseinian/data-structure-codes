/*****************************************
* Shahrood User ID:  9820093
* Submitted for Data Structure Course
* Department of Computer Engineering and IT
* Shahrood University of Technology
*
* By submitting this file, I affirm that
* I am the author of all modifications to
* the provided code.
*****************************************/

#ifndef SEARCH_TREE_H
#define SEARCH_TREE_H

#include<iostream>
#include<algorithm>
#include <assert.h>
#include "exception.h"
using namespace std;

class SearchTree {
private:
	class Node {
	public:
		int nodeValue;
		int treeHeight;

		// The left and right sub-trees
		Node* leftTree;
		Node* rightTree;

		// Hint as to how you can create your iterator
		// Point to the previous and next nodes in linear order
		Node* previousNode;
		Node* nextNode;

		// Member functions
		Node(int const&);

		void updateHeight();

		int height() const;
		bool isLeaf() const;
		Node* front();
		Node* back();
		Node* find(int const&);

		void clear();
		// YOU CAN change the return type of these two functions if you want to!
		bool insert(int const&, Node*& toThis);
		bool erase(int const&, Node*& toThis);

		// extra methods:

		// DFS
		void preOrder(Node* node, ofstream& out) const;
		void inOrder(Node* node, ofstream& out) const;
		void postOrder(Node* node, ofstream& out) const;

		int diffrence();
		Node* balance();
		Node* RR();
		Node* LL();
		Node* RL();
		Node* LR();
	};

	Node* rootNode;
	int treeSize;

	// Hint as to how to start your linked list of the nodes in order 
	Node* frontSentinel;
	Node* backSentinel;

public:
	class Iterator {
	private:
		SearchTree* containingTree;
		Node* currentNode;
		bool isEnd;

		// The constructor is private so that only the search tree can create an iterator
		Iterator(SearchTree* tree, Node* startingNode);

	public:
		// DO NOT CHANGE THE SIGNATURES FOR ANY OF THESE
		int operator*() const;
		Iterator& operator++();
		Iterator& operator--();
		bool operator==(Iterator const& rhs) const;
		bool operator!=(Iterator const& rhs) const;

		// Make the search tree a friend so that it can call the constructor
		friend class SearchTree;
	};

	// DO NOT CHANGE THE SIGNATURES FOR ANY OF THESE
	SearchTree();
	~SearchTree();

	bool empty() const;
	int size() const;
	int height() const;
	void printDFSWithHeights(ofstream&) const;

	int front() const;
	int back() const;

	Iterator begin();
	Iterator end();
	Iterator rbegin();
	Iterator rend();
	Iterator find(int const&);

	void clear();
	bool insert(int const&);
	bool erase(int const&);
};

//////////////////////////////////////////////////////////////////////
//                Search Tree Public Member Functions               //
//////////////////////////////////////////////////////////////////////

// The initialization of the front and back sentinels is a hint
SearchTree::SearchTree() :
	rootNode(nullptr),
	treeSize(0),
	frontSentinel(new SearchTree::Node(0)),
	backSentinel(new SearchTree::Node(0)) {
	frontSentinel->nextNode = backSentinel;
	backSentinel->previousNode = frontSentinel;
}

SearchTree::~SearchTree() {
	clear();
}

bool SearchTree::empty() const {
	return (rootNode == nullptr);
}

int SearchTree::size() const {
	return treeSize;
}

int SearchTree::height() const {
	return rootNode->height();
}

// print each node value and height like this: START->[value, height]->[value, height]->END
void SearchTree::printDFSWithHeights(ofstream& out) const {
	out << "START->";
	rootNode->preOrder(rootNode, out);
	out << "END" << endl;
}

// P L R
void SearchTree::Node::preOrder(Node* node, ofstream& out) const{

	if (node == nullptr) return;
	out << "[" << node->nodeValue << ", " << node->treeHeight << "]->";
	preOrder(node->leftTree, out);
	preOrder(node->rightTree, out);
}

// L P R
void SearchTree::Node::inOrder(Node* node, ofstream& out) const{

	if (node == nullptr) return;
	inOrder(node->leftTree, out);
	out << node->nodeValue << "->";
	inOrder(node->rightTree, out);
}

// L R P
void SearchTree::Node::postOrder(Node* node, ofstream& out) const{

	if (node == nullptr) return;
	postOrder(node->leftTree, out);
	postOrder(node->rightTree, out);
	out << node->nodeValue << "->";
}

int SearchTree::front() const {
	if (empty()) {
		throw Underflow();
	}
	return rootNode->front()->nodeValue;
}

int SearchTree::back() const {
	if (empty()) {
		throw Underflow();
	}

	return rootNode->back()->nodeValue;
}

SearchTree::Iterator SearchTree::begin() {
	return empty() ? Iterator(this, backSentinel) : Iterator(this, rootNode->front());
}

SearchTree::Iterator SearchTree::end() {
	return Iterator(this, backSentinel);
}

SearchTree::Iterator SearchTree::rbegin() {
	return empty() ? Iterator(this, frontSentinel) : Iterator(this, rootNode->back());
}

SearchTree::Iterator SearchTree::rend() {
	return Iterator(this, frontSentinel);
}

SearchTree::Iterator SearchTree::find(int const& val) {
	if (empty()) {
		return Iterator(this, backSentinel);
	}

	SearchTree::Node* searchResult = rootNode->find(val);

	if (searchResult == nullptr) {
		return Iterator(this, backSentinel);
	}
	else {
		return Iterator(this, searchResult);
	}
}

void SearchTree::clear() {
	if (!empty()) {
		rootNode->clear();
		rootNode = nullptr;
		treeSize = 0;
	}

	// Reinitialize the sentinels
	frontSentinel->nextNode = backSentinel;
	backSentinel->previousNode = frontSentinel;
}

// after inserting every single node ---> we need to update sentinels!
bool SearchTree::insert(int const& val) {

	if (empty()) {
		rootNode = new SearchTree::Node(val);
		treeSize = 1;

		rootNode->nextNode = backSentinel;
		backSentinel->previousNode = rootNode;

		rootNode->previousNode = frontSentinel;
		frontSentinel->nextNode = rootNode;

		return true;
	}
	else if (rootNode->insert(val, rootNode)) {
		++treeSize;

		rootNode->back()->nextNode = backSentinel;
		backSentinel->previousNode = rootNode->back();

		rootNode->front()->previousNode = frontSentinel;
		frontSentinel->nextNode = rootNode->front();

		return true;
	}
	else {
		return false;
	}
}

// after erasing every single node ---> we need to update sentinels!
// notice, if the tree be empty ---> we need to set sentinels to the default
bool SearchTree::erase(int const& val) {
	if (!empty() && rootNode->erase(val, rootNode)) {
		--treeSize;

		if (empty()) { // set to default
			frontSentinel->nextNode = backSentinel;
			backSentinel->previousNode = frontSentinel;
			return true;
		}

		rootNode->back()->nextNode = backSentinel;
		backSentinel->previousNode = rootNode->back();

		rootNode->front()->previousNode = frontSentinel;
		frontSentinel->nextNode = rootNode->front();

		return true;
	}
	else {
		return false;
	}
}

//////////////////////////////////////////////////////////////////////
//                   Node Public Member Functions                   //
//////////////////////////////////////////////////////////////////////

SearchTree::Node::Node(int const& val) :
	nodeValue(val),
	leftTree(nullptr),
	rightTree(nullptr),
	nextNode(nullptr),
	previousNode(nullptr),
	treeHeight(0) {
	// does nothing
}

void SearchTree::Node::updateHeight() {
	treeHeight = max(leftTree->height(), rightTree->height()) + 1;
}

int SearchTree::Node::height() const {
	return (this == nullptr) ? -1 : treeHeight;
}

// Return true if the current node is a leaf node, false otherwise
bool SearchTree::Node::isLeaf() const {
	return ((leftTree == nullptr) && (rightTree == nullptr));
}

// Return a pointer to the front node
SearchTree::Node* SearchTree::Node::front() {
	return (leftTree == nullptr) ? this : leftTree->front();
}

// Return a pointer to the back node
SearchTree::Node* SearchTree::Node::back() {
	return (rightTree == nullptr) ? this : rightTree->back();
}

SearchTree::Node* SearchTree::Node::find(int const& val) {
	if (val == nodeValue) {
		return this;
	}
	else if (val < nodeValue) {
		return (leftTree == nullptr) ? nullptr : leftTree->find(val);
	}
	else {
		return (rightTree == nullptr) ? nullptr : rightTree->find(val);
	}
}

// Recursively clear the tree
void SearchTree::Node::clear() {
	if (leftTree != nullptr) {
		leftTree->clear();
	}
	if (rightTree != nullptr) {
		rightTree->clear();
	}
	delete this;
}

// insert a new node! would be a left/right child, depends on...
// the previous/next node of the related nodes will be set or update
// and!! balance()! for making it an avl tree...
bool SearchTree::Node::insert(int const& val, SearchTree::Node*& toThis) {
	if (val < nodeValue) {
		if (leftTree == nullptr) {
			leftTree = new SearchTree::Node(val);
			leftTree->previousNode = toThis->previousNode;
			leftTree->nextNode = toThis;

			if (toThis->previousNode != nullptr) toThis->previousNode->nextNode = leftTree;
			toThis->previousNode = leftTree;

			toThis = balance();
			toThis->updateHeight();
			return true;
		}
		else {
			if (leftTree->insert(val, leftTree)) {
				toThis = balance();
				toThis->updateHeight(); // why without toThis-> doesn't work!
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if (val > nodeValue) {
		if (rightTree == nullptr) {
			rightTree = new SearchTree::Node(val);
			rightTree->previousNode = toThis;
			rightTree->nextNode = toThis->nextNode;

			if (toThis->nextNode != nullptr) toThis->nextNode->previousNode = rightTree;
			toThis->nextNode = rightTree;

			toThis = balance();
			toThis->updateHeight();
			return true;
		}
		else {
			if (rightTree->insert(val, rightTree)) {
				toThis = balance();
				toThis->updateHeight();
				return true;
			}
			else {
				return false;
			}
		}
	}
	else {
		return false;
	}
}

// when you remove a node... you have to set/update previous/next node of remain nodes again
// balance() is requierd! it's an avl tree
bool SearchTree::Node::erase(int const& val, SearchTree::Node*& toThis) {
	if (val < nodeValue) {
		if (leftTree == nullptr) {
			return false;
		}
		else {
			if (leftTree->erase(val, leftTree)) {
				toThis = balance();
				toThis->updateHeight();
				return true;
			}

			return false;
		}
	}
	else if (val > nodeValue) {
		if (rightTree == nullptr) {
			return false;
		}
		else {
			if (rightTree->erase(val, rightTree)) {
				toThis = balance();
				toThis->updateHeight();
				return true;
			}

			return false;
		}
	}
	else {
		assert(val == nodeValue);

		if (isLeaf()) {
			toThis->previousNode->nextNode = toThis->nextNode;
			toThis->nextNode->previousNode = toThis->previousNode;

			toThis = nullptr;
			delete this;
		}
		else if (leftTree == nullptr) {
			toThis->previousNode->nextNode = toThis->nextNode;
			toThis->nextNode->previousNode = toThis->previousNode;

			toThis = rightTree;
			delete this;
		}
		else if (rightTree == nullptr) {
			toThis->previousNode->nextNode = toThis->nextNode;
			toThis->nextNode->previousNode = toThis->previousNode;

			toThis = leftTree;
			delete this;
		}
		else {
			nodeValue = rightTree->front()->nodeValue;
			rightTree->erase(nodeValue, rightTree); // call back
			toThis = balance();
			toThis->updateHeight();
		}
		return true;
	}
}

// the diffrence of the heights L-R
int SearchTree::Node::diffrence() {
	return leftTree->height() - rightTree->height();
}

// if you want to make the tree balance() you need to check the diffrences of heights and
// if it need -> make a rotate
SearchTree::Node* SearchTree::Node::balance() {

	switch (diffrence())
	{
	case 2:
		if (leftTree->diffrence() > 0) return LL();
		else return LR();
		break;
	case -2:
		if (rightTree->diffrence() < 0) return RR();
		else return RL();
		break;
	default:
		return this;
	}
}

/*
 *         (-2) a
 *             / \
 *                b 
 *               / \
 *                  c
 *                 / \
*/
SearchTree::Node* SearchTree::Node::RR() {
	Node* temp = rightTree;
	rightTree = temp->leftTree; updateHeight();
	temp->leftTree = this;
	return temp;
}

// just make sure to do updateHeight() for the nodes which are not a new root

/*
 *         (+2) a
 *             / \
 *            b
 *           / \
 *          c
 *         / \
*/
SearchTree::Node* SearchTree::Node::LL() {
	Node* temp = leftTree;
	leftTree = temp->rightTree; updateHeight();
	temp->rightTree = this;
	return temp;
}

/*
 *         (+2) a
 *             / \
 *            b
 *           / \
 *              c
 *             / \
*/
SearchTree::Node* SearchTree::Node::LR() {

	Node* temp = leftTree->rightTree;
	Node* rightChildTemp = leftTree->rightTree->rightTree;
	Node* leftChildTemp = leftTree->rightTree->leftTree;

	leftTree->rightTree->rightTree = this;
	leftTree->rightTree->leftTree = leftTree;

	leftTree->rightTree = leftChildTemp; leftTree->updateHeight();
	leftTree = rightChildTemp; updateHeight();
	return temp;
}

/*
 *         (-2) a
 *             / \
 *                b
 *               / \
 *              c
 *             / \
*/
SearchTree::Node* SearchTree::Node::RL() {

	Node* temp = rightTree->leftTree;
	Node* rightChildTemp = rightTree->leftTree->rightTree;
	Node* leftChildTemp = rightTree->leftTree->leftTree;

	rightTree->leftTree->rightTree = rightTree;
	rightTree->leftTree->leftTree = this;

	rightTree->leftTree = rightChildTemp; rightTree->updateHeight();
	rightTree = leftChildTemp; updateHeight();
	return temp;
}

//////////////////////////////////////////////////////////////////////
//                   Iterator Private Constructor                   //
//////////////////////////////////////////////////////////////////////

SearchTree::Iterator::Iterator(SearchTree* tree, SearchTree::Node* startingNode) :
	containingTree(tree),
	currentNode(startingNode) {
	// This is done for you...
	// Does nothing...
}

//////////////////////////////////////////////////////////////////////
//                 Iterator Public Member Functions                 //
//////////////////////////////////////////////////////////////////////

int SearchTree::Iterator::operator*() const {
	// This is done for you...
	return currentNode->nodeValue;
}

// Update the current node to the node containing the next higher value, If we are already at end do nothing
// Your implementation here, do not change the return value
// so the current node should go up
SearchTree::Iterator& SearchTree::Iterator::operator++() {
	currentNode = currentNode->nextNode;
	return *this;
}

// Update the current node to the node containing the next smaller value, If we are already at either rend, do nothing
// Your implementation here, do not change the return value
// so the current node should go back
SearchTree::Iterator& SearchTree::Iterator::operator--() {
	currentNode = currentNode->previousNode;
	return *this;
}

bool SearchTree::Iterator::operator==(SearchTree::Iterator const& rhs) const {
	// This is done for you...
	return (currentNode == rhs.currentNode);
}

bool SearchTree::Iterator::operator!=(SearchTree::Iterator const& rhs) const {
	// This is done for you...
	return (currentNode != rhs.currentNode);
}

#endif
