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

#ifndef ABSTRACT_TREE_H
#define ABSTRACT_TREE_H

#include <iostream>
#include "exception.h"
#include "double_linked_list.h"
#include "mystack.h"
#include"myqueue.h"
using namespace std;

class AbstractTree {
public:
	class TreeNode {
	public:
		TreeNode(int const&, TreeNode* = nullptr);
		int value() const;
		int degree() const;
		TreeNode* getParent() const;
		TreeNode* child(int const&) const;

	private:
		int nodeValue;
		TreeNode* parent;
		DoubleLinkedList<TreeNode*> children;
		friend AbstractTree;
	};

	AbstractTree(int const&);
	AbstractTree(AbstractTree const&);
	~AbstractTree();

	// Accessors
	int size() const;
	int height() const;
	bool empty() const;

	bool find(int const&);
	int count(int const&);

	// Mutators
	void push(int const&);
	void push(int*&, int const&);
	int pop();

	// Printers
	void printBFS(std::ostream&);
	void printDFS(std::ostream&);

private:
	TreeNode* root;
	int maxDegree;
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

/****************************AbstractTree*******************************/

AbstractTree::AbstractTree(int const& maxDegree) :
	root(nullptr),
	maxDegree(maxDegree) {	
}

// to copy a new tree, just push all the nodes of that tree
AbstractTree::AbstractTree(AbstractTree const& tree) :
	root(nullptr),
	maxDegree(tree.maxDegree) {
	
	if (!tree.empty()) {
		Queue<TreeNode*> queue;
		queue.push(tree.root);

		while (!queue.empty()) {

			TreeNode* currentNode = queue.pop();
			push(currentNode->nodeValue);
			for (int i = 0; i < currentNode->degree(); i++) {
				queue.push(currentNode->child(i));
			}
		}
	}
}

AbstractTree::~AbstractTree() {
	while (!empty()) pop();
}

// bfs kind, the numbers of nodes, count them
int AbstractTree::size() const {

	if (empty()) return 0;

	Queue<TreeNode*> queue;
	queue.push(root);

	int s = 0;
	while (!queue.empty()) {

		TreeNode* currentNode = queue.pop(); s++;
		for (int i = 0; i < currentNode->degree(); i++) {
			queue.push(currentNode->child(i));
		}
	}
	return s;
}

// dfs kind
// this tree is a complete tree! use this benefite and find the height
// the height in complete tree is the height of all left nodes (just first left)
int AbstractTree::height() const {

	if (empty()) return -1;
	Stack<TreeNode*> stack;
	stack.push(root);
	int h = -1;
	while (!stack.empty()) {

		TreeNode* currTreeNode = stack.top();stack.pop();
		h++;
		if (!currTreeNode->children.empty()) stack.push(currTreeNode->child(0));
	}
	return h;
}

// root make it clear
bool AbstractTree::empty() const {
	return root == nullptr;
}

// dfs kind would be easier maybe
bool AbstractTree::find(int const& val) {

	if (empty()) return false;
	Stack<TreeNode*> stack;
	stack.push(root);
	while (!stack.empty()) {

		TreeNode* currTreeNode = stack.top();stack.pop();

		if (currTreeNode->nodeValue == val) return true;

		for (int i = currTreeNode->degree() - 1; i > -1; i--) {
			stack.push(currTreeNode->child(i));
		}
	}
	return false;
}

// bfs kind, count the similar value of inut val
int AbstractTree::count(int const& val) {

	if (empty()) return 0;
	Queue<TreeNode*> queue;
	queue.push(root);

	int c = 0;
	while (!queue.empty()) {

		TreeNode* currentNode = queue.pop();
		if (currentNode->nodeValue == val) c++;
		for (int i = 0; i < currentNode->degree(); i++) {
			queue.push(currentNode->child(i));
		}
	}
	return c;
}

// look for a good place for adding a new node, remember it's a complete tree
// if the tree is empty, means you are pushing the first node, means root
void AbstractTree::push(int const& value) {

	if (empty()) {
		root = new TreeNode(value);
		return;
	}
	Queue<TreeNode*> queue;
	queue.push(root);

	while (!queue.empty()) {

		TreeNode* currentNode = queue.pop();

		if (currentNode->degree() < maxDegree) {
			currentNode->children.pushBack(new TreeNode(value, currentNode));
			return;
		}
		for (int i = 0; i < currentNode->degree(); i++) {
			queue.push(currentNode->child(i));
		}
	}
}

// just for adding multiples nodes, call above push() as much as u want to
// this could be implement better for sure
void AbstractTree::push(int*& values, int const& num) {
	for (int i = 0; i < num; i++) push(values[i]);
}

// for poping the last node... a bfs till the end of the tree, then delete that from the tree
// notice if it's root you have to make the root null and consider the root have no parent!
int AbstractTree::pop() {
	
	if (empty()) throw Underflow();

	Queue<TreeNode*> queue;
	queue.push(root);

	TreeNode* currentNode = root;
	while (!queue.empty()) {

		currentNode = queue.pop();
		for (int i = 0; i < currentNode->degree(); i++) {
			queue.push(currentNode->child(i));
		}
	}

	if (currentNode != root) {
		currentNode->getParent()->children.erase(currentNode);
	}
	else {
		root = nullptr;
	}
	int val = currentNode->nodeValue;
	delete currentNode;
	return val;
}

// with using queue
void AbstractTree::printBFS(std::ostream& out) {

	out << "START->";
	if (!empty()) {
		Queue<TreeNode*> queue;
		queue.push(root);
		while (!queue.empty()) {

			TreeNode* currTreeNode = queue.pop();
			out << currTreeNode->nodeValue << "->";
			for (int i = 0; i < currTreeNode->degree(); i++) {
				queue.push(currTreeNode->child(i));
			}
		}
	}
	out << "END" <<endl;
}

// using stack
void AbstractTree::printDFS(std::ostream& out) {

	out << "START->";
	if (!empty()) {
		Stack<TreeNode*> stack;
		stack.push(root);
		while (!stack.empty()) {

			TreeNode* currTreeNode = stack.top();stack.pop();
			out << currTreeNode->nodeValue << "->";
			for (int i = currTreeNode->degree() - 1; i > -1; i--) {
				stack.push(currTreeNode->child(i));
			}
		}
	}
	out << "END" << endl;
}

/****************************TreeNode***********************************/

AbstractTree::TreeNode::TreeNode(int const& nv, TreeNode* parent) :
	nodeValue(nv),
	parent(parent) {
}

int AbstractTree::TreeNode::value() const {
	return nodeValue;
}

int AbstractTree::TreeNode::degree() const {
	return children.size();
}

AbstractTree::TreeNode* AbstractTree::TreeNode::getParent() const {
	return parent;
}

AbstractTree::TreeNode* AbstractTree::TreeNode::child(int const& i) const {

	if (i < 0 || i >= degree()) return nullptr;
	DoubleLinkedList<TreeNode*>::DoubleNode* currTreeNode = children.begin();
	for (int k = 0; k < i; k++) {
		currTreeNode = currTreeNode->next();
	}
	return currTreeNode->value();
}

#endif