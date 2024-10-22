To test under Windows:
=====

1 - Open a "git bash" terminal (the normal cmd terminal does *not* work right)
2 - Enter into the folder where you have your .cpp, .h, and sample input/output files
    (sample.in & sample.ans)
3 - Copy and paste into the git bash terminal:
    
g++ -Wall -g myAnswer.cpp -o s.exe && s.exe < sample.in
    
    The above line will generate output inside the terminal. 
    If you would rather generate output in a file, use this instead:
    
g++ -Wall -g myAnswer.cpp -o s.exe && s.exe < sample.in > output
    
    now, compare your output to sample.ans, to see if it is right.
    
    You can also modify (your copy of) sample.in and sample.ans to add
    test-cases that may not appear in the originals.

Beware the use of a "phantom node" in SList.h
=====

The _head is never changed; this makes some operations slightly easier to write 
(because "list may be empty w/ nullptr everywhere" is no longer possible). 

But:
- the 1st element is now no longer at head. Instead, it is at 
    head->next
- empty lists no longer have head == tail == nullptr; they have
    head->_next == nullptr 
- to place a node 'n' at the end, there is no 'if empty'; instead
    list._tail->next = n;           // place after old end
    list._tail = n;                 // make end point to it 
