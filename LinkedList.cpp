#include "LinkedList.h"
#include <iostream>
using namespace std;

// Constructor
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr) {}

// Destructor (Deletes all nodes)
template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

// **Clears the entire list**  
// Iterates through the list, deleting all nodes and resetting `head` to `nullptr`.
// Time Complexity: O(N)  
// Space Complexity: O(1)
template <typename T>
void LinkedList<T>::clear() {
    ListNode<T>* current = head;
    while (current) {
        ListNode<T>* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
}

// **Checks if an item exists in the list**  
// Traverses the list and returns true if `data` is found, false otherwise.  
// Time Complexity: O(N) (Worst case: item is at the end or not in the list)  
// Space Complexity: O(1)
template <typename T>
bool LinkedList<T>::contains(T* data) const {
    ListNode<T>* current = head;
    while (current) {
        if (current->data == data) return true; // Found match
        current = current->next;
    }
    return false;  // Data not found
}

// **Appends an item at the end of the list**  
// Adds a new node with `data` at the tail of the list.  
// Time Complexity: O(N) (Worst case: traverse entire list to find last node)  
// Space Complexity: O(1)
template <typename T>
void LinkedList<T>::append(T* data) {
    ListNode<T>* newNode = new ListNode<T>(data);
    if (!head) {
        head = newNode;
        return;
    }

    // Traverse to the last node
    ListNode<T>* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}

// **Inserts at the head (Prepend)**  
// Inserts a new node with `data` at the beginning of the list.  
// Time Complexity: O(1) (Constant time since only head is modified)  
// Space Complexity: O(1)
template <typename T>
void LinkedList<T>::insert(T* data) {
    ListNode<T>* newNode = new ListNode<T>(data);
    newNode->next = head;
    head = newNode;
}

// **Removes an item from the list**  
// Searches for `data`, removes it if found, and updates the list accordingly.  
// Time Complexity: O(N) (Worst case: item is at the end or not in the list)  
// Space Complexity: O(1)
template <typename T>
bool LinkedList<T>::remove(T* data) {
    ListNode<T>* current = head;
    ListNode<T>* prev = nullptr;

    while (current) {
        if (current->data == data) { // Found node to remove
            if (prev) {
                prev->next = current->next; // Skip over the current node
            } else {
                head = current->next; // Update head if first node is removed
            }
            delete current;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

// **Displays all elements**
// Time Complexity: O(N) (Iterates through all elements)  
template <typename T>
void LinkedList<T>::display(void (*displayFunc)(const T&)) const {
    ListNode<T>* current = head;
    while (current) {
        displayFunc(*(current->data));  // Call display function for each node
        current = current->next;
    }
}

// **Counts the number of elements in the list**  
// Iterates through the list and returns the total count.  
// Time Complexity: O(N)  
// Space Complexity: O(1)
template <typename T>
int LinkedList<T>::count() const {
    int count = 0;
    ListNode<T>* current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

// **Converts linked list to an array**  
// Creates a dynamically allocated array containing all elements in the list.  
// Time Complexity: O(N) (Traverses the list twice: once to count, once to copy)  
// Space Complexity: O(N) (Creates a new array of size N)
template <typename T>
T** LinkedList<T>::toArray(int& count) const {
    count = this->count(); // Get the number of elements
    if (count == 0) return nullptr; // If empty, return nullptr

    T** array = new T*[count];
    ListNode<T>* current = head;
    for (int i = 0; i < count; ++i) {
        array[i] = current->data; // Copy each element to array
        current = current->next;
    }
    return array;
}

// **Returns head node**  
// Provides access to the first node in the list.  
// Time Complexity: O(1)  
// Space Complexity: O(1)
template <typename T>
ListNode<T>* LinkedList<T>::getHead() const {
    return head;
}

// Explicit instantiations
template class LinkedList<Movie>;
template class LinkedList<Actor>;  