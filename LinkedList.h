#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

// Node structure for LinkedList
template <typename T>
struct ListNode {
    T* data;          // Pointer to the actual data
    ListNode* next;   // Pointer to the next node

    ListNode(T* data) : data(data), next(nullptr) {}
};

// Linked List Class
template <typename T>
class LinkedList {
private:
    ListNode<T>* head; // Head pointer (first node of the list)

public:
    // Constructor
    // Pre-condition: None
    // Post-condition: Initializes an empty linked list
    LinkedList();

    // Destructor
    // Pre-condition: None
    // Post-condition: Deletes all elements and frees memory
    ~LinkedList();
    
    // Clears the entire linked list
    // Pre-condition: None
    // Post-condition: All nodes in the list are deleted, and head is set to nullptr
    void clear();   

    // Checks if an element exists in the list
    // Pre-condition: The list may be empty or contain elements
    // Post-condition: Returns true if the element is found, false otherwise
    // Condition: The comparison is done using pointer equality
    // Return: true if found, false if not found
    bool contains(T* data) const;

    // Appends an element at the end of the list
    // Pre-condition: data must not be nullptr
    // Post-condition: A new node containing data is added at the end
    // Condition: If the list is empty, the new node becomes the head
    void append(T* data);

    // Inserts an element at the head (beginning) of the list
    // Pre-condition: data must not be nullptr
    // Post-condition: A new node containing data is inserted at the front
    // Condition: If the list is empty, the new node becomes the head
    void insert(T* data);

    // Removes an element from the list
    // Pre-condition: The list may be empty or contain elements
    // Post-condition: If found, the node containing data is removed
    // Condition: The first occurrence of data is deleted if it exists
    // Return: true if deletion was successful, false if not found
    bool remove(T* data);

    // Displays all elements using a function pointer
    // Pre-condition: displayFunc must be a valid function that takes T&
    // Post-condition: Prints all elements in the list
    // Condition: If the list is empty, nothing is displayed
    void display(void (*displayFunc)(const T&)) const;

    // Counts the number of elements in the list
    // Pre-condition: None
    // Post-condition: Returns the total number of nodes in the list
    // Condition: If the list is empty, count is 0
    // Return: The total count of elements in the list
    int count() const;

    // Converts the linked list to a dynamic array for sorting
    // Pre-condition: None
    // Post-condition: Returns a dynamically allocated array containing list elements
    // Condition: If the list is empty, returns nullptr
    // Return: A pointer to the array of elements, caller must free memory
    T** toArray(int& count) const;

    // Returns the head node of the list
    // Pre-condition: None
    // Post-condition: Returns a pointer to the first node
    // Condition: If the list is empty, returns nullptr
    // Return: A pointer to the first node in the list
    ListNode<T>* getHead() const;
};

// Explicit template instantiations for Movie and Actor
extern template class LinkedList<class Movie>;
extern template class LinkedList<class Actor>;

#endif