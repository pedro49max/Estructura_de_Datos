/**
 * Implementation of a Queue ADT using a singly-linked list
 * (c) Marco Antonio Gómez Martín, 2012
 * Modified by Ignacio Fábregas, 2022
 * English & more by Manuel Freire, 2023
 */
#ifndef __LL_QUEUE_H
#define __LL_QUEUE_H

#include "Exceptions.h"
#include <iostream>

/**
 * Singly linked list, usable as a queue
 * Operations are:
 *   - EmptyList: -> SList. SList (empty constructor)
 *   - push_back: SList, Elem -> Stack. Generator
 *   - pop_front: SList -> SList. Partial modifier
 *   - front: SList -> Elem. Partial observer
 *   - empty: SList -> Bool. Observer
 *   - size: SList -> Int. Observer
 */
template <class T>
class SList {
public:
    /** Constructor; EmptyList operation. O(1) */
    SList() : _first(nullptr), _last(nullptr) {
    }

    /** Destructor; frees the list. O(n) */
    ~SList() {
        free();
        _first = _last = nullptr;
    }

    /** Pushes an element at back. Generator. O(1) */
    void push_back(const T &_elem) {
        Node *newNode = new Node(_elem, nullptr);
        if (_last != nullptr) {
            _last->_next = newNode;
        }
        _last = newNode;
        // If queue was empty, newNode is also _first
        if (_first == nullptr) {
            _first = newNode;
        }
    }

    /**
     * Pops an element (whichever was pushed first). 
     * Partial modifier (fails if empty). O(1)
     */
    void pop_front() {
        if (empty()) {
            throw EmptyListException("Cannot pop: SList is empty");
        }
        Node *toRemove = _first;
        _first = _first->_next;
        delete toRemove;
        if (_first == nullptr) //si la cola queda vacía, no hay último
            _last = nullptr;
    }

    /**
     * Returns top-most element (whichever would be popped by pop_front()).
     * Partial observer (fails if empty). O(1)
     */
    const T &front() const {
        if (empty()) {
            throw EmptyListException("Cannot get front: SList is empty");
        }
        return _first->_elem;
    }

    /** True IFF queue is empty. Observer. O(1) */
    bool empty() const {
        return _first == nullptr;
    }

    // //
    // C++ Boilerplate code to make class more useful
    // //

    /** Copy ctor. O(n) */
    SList(const SList<T> &other) : _first(nullptr), _last(nullptr) {
        copy(other);
    }

    /** Assignment constructor. O(n) */
    SList<T> &operator=(const SList<T> &other) {
        if (this != &other) {
            free();
            copy(other);
        }
        return *this;
    }

    /** Equality operator. O(n) */
    bool operator==(const SList<T> &rhs) const {
        bool same = true;
        Node *p1 = _first;
        Node *p2 = rhs._first;
        while ((p1 != nullptr) && (p2 != nullptr) && same) {
            if (p1->_elem != p2->_elem)
                same = false;
            else {
                p1 = p1->_next;
                p2 = p2->_next;
            }
        }
        return same;
    }

    /** Inequality operator. O(n) */
    bool operator!=(const SList<T> &rhs) const {
        return !(*this == rhs);
    }

    /** Outputs to stream using operator <<, from first to last. */
    void write(std::ostream& sOut) {
        Node* aux = _first;
        while (aux != nullptr){
            sOut << aux->_elem;
            aux = aux->_next;
            if (aux != nullptr) sOut << " ";
        }
    }

protected:

    void free() {
        free(_first);
    }

    void copy(const SList &other) {
        if (other.empty()) {
            _first = _last = nullptr;
        } else {
            Node *_current = other._first;
            Node *_prev;
            _first = new Node(_current->_elem);
            _prev = _first;
            while (_current->_next != nullptr) {
                _current = _current->_next;
                _prev->_next = new Node(_current->_elem);
                _prev = _prev->_next;
            }
            _last = _prev;
        }
    }

private:

    /**
     * Node class. Stores the element (of type T), and pointers to next node
     * Pointer to next may be nullptr for last node in list
     */
    class Node {
    public:
        Node() : _next(nullptr) {}
        Node(const T &_elem) : _elem(_elem), _next(nullptr) {}
        Node(const T &_elem, Node *_next) : _elem(_elem), _next(_next) {}

        T _elem;
        Node *_next;
    };

    /**
     * Removes all nodes from list. 
     * Passing nullptr is ok - nothing to free then. 
     * If argument is non-nullptr, must be 1st element in list.
     */
    static void free(Node *n) {
        while (n != nullptr) {
            Node *aux = n;
            n = n->_next;
            delete aux;
        }
    }

    /** Pointer to 1st element */
    Node *_first;

    /** Pointer to last element */
    Node *_last;

public:

    void merge(SList *sources, int n) {
        SList* minList = nullptr;
        do {
            minList = nullptr;
            for (int i = 0; i < n; i++) {
                SList *current = &sources[i];
                if (!current->empty() && minList == nullptr)
                    minList = current;
                else if (!current->empty() && current->_first) {
                    if (current->_first->_elem < minList->_first->_elem) {
                        minList = current;
                    }
                }
            }
            if (minList) {
                if (_last != nullptr) {
                    _last->_next = minList->_first;
                   // _last = minList->_first;
                    minList->_first = minList->_first->_next;
                }
                else {
                    _last = _first = minList->_first;
                    minList->_first = minList->_first->_next;
                }
                    
                //minList is the list with the smallest initial element
                //take the 1st element from minList
                //place at the end of this
            }
        } while (minList);
        // YOUR CODE HERE
        // while the source lists are not all empty,        
        // take the smallest initial element from the sources, and move it to the end of this list
    }
};

/** Output operator, for use with streams */
template<class T>
std::ostream& operator<<(std::ostream& sOut, SList<T>& q) {
    q.write(sOut);
    return sOut;
}

#endif // __LL_QUEUE_H
