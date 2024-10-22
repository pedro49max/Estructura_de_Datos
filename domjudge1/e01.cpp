/////
// Name of 1st author: Pedro Tobalina
// Name of 2nd author:
// (leave blank if only 1 author)
/////

#include <iostream>
#include <vector>

using namespace std;


struct MemorySegment {
    int start;
    int size;
};

bool contains(const MemorySegment& segment, int address) {
    //cout << address << " < " << segment.start + segment.size - 1 << endl;
    return  address <= segment.start + segment.size - 1;
}

class MemMap {
    MemorySegment segments[100];
    int size;
    // TODO: write a private part
public:
    MemMap(int nSegments, const int* starts, const int *sizes) {
        for (int i = 0; i < nSegments; i++) {
            segments[i] = { starts[i], sizes[i]};
        }
        size = nSegments;
        // TODO: initialize private part from parameters here
    }

    bool canFree(int start) const {
        bool found = false;
        for (int i = 0; i < size && !found; i++) {
            MemorySegment segment = segments[i];
            if (segment.start == start) {
                found = true;
            }
        }
        return found;
    }

    bool canUse(int start, int size) const {
        bool valid = true, fullValid = false;

        for (int i = 0; i <= size && !fullValid; i++) {
            MemorySegment segment = segments[i];
            if (contains(segment, start) && contains(segment, start + size - 1)) {
                valid = true;
                fullValid = true;
            }
            else {
                valid = false;
            }
        }
        return fullValid;
    }

};


const unsigned int MAX = 100;

int main() {

    // reserve static memory only once
    int starts[MAX];
    int sizes[MAX];
    
    // loop for each test case
    int nCases;
    cin >> nCases;
    while (nCases --) {

        // read 1st section
        int nSegments = 0;
        bool finished = false;
        while (!finished) {
            int start, size;
            cin >> start >> size;
            if (!start || !size) {
                finished = true;
            } else {
                starts[nSegments] = start;
                sizes[nSegments] = size;
                nSegments ++;
            }
        }

        // call constructor
        MemMap mm(nSegments, starts, sizes);

        // 2nd section: read & process process each request
        finished = false;
        while (!finished) {
            string request;
            int start, size;
            cin >> request;
            if (request == "end") {
                finished = true;
            } else if (request == "free") {
                cin >> start;
                cout << (mm.canFree(start) ? "OK" : "CRASH") << endl;
            } else if (request == "use") {
                cin >> start >> size;
                cout << (mm.canUse(start, size) ? "OK" : "EXPLODE") << endl;
            }
        }
    }

    return 0;
}
