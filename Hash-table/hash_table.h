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

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <string>
#include "linked_list.h"
using namespace std;

class HashTable {

public:
	void insert(string const&, string const&);
	string lookup(string const&);

	HashTable(int const&);
	~HashTable();

private:
	
	// the type of linked list is Pair, each Pair have its own word any meaning
	// it uses for saving the input data
	class Pair {
	private:
		string word;
		string meaning;
	public:
		Pair(string w, string m) {
			word = w;
			meaning = m;
		}
		string getWord() {
			return word;
		}
		string getMeaning() {
			return meaning;
		}
	};
	int capacity;
	DoubleLinkedList<Pair>* hashTable;
	int hashFunction(string const&);
};

// n is the maximum number of words
HashTable::HashTable(int const& n) :
	// Updated the initialization list here
	capacity(n * 2) // Just a sample --> Load Factor = (n/2n) = 0.5
{
	hashTable = new DoubleLinkedList<Pair>[capacity];
}

HashTable::~HashTable() {
	delete[] hashTable;
}

// make its Pair and push it back on linked list, which linked list? ask hash function!
void HashTable::insert(string const& word, string const& meaning) {

	int hash = hashFunction(word);
	Pair newItem(word, meaning);
	hashTable[hash].pushBack(newItem);
}

// return "NOT FOUND" if not found!
// give the word to ur hash function, to find which linked list you have to look up for that word
// and look it up on that linked list
// if that linked list is already empty, why you look for it?!
string HashTable::lookup(string const& word) {

	int hash = hashFunction(word);
	if (hashTable[hash].empty()) return "NOT FOUND";

	DoubleLinkedList<Pair>::DoubleNode* node = hashTable[hash].begin();
	while (node) {

		if (node->value().getWord() == word) {
			return node->value().getMeaning();
		}
		node = node->next();
	}
	return "NOT FOUND";
}

// just a sample, a simple sample
int HashTable::hashFunction(string const& word) {
	int res = 0;
	//for (int i = 0; i < word.length(); i++) res += word[i] * 3;
	for (char c : word) res += c * 3;
	return res % capacity;
}

#endif