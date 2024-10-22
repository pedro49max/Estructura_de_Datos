#include <iostream>
#include <sstream>
#include <algorithm>
#include <list>

#include "TreeMap.h"
//#include "HashMap.h"
#include "List.h"

typedef int money;
typedef std::string a_id;
typedef std::string w_id;

/*
NOTE: if you choose to store iterators to last-pushed-back elements, declare them as 
        std::list<w_id>::iterator it
    with value 
        --(myList.rbegin().base())    
    ... where calling base() converts the reverse_iterator from rbegin() into a normal one, and
    the -- notation simply means "previous" (++ is for next, -- for previous), to compensate for the fact
    that reverse iterators are offset by 1 position compared to normal ones.
    See https://stackoverflow.com/a/1830240/15472 for a longer discussion

NOTE2: there are at least 2 other ways to do this while retaining high efficiency:
    1 - you can add a last() operation to List.h, which would return an iterator to the last element of the list (_last)
    2 - you defer erasing stuff from your list until you have to extract the 1st k elements -- and then simply
        drop elements that are known to have been erased. This has, arguably, the same asymptotic cost as erasing early - 
        although you pay it at a different time (when selling vs when looking for old elements)
*/

class Gallery {

    // YOUR CODE HERE

public:
    struct ArtMoney {
        a_id arist;
        money cost;
        //int age = 0;
    };
    TreeMap<w_id, ArtMoney> gallery;
    TreeMap<a_id, int> sells;
    List<w_id> old;
   // TreeMap< w_id, int> timer;
    Gallery() {}
    
    void add(w_id work, a_id artist, money price) {
        if (gallery.contains(work)) {
            throw std::invalid_argument("duplicate work");
        }
        else {
            ArtMoney second;
            second.arist = artist; second.cost = price;
            gallery[work] = second;
            old.push_back(work);
            //timer[work] = 0;
        }
        /*for (auto object = gallery.begin(); object != gallery.end(); object++) {
            auto name = object.key();
            gallery[name].age += 1;
        }*/
        // YOUR CODE HERE
        // main expects you to        
        //    throw std::invalid_argument("duplicate work");
        // if work is duplicate
    }
    
    void sell(w_id work) {
        int sales = 0;
        if (gallery.contains(work)) {
            ArtMoney second;
            second = gallery.at(work);
            sales = second.cost;
            sells[second.arist] += sales;
            gallery.erase(work);
            //timer.erase(work);
            //add 1 to timers
            for (auto object = old.begin(); object != old.end(); object++) {
                if (object._elem() == work){
                    object = old.erase(object);
                    break;
                }
                    
            }
            /*for (auto object = gallery.begin(); object != gallery.end(); object++) {
                auto name = object.key();
                gallery[name].age += 1;
            }*/               
        }
        else {
            throw std::invalid_argument("no such work");
        }
        // YOUR CODE HERE
        // main expects you to        
        //    throw std::invalid_argument("no such work");
        // if work not found
    }

    std::list<a_id> best() {
        std::list<w_id> best;
        int bestMoney = -1;
        if (!sells.empty()) {
            for (auto person = sells.cbegin(); person != sells.cend(); person++) {
                auto name = person.key();
                if (sells.at(name) > bestMoney) {
                    bestMoney = sells.at(name);
                    for (int o = 0; o < best.size(); o++)
                        best.pop_back();
                    best.push_back(name);
                }
                else if(sells.at(name) == bestMoney)
                    best.push_back(name);
            }
        }
        // YOUR CODE HERE
        return best;
    }
    // O(k)
    std::list<w_id> oldest(int k) {
        std::list<w_id> old2;
        int older = -1;
        int younger = 6546465;
        if (!gallery.empty()) {
            for (int i = 0; i < old.size() && i < k;i++) {
                w_id art =old.at(i);
                if (gallery.contains(art))
                    old2.push_back(art);
            }
        }
        // YOUR CODE HERE
        return old2;
    }
};

using namespace std;

int main() {
    int line = 1;
    Gallery g;
    string op;
    money price;
    a_id artist;
    w_id work;
    int k;
    while (cin >> op) {
        line ++;
        if (op == "end") {
            cout << "---" << endl;
            g = Gallery(); // new gallery
        } else if (op == "add") {
            cin >> work >> artist >> price;
            cerr << " - adding " << work << endl;
            try  {
                g.add(work, artist, price);
            } catch (std::invalid_argument const& ex) {
                cout << "ERROR: " << ex.what() << endl;
            }
        } else if (op == "sell") { 
            cin >> work;
            cerr << " - selling " << work << endl;
            try  {
                g.sell(work);
            } catch (std::invalid_argument const& ex) {
                cout << "ERROR: " << ex.what() << endl;
            }
        } else if (op == "best") { 
            cout << "best:" << endl;
            list<a_id> bs = g.best();
            for (auto it=bs.begin(); it!=bs.end(); it++) {
                cout << " " << *it << endl;
            }
        } else if (op == "oldest") { 
            cin >> k;
            cerr << " - listing oldest " << k << endl;

            cout << "oldest:" << endl;
            list<w_id> bs = g.oldest(k);
            for (auto it=bs.begin(); it!=bs.end(); it++) {
                cout << " " << *it << endl;
            }
        } else {
            cerr << "ERROR: ??OP " << op << " at line " << line << endl;
        }
    }
    return 0;
}