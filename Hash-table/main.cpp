#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <cmath>
#include"hash_table.h"
using namespace std;

#define EPS 0.00001
#define MAX_TIME 1.0

inline string trim(string& str)
{
	str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
	str.erase(str.find_last_not_of(' ') + 1);         //surfixing spaces
	return str;
}

int main() {

	HashTable hashTable(21000);

	// add [word, meaning] pairs to the hash table ==================
	ifstream fin;
	fin.open("input.txt");

	time_t start, end; // is used to measure elapsed time
	double overallInsertTime = 0, overallFetchTime = 0;

	time(&start); // start time

	int nWords;
	string word, meaning;

	fin >> nWords; // read number of words
	getline(fin, meaning); // ignore rest of the line

	for (int i = 0; i < nWords; i++)
	{
		fin >> word;

		getline(fin, meaning);
		meaning = trim(meaning);

		hashTable.insert(word, meaning); // insert into hash table
	}
	time(&end); // end time
	overallInsertTime = difftime(end, start);

	// ask the hash table for words meaning and write it in the output.txt =====

	ofstream fout;
	fout.open("output.txt");

	fin >> nWords; // read number of words

	time(&start); // start time
	for (int i = 0; i < nWords; i++)
	{
		fin >> word;
		fout << hashTable.lookup(word) << endl;
	}
	time(&end); // end time
	overallFetchTime = difftime(end, start);

	fout << boolalpha << "Time is valid: " << (overallFetchTime <= MAX_TIME) << endl;

	fin.close();
	fout.close();

	return 0;
}
