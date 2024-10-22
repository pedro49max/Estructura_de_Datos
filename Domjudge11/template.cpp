#include <iostream>
#include "BinTree.h"
using namespace std;

class BadInputException{};

BinTree<int> readTree() {
    char c;
    cin >> c;
    switch (c) {
        case '#': return BinTree<int>();
        case '[': {
            int v;
            cin >> v;
            cin >> c;
            assert(c == ']');
            return BinTree<int>(v);
        }
        case '(': {
            const BinTree<int> &left = readTree();
            int v;
            cin >> v;
            const BinTree<int> &right = readTree();
            cin >> c;
            assert(c == ')');
            return BinTree<int>(left, v, right);
        }
        default: {
            cerr << "Invalid tree character: " << c << "\n";
            throw BadInputException();
        }
    }
}

// STATE COMPLEXITY HERE
int deepest_square(const BinTree<int>& t, int &deph, int &sum) {//([1]1[0])
    // YOUR CODE HERE
    int answer = -1, leftdeep = deph+ 1, rightdeep = deph + 1, leftSum = 0, rightSum = 0, left = -1, right = -1;
    if (!t.empty()) {
        if (!t.left().empty()) {
            left = deepest_square(t.left(), leftdeep, leftSum);
        }
        if (!t.right().empty()) {
            right = deepest_square(t.right(), rightdeep, rightSum);
        }
        if (t.left().empty() && t.right().empty() && t.elem() == 0) {
            answer = 0;
            sum = 0;
        }
        else if ((right && left == -1) && leftSum + rightSum == t.elem()) {
            answer = t.elem();
            sum = leftSum + rightSum + t.elem();
        }
        else if ((right && left == -1) && leftSum + rightSum != t.elem()) {
            sum = leftSum + rightSum + t.elem();
            deph--;
        }
        else {
            if (rightdeep > leftdeep) {
                answer = right;
                sum = leftSum + rightSum + t.elem();
                deph = rightdeep;
            }
            else {
                answer = left;
                sum = leftSum + rightSum + t.elem();
                deph = leftdeep;
            }
        }
    }
    else
        answer = -1;
    

    return answer;
}

int main() {
    int b; 
    cin >> b;
    for (int i=0; i<b; i++) {
        BinTree<int> t = readTree();
        int deep = -1, Sum = 0;
        cout << deepest_square(t, deep, Sum) << "\n";
    }
    return 0;
}