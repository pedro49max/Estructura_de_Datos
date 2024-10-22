#include <iostream>

#include "Evaluator.h"
using namespace std;

int main() {
    string o;
    Evaluator evaluator;
    // int line = 1;
    while (cin >> o) {
        // cerr << "\t(line " << (line ++) << ", op is " << o << ")\n";
        if (o == "end") {
            // starts over with empty
            evaluator = Evaluator{};
        } else if (o == "add_s") {
            sid_t id;
            cin >> id;
            try {
                evaluator.add_s(id);
            } catch (EDuplicate e) {
                cout << "EDuplicate\n";
            }
        } else if (o == "add_e") {
            eid_t id;
            int m;
            cin >> id >> m;
            try {
                evaluator.add_e(id, m?true:false);
            } catch (EDuplicate e) {
                cout << "EDuplicate\n";
            }
        } else if (o == "grade") {
            sid_t st;
            grade_t g;
            eid_t ex;
            cin >> st >> g >> ex;
            try {
                evaluator.grade(st, g, ex);
            } catch (EBadArgs e) {
                cout << "EBadArgs\n";
            } 
        } else if (o == "top") {
            int n; 
            cin >> n;
            List<sid_t> tl = evaluator.top(n);
            for (auto it=tl.cbegin(); it!=tl.cend(); it++) {
                if (it != tl.cbegin()) cout << " ";
                cout << (*it);
            }
            cout << "\n";
        } else if (o == "average") {
            sid_t id;
            cin >> id;
            try {
                cout << evaluator.average(id) << "\n";
            } catch (EBadArgs e) {
                cout << "EBadArgs\n";
            }
        } else {
            cout << "NO SUCH OP: " << o << "\n";
        }
    }
    return 0;
}
