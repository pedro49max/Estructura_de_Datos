#include <iostream>
#include <sstream>
#include <algorithm>

#include "HashMap.h"
#include "List.h"

// naming units is a good way to not mix them up
typedef int t_units;
typedef int a_id;

class Planner {

    // This part of the private implementation provided for free
    struct Segment {
        t_units start;
        t_units end;
        bool inside(t_units t) const {
            return start <= t && t < end;
        }
        bool overlaps(const Segment &other) const {
            return inside(other.start) || inside(other.end+1) || 
                (other.start <= start && other.end > end);
        }
    };

    struct Appointment {
        a_id id;
        std::string text;
        Segment time;
    };

    a_id lastId=0;
   
    // REST OF PRIVATE IMPLEMENTATION HERE
    HashMap<a_id, Appointment> appointments;

public:

    Planner() : lastId(0) {}

    // O(1)
    a_id add(t_units start, t_units end, const std::string &text) {
        
        std::stringstream ss;
        ss << start << " " << end << text;
        Appointment a{lastId++, ss.str(), Segment{start, end}};

        // YOUR CODE HERE
        appointments[a.id] = a;
        return a.id;
    }

    // O(n), n = # appointments
    bool free(t_units start, t_units end) const {
        // YOUR CODE HERE
        Segment s = Segment{start, end};
        for (auto it=appointments.cbegin(); it!=appointments.cend(); it++) {
            if (it.value().time.overlaps(s)) return false;
        }
        return true;
    }

    // O(1)
    void rm(a_id id) {
        // YOUR CODE HERE
        appointments.erase(id);
    }

    // O(n), n = # appointments
    List<Appointment> check(t_units t) const {
        // YOUR CODE HERE - no need to sort (main() calls showSorted())
        List<Appointment> result;
        for (auto it=appointments.cbegin(); it!=appointments.cend(); it++) {
            if (it.value().time.inside(t)) {
                result.push_back(it.value());
            }
        }
        return result;
    }

    // O(1)
    std::string show(a_id id) const {
        // YOUR CODE HERE - given appointment a, just return a.text; or "ERROR" if absent
        if (appointments.contains(id)) {
            return appointments.at(id).text;
        } else {
            return "ERROR";
        }
    }

    // O(n), n = # appointments
    List<Appointment> all() const {
        // YOUR CODE HERE - no need to sort (main() calls showSorted())
        List<Appointment> result;
        for (auto it=appointments.cbegin(); it!=appointments.cend(); it++) {
            result.push_back(it.value());
        }
        return result;
    }    

    // O(n log n), n = # elements in list
    static void showSorted(const List<Appointment> &l) {
        if ( ! l.empty()) {
            // load v with elements from l
            Appointment v[l.size()];
            unsigned int i=0;
            for (auto li=l.cbegin(); li != l.cend(); li++) {
                v[i++] = *li;
            }
            std::sort(v+0, v+l.size(), [](const Appointment &a, const Appointment &b) { 
                return a.time.start < b.time.start; 
            });

            // display sorted
            for (i=0; i<l.size(); i++) {
                std::cout << ' ' << v[i].id;
            }
        }
        std::cout << std::endl;
    }
};

using namespace std;

int main() {
    int n;
    int line = 1;
    cin >> n;
    for (int i=0; i<n; i++) {
        cout << "block #" << (i+1) << '\n';
        Planner a;
        string op, text;
        t_units start, end, t;
        a_id id;
        while (cin >> op && op != "end") {
            line ++;
            if (op == "add") {
                cin >> start >> end;
                getline(cin, text);
                cout << line << ": " << a.add(start, end, text) << '\n';
            } else if (op == "free") { 
                cin >> start >> end;
                cout << line << ": " << (a.free(start, end) ? "true" : "false") << '\n';
            } else if (op == "rm") { 
                cin >> id;
                a.rm(id);
            } else if (op == "list") { 
                cin >> t; 
                cout << line << ":";
                Planner::showSorted(a.check(t));
            } else if (op == "show") { 
                cin >> id;
                cout << line << ": " << a.show(id) << '\n';
            } else if (op == "all") { 
                cout << line << ":";
                Planner::showSorted(a.all());
            } else {
                cerr << "ERROR: ??OP " << op << '\n';
            }
        }
        line ++;
    }
    return 0;
}