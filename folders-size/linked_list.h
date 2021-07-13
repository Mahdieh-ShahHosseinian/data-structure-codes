#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <iostream>
#include "exception.h"

template <typename Type>
class DoubleLinkedList {
public:
    class DoubleNode {
    public:
        DoubleNode(Type const& = Type(), DoubleNode* = nullptr, DoubleNode* = nullptr);

        Type value() const;
        DoubleNode* previous() const;
        DoubleNode* next() const;

        Type         nodeValue;
        DoubleNode* previousNode;
        DoubleNode* nextNode;
    };

    DoubleLinkedList();
    DoubleLinkedList(DoubleLinkedList const&);
    ~DoubleLinkedList();

    // Accessors

    int size() const;
    bool empty() const;

    Type front() const;
    Type back() const;

    DoubleNode* begin() const;
    DoubleNode* end() const;

    DoubleNode* find(Type const&) const;
    int count(Type const&) const;

    // Mutators

    void swap(DoubleLinkedList&);

    void pushFront(Type const&);
    void pushBack(Type const&);

    void popFront();
    void popBack();

    int erase(Type const&);

private:
    DoubleNode* listHead;
    DoubleNode* listTail;
    int listSize;

    // List any additional private member functions you author here
    // Friends

    friend std::ostream& operator<<(std::ostream&, DoubleLinkedList const&);
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
DoubleLinkedList<Type>::DoubleLinkedList() :
    // Updated the initialization list here
    listHead(nullptr),
    listTail(nullptr),
    listSize(0) {}

// this methods push all list nodes to the class list through the pushBack() function, O(n)
template <typename Type>
DoubleLinkedList<Type>::DoubleLinkedList(DoubleLinkedList const& list) :
    // Updated the initialization list here
    listHead(nullptr),
    listTail(nullptr),
    listSize(0) {
    DoubleNode* currNode = list.begin();
    while (currNode != nullptr) {
        pushBack(currNode->value());
        currNode = currNode->next();
    }
}

// the destructure methods delete all list nodes with using popBack() methode, O(n)
// you can also use popFront(), no diff
template <typename Type>
DoubleLinkedList<Type>::~DoubleLinkedList() {
    while (!empty()) popBack();
}

// O(1), this is obvious what it do
template <typename Type>
int DoubleLinkedList<Type>::size() const {
    return listSize;
}

// O(1), obvious
template <typename Type>
bool DoubleLinkedList<Type>::empty() const {
    return listSize == 0;
}

// O(1), obvious
template <typename Type>
Type DoubleLinkedList<Type>::front() const {
    if (!empty()) return listHead->value();
    throw Underflow();
}

// O(1), obvious
template <typename Type>
Type DoubleLinkedList<Type>::back() const {
    if (!empty()) return listTail->value();
    throw Underflow();
}

// O(1), obvious
template <typename Type>
typename DoubleLinkedList<Type>::DoubleNode* DoubleLinkedList<Type>::begin() const {
    return listHead;
}

// O(1), obvious
template <typename Type>
typename DoubleLinkedList<Type>::DoubleNode* DoubleLinkedList<Type>::end() const {
    return listTail;
}
// first matche value node will find right here, O(n)
template <typename Type>
typename DoubleLinkedList<Type>::DoubleNode* DoubleLinkedList<Type>::find(Type const& value) const {

    DoubleNode* currNode = listHead;
    while (currNode != nullptr) {

        if (currNode->value() == value) return currNode;
        currNode = currNode->next();
    }
    return nullptr;
}

// all matches value nodes will find right here, O(n)
template <typename Type>
int DoubleLinkedList<Type>::count(Type const& value) const {

    int ctr = 0;

    DoubleNode* currNode = listHead;
    while (currNode != nullptr) {

        if (currNode->value() == value) ctr++;
        currNode = currNode->next();
    }
    return ctr;
}

// swap two info lists! head, tail, size and enough ---- O(n)
// swap() can be replace here))
template <typename Type>
void DoubleLinkedList<Type> ::swap(DoubleLinkedList& list) {

    DoubleNode* temp = listHead;
    listHead = list.begin();
    list.listHead = temp;

    temp = listTail;
    listTail = list.end();
    list.listTail = temp;

    int copySize = listSize;
    listSize = list.listSize;
    list.listSize = copySize;
}

// just notice that when the first node add, listTail will be the same as listTail in address, O(1)
//no need to explain more! it's completely obvious
template <typename Type>
void DoubleLinkedList<Type>::pushFront(Type const& value) {

    DoubleNode* newNode = new DoubleNode(value, nullptr, listHead);
    if (!empty()) {
        listHead->previousNode = newNode;
    }
    listHead = newNode;
    if (listTail == nullptr) listTail = listHead;
    listSize++;
}

// just notice that when the first node add, listTail will be the same as listTail in address, O(1)
//no need to explain more! it's completely obvious
template <typename Type>
void DoubleLinkedList<Type>::pushBack(Type const& value) {

    DoubleNode* newNode = new DoubleNode(value, listTail, nullptr);
    if (!empty()) {
        listTail->nextNode = newNode;
    }
    listTail = newNode;
    if (listHead == nullptr) {
        listHead = listTail;
    }
    listSize++;
}

// just have to consider this: if you pop the last node, then listTail should set as null! O(1)
// for deleting the head item you have to put it in the tempValue (copyHead), can't delete it without that
// hope you understand why :D
template <typename Type>
void DoubleLinkedList<Type>::popFront() {

    if (empty()) throw Underflow();

    DoubleNode* copyHead = listHead;
    listHead = listHead->next();
    listSize--;
    if (!empty()) {
        listHead->previousNode = nullptr;
    }
    else {
        listTail = nullptr;
    }
    delete copyHead;
}

// the same work, like popFront()!
template <typename Type>
void DoubleLinkedList<Type>::popBack() {

    if (empty()) throw Underflow();

    DoubleNode* copyTail = listTail;
    listTail = listTail->previous();
    listSize--;
    if (!empty()) {
        listTail->nextNode = nullptr;
    }
    else {
        listHead = nullptr;
    }
    delete copyTail;
}

// you need to know what node you want to delete! depends on that u have to set those if,elseif --- O(1)
// if you tryna to 1)delete listHead, you have to update listHead! ---- same for listTail
template <typename Type>
int DoubleLinkedList<Type>::erase(Type const& value) {

    int ctr = 0;
    DoubleNode* currNode = listHead;
    while (currNode != nullptr) {

        DoubleNode* temp = nullptr;
        if (currNode->value() == value) {

            if (currNode == listHead) {
                if (listHead->nextNode != nullptr) listHead->nextNode->previousNode = nullptr;
                temp = listHead;
                listHead = listHead->next();
            }
            else if (currNode == listTail) {
                if (listTail->previousNode != nullptr) listTail->previousNode->nextNode = nullptr;
                temp = listTail;
                listTail = listTail->previous();
            }
            else {
                if (currNode->previousNode != nullptr) currNode->previousNode->nextNode = currNode->nextNode;
                if (currNode->nextNode != nullptr) currNode->nextNode->previousNode = currNode->previousNode;
                temp = currNode;
            }
            listSize--;
            ctr++;
        }
        currNode = currNode->next();
        delete temp;
    }
    return ctr;
}


template <typename Type>
DoubleLinkedList<Type>::DoubleNode::DoubleNode(
    Type const& nv,
    DoubleLinkedList::DoubleNode* pn,
    DoubleLinkedList::DoubleNode* nn) :
    // Updated the initialization list here
    nodeValue(nv), // This assigns 'nodeValue' the default value
    previousNode(pn),
    nextNode(nn)
{}

template <typename Type>
Type DoubleLinkedList<Type>::DoubleNode::value() const {
    return nodeValue;
}

template <typename Type>
typename DoubleLinkedList<Type>::DoubleNode* DoubleLinkedList<Type>::DoubleNode::previous() const {
    return previousNode;
}

template <typename Type>
typename DoubleLinkedList<Type>::DoubleNode* DoubleLinkedList<Type>::DoubleNode::next() const {
    return nextNode;
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// If you author any additional private member functions, include them here

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

//template <typename Type>
//std::ostream& operator<<(std::ostream& out, DoubleLinkedList<Type> const& list) {
//    out << "head";
//
//    // print list from start to end
//    for (auto* ptr = list.begin(); ptr != nullptr; ptr = ptr->next()) {
//        out << "->" << ptr->value();
//    }
//    out << "->0" << std::endl << "tail";
//
//    // print list from end to start
//    for (DoubleLinkedList<Type>::DoubleNode* ptr = list.end(); ptr != nullptr; ptr = ptr->previous()) {
//        out << "->" << ptr->value();
//    }
//    out << "->0";
//
//    return out;
//}

#endif