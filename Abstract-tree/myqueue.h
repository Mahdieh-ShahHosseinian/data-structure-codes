#ifndef QUEUE_H
#define QUEUE_H
#include "double_linked_list.h"

template < typename Type>
class Queue {

private:

    DoubleLinkedList<Type> linkedList;
public:

    bool empty() const;
    void push(Type const&);
    Type pop();
};

template < typename Type>

bool Queue<Type>::empty() const {
    return linkedList.empty();
};

template < typename Type>

void Queue<Type>::push(Type const& value) {
    linkedList.pushBack(value);
};

template < typename Type>

Type Queue<Type>::pop() {

    Type front = linkedList.front();
    linkedList.popFront();
    return front;
};
#endif