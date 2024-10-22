#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include "TreeMap.h"
#include "TreeSet.h"
using namespace std;

//
// operations on map & set
//      both: .erase(k), .contains(k), .empty(), .begin(), .end(), .cbegin(), .cend()
//      map:  [k] (get&set), .at(k), .insert(k, v)
//      set:  .insert(k)
// iterators have
//      map:  .key(), .value()
//      set:  .elem() 
// note: no exception (and no effect) if removing absent element
//

/**
 * Reads a player's line from the input, composed of name and numWords words, 
 * and inserts it into the block under the player's name
 */
void readPlayer(TreeMap<string, TreeSet<string>> &block, int numWords) {
    // YOUR CODE HERE!
    string name, word;
    cin >> name;
    TreeSet<string> tree =  TreeSet<string>();
    for (int i = 0; i < numWords; i++) {
        cin >> word;
        tree.insert(word);
    }
    block.insert(name,tree);
}

/**
 * Checks a word from 'in' against all players in the block. 
 * Return true if any player has won, false otherwise.
 * (note that several players may win at once!)
 */
bool checkWord(TreeMap<string, TreeSet<string>> &block, const string &word) {
    bool win = false; //just for the return, to indicate if someone has won, many people can win at the same time
    for (auto person = block.begin(); person !=  block.end(); person++) {
        auto name = person.key();
        if (block[name].contains(word)) {
            block[name].erase(word);
            if (block[name].empty())
                win = true;
        }
    }
    // YOUR CODE HERE!
    return win;
}

/**
 * Outputs the winner(s) of a block, or 'BORING' if none
 */
void printWinner(const TreeMap<string, TreeSet<string>> &block) {
    // YOUR CODE HERE!
    bool first = true;// just for the space betwwen
    bool found = false; // to print boring or not
    for (auto person = block.cbegin(); person != block.cend(); person++) {
        auto name = person.key();
        if (block.at(name).empty()) {
            found = true;
            if(first)
                cout << name;
            else
                cout << " " << name;
            first = false;
        }

    }
    if (!found)
        cout << "BORING\n";
    else
        cout << endl;
}

int main() {
    int n, k;
    while (cin >> n >> k && n) {
        TreeMap<string, TreeSet<string>> block;
        for (int i=0; i<n; i++) {
            readPlayer(block, k);
        }
        string ignore, line;
        getline(cin, ignore); // eats extra \n from last line
        getline(cin, line); 
        line = regex_replace(line, regex("[.,!?:;-]"), ""); // rm punctuation  
        istringstream words(line);
        string word;
        while (words >> word) {
            if (checkWord(block, word)) break; // somebody won!
        }
        printWinner(block);
    }
    return 0;
}
