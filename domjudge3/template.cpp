#include <iostream>
#include <string>
#include <sstream>
#include "SList.h"

using namespace std;

/*
 * NOTE: you should not need to change this file. All your changes should go into SList.h
 */

/** reads a list of integers into a list */
SList<int> readList(string input) {
    istringstream iss(input);
    SList<int> output;
    for (int i; iss >> i; output.push_back(i)) /**/;
    return output;
}

int main() {
    
    // N = # lines in block
    int n; 
    while (cin >> n && n) {
        string discard;
        getline(cin, discard); // discards the "/n" at the end of 1st line

        SList<int> *block = new SList<int>[n];
        for (int i=0; i<n; i++) {
            string input;
            getline(cin, input);
            block[i] = readList(input);            
        }
        SList<int> result;
        result.merge(block, n); // <--- implement this (in SList.h)
        result.write(cout);
        cout << "\n";

        delete[] block;
    }
    return 0;
}
