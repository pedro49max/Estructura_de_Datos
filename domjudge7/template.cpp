// These comments are only important if you are using vcs-cricket
// (they activate cricket, give a server address, and identify your things)
// do not modify the URL (or it will send things somewhere where they will be ignored)
//
// cricket-url: http://gin.fdi.ucm.es:8080
// cricket-id: I42
//              /\
// PLEASE CHANGE THE ID TO YOUR domjudge USERNAME
//
// To install cricket, 
// 1. open the extensions pane on the left (the icon is a stack of boxes), 
// 2. click the "..." icon in the top-right of that pane
// 3. choose the last option ("Install from VSIX ...")
// 4. select "cricket-0.0.1.vsix"

#include <iostream>
#include "TreeMap.h"

using namespace std;

struct Bank {
    TreeMap<string, int> accounts;
    void transfer(int line, string source, string target, int quantity) {
        if (source != "*") {

            if (accounts.contains(source) && accounts[source] >= quantity) {
                 accounts[source] -= quantity;
                 accounts[target] += quantity;
            }
            else
                 cout << line << " " << source << " is " << quantity - accounts[source] << " short of " << quantity << endl;
            
        }
        else
            accounts[target] += quantity;
        // Attempts to transfer quantity from source to target
        // if source is *, put the money directly into target's account
        // otherwise, if source does not have enough funds, complain and do nothing else
        // otherwise, remove quantity from source, and add quantity to target

        // YOUR CODE HERE
    }
    void state() const {
        // Iterate map in alphabetical order and output money in non-empty, non-* accounts
        for (auto person = accounts.cbegin(); person != accounts.cend(); person++) {
            auto name = person.key();
            if (name != "*" && accounts.at(name) > 0)
                cout << name << " " << accounts.at(name) <<endl;
        }
        // YOUR CODE HERE
    }
};

int main() {
    int n;
    while (cin >> n && n) {
        Bank bank;
        for (int i=0; i<n; i++) {
            string source, target;
            int quantity;
            cin >> source >> target >> quantity;
            bank.transfer(i+1, source, target, quantity);
        }
        bank.state();
    }
    return 0;
}