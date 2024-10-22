#include <iostream>
#include <string>
#include <sstream>
#include <ios>
#include "MList.h"

using namespace std;

typedef List<char> Line;

/** reads a string to a list */
Line readList(string input) {
    istringstream iss(input);
    Line output;
    iss >> noskipws; // avoids whitespace-skipping
    for (char c; iss >> c; output.push_back(c)) /**/;
    return output;
}

/** outputs a line */
void show(const Line &line) {
    for (auto it=line.cbegin(); it!=line.cend(); it++) cout << *it;
    cout << "\n";
}

/** creates a list from another list, interpreting some characters as instructions */
Line process(const Line &keystrokes) {
    bool overwrite = false;
    Line output;
    Line::Iterator cursor = output.end();

    for (Line::ConstIterator ki=keystrokes.cbegin(); ki!=keystrokes.cend(); ki++) {
        char key = *ki;
        switch (key) {

        case '<': {
            if (cursor == output.end()) {
                cursor = output.rbegin();
            }
            else if (cursor != output.begin()) {
                cursor--;
            }
            break;
        }
        case '>': {
            if (cursor != output.end()) {
                cursor++;
            }
            break;
        }
        case '{': {
            cursor = output.begin();
            break;
        }
        case '}': {
            cursor = output.end();
            break;
        }
        case '\\': { // erase prev char (backspace key)
            if (cursor == output.end()) {
                cursor = output.rbegin();
            }
            if (cursor != output.end()) {
                if (cursor != output.begin()) {
                    cursor--;
                }
                cursor = output.erase(cursor);
            }
            break;
        }
        case '/': { // erase next char (del key)
            if (cursor != output.end()) {
                cursor = output.erase(cursor);
            }
            break;
        }
        case '@': {
            overwrite = !overwrite;
            break;
        }
        default: {
            if (cursor == output.end()) {
                output.push_back(key);
            }
            else if (overwrite) {
                cursor.set(key);
                cursor++;
            }
            else {
                output.insert(key, cursor);
            }
        }
        }

        // uncomment these lines to help debug your program
        // cout << "after "<< key << ": ";
        // show(output);
    }
    return output;
}


int main() {
    string input;
    while (getline(cin, input)) {
        Line keystrokes;
        keystrokes = readList(input);
        // uncomment this line to help debug your program
         //show(keystrokes);
        show(process(keystrokes));
    }
    return 0;
}
