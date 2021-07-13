
#ifndef FILE_READER_H
#define FILE_READER_H

#include <fstream>
#include "evaluator.h"

using namespace std;

class FileReader {

private:

    int number{};

    Evaluator evaluator;

public:

    void lineProcessor(const string &);

    void getInput();

};

void FileReader::lineProcessor(const string &line) {


    string name;
    int v = 0;

    for (char c : line) {
        if (c == ' ') continue;

        if (isdigit(c)) {
            v = (int) c - 48 + v * 10;
        } else
            name += c;
    }

    evaluator.getNodes(name, v);


}

void FileReader::getInput() {

    ifstream fin("input.txt");

    ofstream fout("output.txt");

    string line;

    getline(fin, line);
    number = stoi(line);



    for (int i = 0; i < number; ++i) {

        getline(fin, line);

        lineProcessor(line);
    }

    while (fin.peek() != EOF){

        getline(fin, line);

        string name1, name2;

        bool nextName = false;

        for (char c : line) {

            if (c == ' ') {
                nextName = true;
            } else if (!nextName) {
                name1 += c;
            } else {
                name2 += c;
            }

        }


        evaluator.order(name1, name2);

    }


    evaluator.print(fout);

    fin.close();
    fout.close();
}

#endif
