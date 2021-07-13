#ifndef MYSTACK_H
#define MYSTACK_H

#include "double_linked_list.h"

// clear!
template <typename T>
class Stack {

public:
	bool empty();
	int size();
	void push(T);
	T top();
	void pop();

private:
	DoubleLinkedList<T> list;
};

// check if it's empty :/
template <typename T>
bool Stack<T>::empty() {
	return list.empty();
}

// how many dishes do you have
template <typename T>
int Stack<T>::size() {
	return list.size();
}

template <typename T>
void Stack<T>::push(T item) {
	list.pushFront(item);
}

// get the top
template <typename T>
T Stack<T>::top() {
	return list.front();
}

// pop the top
template <typename T>
void Stack<T>::pop() {
	list.popFront();
}

#endif 
