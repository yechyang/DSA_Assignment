#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

// Node structure for LinkedList
template <typename T>
struct ListNode {
    T* data;
    ListNode* next;

    ListNode(T* data) : data(data), next(nullptr) {}
};

// Linked List Class
template <typename T>
class LinkedList {
private:
    ListNode<T>* head; // Head pointer

public:
    // Constructor & Destructor
    LinkedList();
    ~LinkedList();
    
    // **New Methods**
    void clear();   // Clears the entire linked list
    bool contains(T* data) const; // Check if element exists
    void append(T* data);  // Add at the end of the list

    // Linked List Operations
    void insert(T* data);
    bool remove(T* data);
    void display(void (*displayFunc)(const T&)) const;
    int count() const;

    // Getters
    ListNode<T>* getHead() const;
    T** toArray(int& count) const; // Convert linked list to array for sorting
};

// Explicit template instantiation for Movie
extern template class LinkedList<class Movie>;
extern template class LinkedList<class Actor>;

#endif