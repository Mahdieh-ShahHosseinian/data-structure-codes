
#ifndef TREE_H
#define TREE_H

#include "linked list.h"
#include <algorithm>

using namespace std;

class Tree {

private:

    string nodeName;
    int nodeVolume;
    Tree *parent;
    DoubleLinkedList<Tree *> children;

public:

    explicit Tree(string = string() , int const & = int(), Tree * = nullptr);

    int volume() const;

    string name();

    Tree *getParent() const;

    int degree() const;

    bool isRoot() const;

    bool isLeaf() const;

    Tree *childAt(int) const;

    int height() const;

    void addChild(Tree const &);

    int size() const;

    void attach(Tree *);

    void detach();

    void print(ofstream &, int);

    int totalVolume();
};

Tree::Tree(string name, const int &volume, Tree *p) :
        nodeName(std::move(name)),
        nodeVolume(volume),
        parent(p) {

}

int Tree::volume() const {
    return nodeVolume;
}

string Tree::name() {

    return nodeName;
}

Tree *Tree::getParent() const {
    return parent;
}

int Tree::degree() const {

    return children.size();
}

bool Tree::isRoot() const {

    return parent == nullptr;
}

bool Tree::isLeaf() const {

    return children.empty();
}

Tree *Tree::childAt(int n) const {

    if (n < 0 || n >= degree()) {
        return nullptr;
    }

    auto child = children.begin();

    for (int i = 1; i < n; ++i) {
        child = child->next();
    }
    return child->value();


}

int Tree::height() const {

    int treeHeight = 0;

    for (auto child = children.begin(); child != nullptr; child = child->next()) {
        treeHeight = max(treeHeight, child->value()->volume() + 1);
    }

    return treeHeight;
}

void Tree::addChild(Tree const &t) {

    children.pushBack((Tree *const &) t);
}

int Tree::size() const {

    int treeSize = 1;

    for (auto child = children.begin(); child != nullptr; child = child->next()) {
        treeSize += child->value()->volume();
    }

    return treeSize;
}

void Tree::attach(Tree *tree) {

    if (!tree->isRoot()) {
        tree->detach();
    }

    tree->parent = this;

    children.pushBack(tree);

}

void Tree::detach() {

    if (isRoot()) {
        return;
    }

    getParent()->children.erase(this);

    parent = nullptr;

}

void Tree::print(ofstream &ofs, int depth) {

    for (int i = 0; i < depth; ++i) {
        ofs << "    ";
    }

    ofs << nodeName << "/" << " " << totalVolume() << endl;

    for (auto *ptr = children.begin(); ptr != nullptr; ptr = ptr->next()) {

        ptr->value()->print(ofs, depth + 1);

    }

}

int Tree::totalVolume() {

    int totalV = volume();

    for (auto *ptr = children.begin(); ptr != nullptr; ptr = ptr->next()) {

       totalV += ptr->value()->totalVolume();

    }

    return totalV;
}


#endif
