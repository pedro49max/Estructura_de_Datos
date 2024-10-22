#include <iostream>
#include <string>
#include <cstring>
#include "Stack.h"

class UnexpectedClosingException {
    public:
    const char closingSymbol;
    UnexpectedClosingException(char closingSymbol) 
        : closingSymbol(closingSymbol) {}
};

class UnclosedSymbolsException {
    public:
    const int nUnclosed;
    UnclosedSymbolsException(int nUnclosed)
        : nUnclosed(nUnclosed) {}
};

/**
 * returns the index of a character in a string, or -1 if not found.
 * Note that strchr(s,c) returns a pointer, which must be converted to an index;
 * and NULL if it does not find the searched-for character.
 */
int indexOf(const char *s, char c) {
    // YOUR CODE HERE

    return -1; // <-- REMOVE    
}

/**
 * Checks nesting of symbols in input string
 * @param input string
 * @param opens a zero-terminated array of opening symbols. 
 *  You can check if a character is in this array using `indexOf(opens, character)`
 *  which will return -1 if not found or its index otherwise.
 * @param closes a zero-terminated array of corresponding closing symbols.
 *  In particular, closes[i] is guaranteed to close opens[i] for all valid indices.
 * @throws UnexpectedClosingException or UnclosedSymbolsException if errors encountered
 * @returns true if no errors (never returns false: would throw first)
 */
bool checkCorrectNesting(const std::string &input, const char *opens, const char *closes) {
    Stack<char> stack;

    for (char c : input) {
       if(c == '[' || c == '{' || c == '(' || c == '<' )
           stack.push(c);
       if (c == ']' || c == '}' || c == ')' || c == '>')
           if(stack.empty())
               throw UnexpectedClosingException(c);
           else if ((c == ']' && stack.top() != '[') || (c == '}' && stack.top() != '{') || (c == ')' && stack.top() != '(') || (c == '>' && stack.top() != '<')){
               throw UnexpectedClosingException(c);
           }
 
           else
               stack.pop();
    }

    if (!stack.empty()) {
        throw UnclosedSymbolsException(stack.size());
    }

    return true;
}

using namespace std;

int main() {
    
    // N = # of testcases as 1st line
    int n; 
    cin >> n;
    string discard;
    getline(cin, discard); // discards the "/n" at the end of 1st line
    for (int i=0; i<n; i++) {
        string input;
        getline(cin, input);
        try {
            if (checkCorrectNesting(input, "({[<", ")}]>")) {
                cout << "OK\n";
            }
        } catch (UnexpectedClosingException uce) {
            cout << "ERROR: UNEXPECTED " << uce.closingSymbol << "\n";
        } catch (UnclosedSymbolsException use) {
            cout << "ERROR: " << use.nUnclosed << " UNCLOSED SYMBOLS\n";
        }
    }
    return 0;
}
