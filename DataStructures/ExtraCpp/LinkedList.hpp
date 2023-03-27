//
//  LinkedList.hpp
//  TestCpp
//
//  Created by Timur Murzakov on 25/03/2023.
//

#ifndef LinkedList_hpp
#define LinkedList_hpp

#define typeT template <typename T>

#include <iostream>

template <typename T>
class ListNode;

template <typename T>
class LinkedList;


typeT
class ListNode {
private:
    // Declaration of friend LinkedList for access to data in List
    friend LinkedList <T>;
    
    // Data contains in current Node
    T data;
    // Previous and next node references
    ListNode <T> *next, *prev;
    
public:
    // Constructor of a Node
    // parameters: const T - data will be stored in current Node
    ListNode(const T &);
    
    // Operators for easy-creating of a Node
    ListNode <T> &operator = (const T &);
    ListNode <T> &operator = (const ListNode <T> &);
    ListNode <T> &operator = (const ListNode <T> *);
};

typeT
class LinkedList {
private:
    uint_fast64_t _size;
    
    // List stores head and end elements(them pointers)
    ListNode <T> *head, *tail;
    
public:
    // Constructors overloaded
    // Constructors for creating list from vector
    LinkedList(std::vector <T> &vector);
    LinkedList(std::vector <T> *pntVector);
    // Constructor for creating list from classic array
    LinkedList(T *pntArray, uint_fast64_t size);
    // Constructors for creating list of only 1 element
    LinkedList(T &elem);
    LinkedList(T *elem);
    LinkedList(T elem);
    
    // Zero-constructor
    LinkedList();
    
    // Destructor
    ~LinkedList();
    
    // Read-only method returns size of current list
    uint_fast64_t size() const;
    // Read-only method returns true if list is empty else false
    bool isEmpty() const;
    
    /* Read-only method returns true if element-parameter
    /  contains in current list else false */
    bool isHere(const T &) const;
    
    // Classic add-method inserts element-parameter at the end
    void add(const T &);
    // Add-method inserts element-parameter at the index given
    void add(const T &, uint_fast64_t at);
    
    /* Remove-method erases element-parameter
    /  and certain pointers in current list
       BE AWARE: method erase only first-left element equals element-parameter */
    bool remove(const T &);
    // Remove-method erases element at the index given
    T remove(uint_fast64_t at);
    
    // Read-only method works like isHere(const T &) but returns element
    T receive(uint_fast64_t at) const;
    // Read-only operator[] works like receive(uint_fast64_t at)
    ListNode <T> &operator [] (uint_fast64_t at) const;
    
    /* Read-only method returns index of first-left element-parameter
       If element is not found, method return UINT_FAST64_MAX */
    uint_fast64_t indexOf(const T &) const;
    /* Method changes data node at the index given to element-parameter
       Returns old data of node */
    T change(const T &, uint_fast64_t at);
    
    // Read-only method returns slice-list(copy) of current list
    LinkedList <T> &receiveSlice(uint_fast64_t from, uint_fast64_t to) const;
    
    // Method swaps two elements of current list
    void swap(uint_fast64_t first, uint_fast64_t sec);
    
    // Method clear current list and pointers
    void eraseMe();
};

/*-IMPLEMENTATIONS-*/
/*==ListNode==*/

typeT
ListNode <T> ::ListNode(const T &val):
    data(val), next(nullptr), prev(nullptr) {}

typeT
ListNode <T> &ListNode <T> ::operator = (const T &val) {
    data = val;
    return *this;
}

typeT
ListNode <T> &ListNode <T> ::operator = (const ListNode <T> &node) {
    data = node.data;
    return *this;
}

typeT
ListNode <T> &ListNode <T> ::operator = (const ListNode <T> *pntNode) {
    data = pntNode->data;
    return *this;
}

/*-IMPLEMENTATIONS-*/
/*==ListNode==*/

typeT
LinkedList <T> ::LinkedList():
    head(nullptr), tail(nullptr), _size(0) {}

