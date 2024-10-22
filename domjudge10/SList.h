/**
 * List ADT implemented with a singly-linked list
 * with phantom 'head' node
 *
 * Original by Manuel Montenegro
 * Modified by Ignacio Fábregas
 * English & more by Manuel Freire
 *
 * Generic version, with a phantom node, head & tail
 */
  
#ifndef __LINKED_LIST_SINGLE_PLUS_H
#define __LINKED_LIST_SINGLE_PLUS_H

#include <cassert>
#include <iostream>

#define DRO3 if(0) // define as 'if(1)' to enable

template<typename T>
class SList {
protected:

    /** Node as structure */
    struct Node {
        T _value;
        Node *_next;
    };

public:

    /** 
     * Returns a new list that is the result of zipping together all passed-in lists.
     * If lists [a1, a2], [b1, b2, b3] are passed in, the output would be
     * [a1, b1, a2, b2, b3].
     * 
     * Passed-in lists are emptied of elements, as all elements are moved (not copied)
     * over to the list returned by zip.
     */
    static SList zip(SList &a, SList &b) {
         SList result, empty;
         result = zip(a, b, empty);
         return result;
    }

    static SList zip(SList &a, SList &b, SList &c) {
         SList result;
         int emptyes = 0;
         bool end = false;
         Node *na = a._head->_next;
         Node *nb = b._head->_next;
         Node *nc = c._head->_next;

         while (!end) {
             emptyes = 0;
             if (na != nullptr) {
                 result._tail->_next = na;
                 result._tail = na;
                 na = na->_next;
                // result.display(std::cout);
             }
             else
                 emptyes++;
             if (nb != nullptr) {
                 result._tail->_next = nb;
                 result._tail = nb;
                 nb = nb->_next;
             }
             else
                 emptyes++;
             if (nc != nullptr) {
                 result._tail->_next = nc;
                 result._tail = nc;
                 nc = nc->_next;
             }
             else
                 emptyes++;
             if (emptyes == 3)
                 end = true;
         }
         a._head->_next = b._head->_next = c._head->_next = nullptr;
         a._tail = a._head;
         b._tail = b._head;
         c._tail = c._head;
         return result;
    }

    /** O(1) */
    SList() {
        _head = new Node;
        DRO3 std::cerr << "+[" << _head << "]\n";   
        _head->_next = nullptr;
        _tail = _head;
    }

    /** O(n) */
    ~SList() {
        DRO3 std::cerr << "~[" << _head << "]\n";
        delete_list(_head);
    }

    /** O(n) */
    SList(const SList &other): _head(copy_nodes(other._head)) {
        DRO3 std::cerr << "[" << other._head << "]=>+[" << _head << "]\n";
        if ( ! other.empty()) {
          _tail = nth_node(other.size()-1);
        }
    }

    /** Assignment constructor. O(n) */
    SList<T> &operator=(const SList<T> &other) {
        if (this != &other) {
            delete_list(_head->_next);
            DRO3 std::cerr << "[" << other._head << "]=>=[" << _head << "]\n";
            _head->_next = copy_nodes(other._head->_next);
            if ( ! other.empty()) {
              _tail = nth_node(other.size()-1);
            }
        }
        return *this;
    }

    /** O(1)*/
    void push_front(const T &_elem) {
        Node *new_node = new Node { _elem, _head->_next };
        _head->_next = new_node;
        if(_tail == _head) //si la lista era unitaria
             _tail = new_node;
    }

    /** O(1)*/
    void push_back(const T &_elem);

    /** O(1) */
    void pop_front() {
        assert (_head->_next != nullptr);
        Node *old_head = _head->_next;
        _head->_next = _head->_next->_next;
        delete old_head;
        if(_head->_next == nullptr)
            _tail = _head;
    }

    /** O(n) */
    void pop_back();

    /** O(n) */
    int size() const;

    /** O(1)*/
    bool empty() const {
        return _head->_next == nullptr;
    };

    /** O(1)*/
    const T & front() const {
        assert (_head->_next != nullptr);
        return _head->_next->_value;
    }

    /** non-const front  O(1)*/
    T & front() {
        assert (_head->_next != nullptr);
        return _head->_next->_value;
    }

    /** O(1)*/
    const T & back() const {
        assert (_tail != nullptr);
        return _tail->_value;
    }

    /** non-const back O(1)*/
    T & back() {
        assert (_tail != nullptr);
        return _tail->_value;
    }

    /** O(n)*/
    const T & at(int index) const {
        Node *result_node = nth_node(index);
        assert (result_node != nullptr);
        return result_node->_value;
    }

    /** non-const at O(1)*/
    T & at(int index) {
        Node *result_node = nth_node(index);
        assert (result_node != nullptr);
        return result_node->_value;

    }

    /** output to a stream O(n)*/
    void display(std::ostream &out) const;

    /** O(n)*/
    void display() const {
        display(std::cout);
    }

private:
    /** pointer to 1st node */
    Node *_head;
    /** pointer to last node */
    Node *_tail;

    void delete_list(Node *start_node);
    Node *nth_node(int n) const;
    Node *copy_nodes(Node *start_node) const;

};


template <typename T>
typename SList<T>::Node * SList<T>::copy_nodes(Node *start_node) const {
  if (start_node != nullptr) {
    Node *result = new Node { start_node->_value, copy_nodes(start_node->_next) };
    return result;
  } else {
    return nullptr;
  }
}

template <typename T>
void SList<T>::delete_list(Node *start_node) {
  if (start_node != nullptr) {
    delete_list(start_node->_next);
    delete start_node;
  }
}

template <typename T>
void SList<T>::push_back(const T &_elem) {
  Node *new_node = new Node { _elem, nullptr };
  _tail->_next = new_node;
  _tail = _tail->_next;
}

template <typename T>
void SList<T>::pop_back() {
  assert (_head->_next != nullptr);
  Node *previous = _head;
  Node *current = _head->_next;

  while (current->_next != nullptr) {
    previous = current;
    current = current->_next;
  }

  delete current;
  previous->_next = nullptr;
  _tail = previous;
}

template <typename T>
int SList<T>::size() const {
  int num_nodes = 0;

  Node *current = _head->_next;
  while (current != nullptr) {
    num_nodes++;
    current = current->_next;
  }

  return num_nodes;
}

template <typename T>
typename SList<T>::Node * SList<T>::nth_node(int n) const {
  assert (0 <= n);
  int current_index = 0;
  Node *current = _head->_next;

  while (current_index < n && current != nullptr) {
    current_index++;
    current = current->_next;
  }

  return current;
}

template <typename T>
void SList<T>::display(std::ostream &out) const {
    if (_head->_next != nullptr) {
        out << _head->_next->_value;
        Node *current = _head->_next->_next;
        while (current != nullptr) {
            out << " " << current->_value;
            current = current->_next;
        }
    }
}


#endif
