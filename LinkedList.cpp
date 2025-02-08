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
template <typename T>
bool LinkedList<T>::contains(T* data) const {
    ListNode<T>* current = head;
    while (current) {
        if (current->data == data) return true; // Found match
        current = current->next;
    }
    return false;
}

// **Appends an item at the end of the list** 
template <typename T>
void LinkedList<T>::append(T* data) {
    ListNode<T>* newNode = new ListNode<T>(data);
    if (!head) {
        head = newNode;
        return;
    }
    ListNode<T>* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}

// **Inserts at the head (Prepend)**
template <typename T>
void LinkedList<T>::insert(T* data) {
    ListNode<T>* newNode = new ListNode<T>(data);
    newNode->next = head;
    head = newNode;
}

// **Removes an item**
template <typename T>
bool LinkedList<T>::remove(T* data) {
    ListNode<T>* current = head;
    ListNode<T>* prev = nullptr;

    while (current) {
        if (current->data == data) {
            if (prev) {
                prev->next = current->next;
            } else {
                head = current->next;
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
template <typename T>
void LinkedList<T>::display(void (*displayFunc)(const T&)) const {
    ListNode<T>* current = head;
    while (current) {
        displayFunc(*(current->data));  // Call display function for each node
        current = current->next;
    }
}

// **Counts the number of elements**
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
template <typename T>
T** LinkedList<T>::toArray(int& count) const {
    count = this->count();
    if (count == 0) return nullptr;

    T** array = new T*[count];
    ListNode<T>* current = head;
    for (int i = 0; i < count; ++i) {
        array[i] = current->data;
        current = current->next;
    }
    return array;
}

// **Returns head node**
template <typename T>
ListNode<T>* LinkedList<T>::getHead() const {
    return head;
}

// Explicit instantiations
template class LinkedList<Movie>;
template class LinkedList<Actor>;  