typeT
LinkedList<T> ::~LinkedList() {
    eraseMe();
    
    delete head;
    delete tail;
}

typeT
void LinkedList <T> ::eraseMe() {
    if (isEmpty()) {
        return;
    }
    
    ListNode <T> *curr = head;
    while (curr != nullptr) {
        if (curr->prev) {
            delete curr->prev;
            curr->prev = nullptr;
        }
        
        if (curr->next) {
            curr = curr->next;
        } else {
            delete curr;
            curr = nullptr;
        }
    }
    
    head = tail = nullptr;
    _size = 0;
}

typeT
uint_fast64_t LinkedList <T> ::size() const {
    return _size;
}

typeT
bool LinkedList <T> ::isEmpty() const {
    return (_size == 0);
}

typeT
bool LinkedList <T> ::isHere(const T &val) const {
    if (isEmpty()) {
        throw std::runtime_error("[LinkedList isHere(val)]: attempt of receiving element while the list is empty");
    }
    
    ListNode <T> *curr = head;
    
    while (curr != nullptr) {
        if (curr->data != val) {
            curr = curr->next;
        } else {
            return true;
        }
    } return false;
}

typeT
void LinkedList <T> ::add(const T &val) {
    ListNode <T> *newer = new ListNode <T> (val);
    
    if (!_size) {
        head = tail = newer;
    } else {
        newer->prev = tail;
        tail->next = newer;
        
        tail = newer;
    }   _size += 1;
}

typeT
void LinkedList <T> ::add(const T &val, uint_fast64_t ind) {
    if (!_size) {
        add(val);
        return;
    }
    
    if (ind < 0 || ind >= _size) {
        throw std::out_of_range("[LinkedList add(val, at)]: given wrong index");
    }
    
    ListNode <T> *curr = head;
    for (uint_fast64_t i = 0; i < ind; i++) {
        curr = curr->next;
    }
    
    ListNode <T> *newer = new ListNode <T> (val);
    newer->next = curr;
    newer->prev = curr->prev;
    
    if (curr->prev) {
        curr->prev->next = newer;
    }
    curr->prev = newer;
    
    if (ind == 0) {
        head = newer;
    }
    if (ind == _size - 1) {
        tail = newer->next;
    }
    
    _size += 1;
}

typeT
bool LinkedList <T> ::remove(const T & val) {
    if (isEmpty()) {
        throw std::runtime_error("[LinkedList remove(val)]: attempt of receiving element while the list is empty");
    }
    ListNode <T> *curr = head;
    
    bool isDone = false;
    while (curr != nullptr) {
        if (curr->data != val) {
            curr = curr->next;
            continue;
        }
        
        if (curr->prev) {
            curr->prev->next = curr->next;
        }
        if (curr->next) {
            curr->next->prev = curr->prev;
        }
        
        if (curr == tail && curr->prev) {
            tail = curr->prev;
        }
        if (curr == head && curr->next) {
            head = curr->next;
        }
        if (curr == tail && tail == head) {
            head = tail = nullptr;
        }
        
        curr->next = nullptr;
        curr->prev = nullptr;
        
        _size -= 1;
        
        isDone = true;
        break;
    }
    return isDone;
}

typeT
T LinkedList <T> ::remove(uint_fast64_t ind) {
    if (isEmpty()) {
        throw std::runtime_error("[LinkedList remove(ind)]: attempt of receiving element while the list is empty");
    }
    
    if (ind < 0 || ind >= _size) {
        throw std::out_of_range("[LinkedList remove(ind)]: given wrong index");
    }
    
    ListNode <T> *curr = head;
    for (uint_fast64_t i = 0; i < ind; i++) {
        curr = curr->next;
    }
    
    if (curr->prev) {
        curr->prev->next = curr->next;
    }
    if (curr->next) {
        curr->next->prev = curr->prev;
    }
    
    if (curr == tail && curr->prev) {
        tail = curr->prev;
    }
    if (curr == head && curr->next) {
        head = curr->next;
    }
    if (curr == tail && tail == head) {
        head = tail = nullptr;
    }
    
    curr->next = nullptr;
    curr->prev = nullptr;
    
    _size -= 1;
    
    return curr->data;
}

