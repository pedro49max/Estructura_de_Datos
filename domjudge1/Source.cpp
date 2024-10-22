/*#include <iostream>
#include <vector>

using namespace std;

// Structure to represent memory segment
struct MemorySegment {
    int start;
    int size;
};

// Function to check if a memory segment contains a given address
bool contains(const MemorySegment& segment, int address) {
    //cout << address << " < " << segment.start + segment.size - 1 << endl;
    return  address <= segment.start + segment.size -1;
}

int main() {
    int cases;
    cin >> cases;

    for (int caseNo = 0; caseNo < cases; ++caseNo) {
        vector<MemorySegment> segments;

        // Read memory segments
        bool zero = false;
        while (!zero) {
            int start, size;
            cin >> start;
            if (start == 0)
                zero = true;
            cin >> size; 
            if(!zero)
                segments.push_back({ start, size });
        }

        // Process requests
        bool input = true;
        while (input) {
            string request;
            cin >> request;
            if (request == "end")
                input = false;

            if (input && request == "free") {
                int pointer;
                cin >> pointer;

                bool found = false;
                for (int i = 0;  i < segments.size() && !found;i++){
                    MemorySegment segment = segments[i];
                    if (segment.start == pointer) {
                        found = true;
                    }
                }
                cout << (found ? "OK" : "CRASH") << endl;
            }
            else if (input && request == "use") {
                int start, size;
                
                cin >> start >> size;

                bool valid = true, fullValid = false;
                
                for (int i = 0;  i < segments.size() && !fullValid; i++) {
                    MemorySegment segment = segments[i];
                    if (contains(segment, start) && contains(segment, start + size - 1)) {
                        valid = true;
                        fullValid = true;
                    }
                    else {
                        valid = false;
                    }
                }
                cout << (valid ? "OK" : "EXPLODE") << endl;
            }
        }
    }

    return 0;
}
*/