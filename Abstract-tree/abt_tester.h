#ifndef ABT_TESTER_H
#define ABT_TESTER_H

#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include "exception.h"
#include "abstract_tree.h"

using namespace std;

class AbtTester {
public:
	AbtTester();
	~AbtTester();

	void readInput();

private:
	stack<AbstractTree> forest;

	bool readNextLine(ifstream& fin, ofstream& fout);

	void addTree(int);
	void copyTree();
	void removeTree();
	void push(int);
	void push(int*, int);
	string pop();
	int size();
	int height();
	void printBFS(ofstream& fout);
	void printDFS(ofstream& fout);
	bool isEmpty();
	string find(int val);
	int count(int val);
};

#endif

AbtTester::AbtTester() : forest() {

}

AbtTester::~AbtTester() {
	forest = stack<AbstractTree>();
}

void AbtTester::readInput() {
	ifstream fin;
	fin.open("input.txt");

	ofstream fout;
	fout.open("output.txt");

	while (readNextLine(fin, fout));

	fin.close();
	fout.close();
}

bool AbtTester::readNextLine(ifstream& fin, ofstream& fout) {
	string inputLine;
	if (getline(fin, inputLine)) {
		stringstream ss(inputLine);

		string command = "";
		if (ss.good()) {
			ss >> command;

			if (command == "") return true;
			else if (command == "new") {
				int param = 0;
				if (ss.good()) ss >> param;

				addTree(param);
			}
			else if (command == "exit") return false;
			else if (command == "copy") copyTree();
			else if (command == "end") {
				removeTree();
				if (forest.empty()) return false;
			}
			else if (command == "size") fout << size() << endl;
			else if (command == "height") fout << height() << endl;
			else if (command == "printDFS") printDFS(fout);
			else if (command == "printBFS") printBFS(fout);
			else if (command == "empty") fout << std::boolalpha << isEmpty() << endl;
			else if (command == "pop") fout << pop() << endl;
			else {
				int param;
				if (ss.good()) ss >> param;
				else throw IllegalArgument();

				if (command == "push") push(param);
				else if (command == "find") fout << find(param) << endl;
				else if (command == "count") fout << count(param) << endl;
				else if (command == "pushB") {
					if (param <= 0) throw IllegalArgument();
					int* params = new int[param];
					for (int i = 0; i < param; i++) ss >> params[i];
					push(params, param);
				}
			}
			return true;
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
}

void AbtTester::addTree(int degree) {
	AbstractTree newTree = AbstractTree(degree);
	forest.push(newTree);
}

void AbtTester::copyTree() {
	AbstractTree newTree(forest.top());
	forest.push(newTree);
}

void AbtTester::removeTree() {
	forest.pop();
}

void AbtTester::push(int val) {
	forest.top().push(val);
}

void AbtTester::push(int* vals, int len) {
	forest.top().push(vals, len);
}

string AbtTester::pop() {
	try {
		int val = forest.top().pop();
		return to_string(val);
	}
	catch (Underflow ex) {
		return "empty";
	}
	catch (Exception ex) {
		return "error";
	}
	return "none";
}

int AbtTester::size() {
	return forest.top().size();
}

int AbtTester::height() {
	return forest.top().height();
}

void AbtTester::printBFS(ofstream& fout) {
	forest.top().printBFS(fout);
}

void AbtTester::printDFS(ofstream& fout) {
	forest.top().printDFS(fout);
}

bool AbtTester::isEmpty() {
	return forest.top().empty();
}


string AbtTester::find(int val) {
	if (forest.top().find(val)) return "found";
	return "not-found";
}

int AbtTester::count(int val) {
	return forest.top().count(val);
}