typeT
T LinkedList <T> ::receive(uint_fast64_t ind) const {
    if (isEmpty()) {
        throw std::runtime_error("[LinkedList receive(ind)]: attempt of receiving element while the list is empty");
    }
    
    if (ind < 0 || ind >= _size) {
        throw std::out_of_range("[LinkedList receive(at)]: given wrong index");
    }
    
    ListNode <T> *curr = head;
    for (uint_fast64_t i = 0; i < ind; i++) {
        curr = curr->next;
    }
    
    return curr->data;
}

typeT
ListNode <T> &LinkedList <T> ::operator [] (uint_fast64_t ind) const {
    if (isEmpty()) {
        throw std::runtime_error("[LinkedList operator[ind]]: attempt of receiving element while the list is empty");
    }
    
    if (ind < 0 || ind >= _size) {
        throw std::out_of_range("[LinkedList operator[ind]]: given wrong index");
    }
    
    ListNode <T> *curr = head;
    for (uint_fast64_t i = 0; i < ind; i++) {
        curr = curr->next;
    }
    
    return *curr;
}

typeT
uint_fast64_t LinkedList <T> ::indexOf(const T & val) const {
    if (!head) {
        throw std::runtime_error("[LinkedList indexOf(val)]: attempt of receiving index while the list is empty");
    }
    ListNode <T> *curr = head;
    
    for (int ind = 0; curr != nullptr; ind++) {
        if (curr->data == val) {
            return ind;
        }
        curr = curr->next;
    }
    
    return UINT_FAST64_MAX;
}

typeT
T LinkedList <T> ::change(const T & toVal, uint_fast64_t ind) {
    if (ind < 0 || ind >= _size) {
        throw std::out_of_range("[LinkedList change(to, ind)]: given wrong index");
    }
    
    ListNode <T> *curr = head;
    for (uint_fast64_t i = 0; i < ind; i++) {
        curr = curr->next;
    }
    
    T tmp = curr->data;
    curr->data = toVal;
    
    return tmp;
}

typeT
LinkedList <T> &LinkedList <T> ::receiveSlice(uint_fast64_t from, uint_fast64_t to) const {
    if (isEmpty()) {
        throw std::runtime_error("[LinkedList receiveSLice(from, to)]: attempt of receiving sublist while the list is empty");
    }
    
    if (to < from) {
        throw std::out_of_range("[LinkedList receiveSlice(from, to)]: given from > to");
    }
    if (from < 0) {
        throw std::out_of_range("[LinkedList receiveSlice(from, to)]: given wrong from index");
    }
    if (to >= _size) {
        throw std::out_of_range("[LinkedList receiveSlice(from, to)]: given wrong to index");
    }
    
    LinkedList <T> *newList = new LinkedList <T> ();
    
    ListNode <T> *curr = head;
    for (uint_fast64_t i = 0; i < from; i++) {
        curr = curr->next;
    }

    for (uint_fast64_t i = from; i <= to; i++) {
        newList->add(curr->data);
    }
    
    return *newList;
}

typeT
void LinkedList <T> ::swap(uint_fast64_t first, uint_fast64_t sec) {
    if (isEmpty()) {
        throw std::runtime_error("[LinkedList swap(first, sec)]: attempt of receiving elements while the list is empty");
    }
    
    if (first > sec) {
        throw std::out_of_range("[LinkedList swap(first, sec)]: given sec < first");
    }
    if (first < 0) {
        throw std::out_of_range("[LinkedList swap(first, sec)]: given wrong first index");
    }
    if (sec >= _size) {
        throw std::out_of_range("[LinkedList swap(first, sec)]: given wrong sec index");
    }
    
    ListNode <T> tmp = (*this)[first];
    (*this)[first] = (*this)[sec];
    (*this)[sec] = tmp;
}

#endif /* LinkedList_hpp */
