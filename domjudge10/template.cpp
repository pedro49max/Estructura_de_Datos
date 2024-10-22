#include <iostream>
#include <string>
#include <sstream>
#include "SList.h"

using namespace std;

/*
 * NOTE: you should not need to change this file. All your changes should go into SList.h
 */

/** reads a list of integers from a line in cin */
SList<int> readList() {
    string input;
    getline(cin, input);
    istringstream iss(input);
    SList<int> output;
    for (int i; iss >> i; output.push_back(i)) /**/;
    return output;
}

/** reads an int from a line in cin */
int readInt() {
    string input;
    if ( ! getline(cin, input)) {
        return -1;
    } else {
        return atoi(input.c_str());
    }
}

int main() {
    int n;
    while ((n = readInt()) && n > 0) {
        SList<int> listA = readList();
        SList<int> listB = readList();
        SList<int> result;
        if (n == 2) {
            result = SList<int>::zip(listA, listB);        // <--- implement this (in SList.h)
        } else if (n == 3) {
            SList<int> listC = readList();
            result = SList<int>::zip(listA, listB, listC); // <--- implement this (in SList.h)       
        } else {
            cerr << "ERROR EN ENTRADA - n = " << n << "???\n";
        }    
        result.display(cout);
        cout << "\n";
    }
    return 0;
}
