#include <iostream>
#include "BinTree.h"

using namespace std;

BinTree<int> readTree() {
    char c;
    cin >> c;
    if (c == '.') return BinTree<int>();

    assert(c == '(');
    const BinTree<int> &left = readTree();
    int v;
    cin >> v;
    const BinTree<int> &right = readTree();
    cin >> c;
    assert(c == ')');
    return BinTree<int>(left, v, right);
}

void writeTree(const BinTree<int> &t) {
    // show "." if empty, or "(LeftValueRight)" otherwise
    // where Left=t.left(), Value=t.elem(), and Right=t.right()
    if (t.empty())
        cout << ".";
    else {
        cout << "(";
        writeTree(t.left());
        cout << t.elem();
        writeTree(t.right());
        cout << ")";
    }
    // [YOUR CODE HERE]
}

BinTree<int> sum(const BinTree<int> &a, const BinTree<int> &b) {
    // returns a tree that is the result of adding two input trees
    
    if (a.empty() && b.empty()) {
        // [YOUR CODE HERE] - both are empty, what should I return?
        return BinTree<int>();
    } else if (! a.empty() && b.empty()) {
        // [YOUR CODE HERE] - one is empty, and the other is not!
        return BinTree<int>(a.left(), a.elem(), a.right());
    } else if (a.empty() && ! b.empty()) {
        // [YOUR CODE HERE] - hey, they switched around!
        return BinTree<int>(b.left(), b.elem(), b.right());
    } else {
        BinTree<int> c = sum(a.left(), b.left());
        BinTree<int> d = sum(a.right(), b.right());
        int v = a.elem() + b.elem();
        return BinTree<int>(c, v, d);
        // [YOUR CODE HERE] - two non-empty trees. How do I add?
    }
}

int main() {
    bool ok = true;
    while (ok) {
        BinTree<int> a = readTree();
        BinTree<int> b = readTree();
        if (a.empty() && b.empty()) {
            ok = false;
        } else {
            writeTree(sum(a, b));
            cout << endl;
        }
    }
    return 0;
}