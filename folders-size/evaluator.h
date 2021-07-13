
#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "tree.h"

class Evaluator {

private:

    DoubleLinkedList<Tree *> trees;

public:

    void getNodes(string, int);

    void order(string, string);

    void print(ofstream &);

};

void Evaluator::getNodes(string name, int volume) {

    trees.pushBack(new Tree(name, volume));
}

void Evaluator::order(string name1, string name2) {


    Tree *t1;
    Tree *t2;

    for (auto *ptr = trees.begin(); ptr != nullptr; ptr = ptr->next()) {

        if (ptr->value()->name() == name1) {
           t1 = ptr->value();
       }

       if (ptr->value()->name() == name2) {
           t2 = ptr->value();
       }
    }


    t1->attach(t2);


}

void Evaluator::print(ofstream &fout) {


    for (auto *ptr = trees.begin(); ptr != nullptr; ptr = ptr->next()) {

        if (ptr->value()->isRoot()) {
           ptr->value()->print(fout, 0);
        }
    }


}

#endif
