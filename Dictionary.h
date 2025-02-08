#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <string>
using namespace std;

// Node structure for the hash table
template <typename T>
struct Node {
    int key; // Unique key (e.g., Movie ID or Actor ID)
    T value;    // Value stored in the dictionary
    Node* next; // Pointer for collision resolution (chaining)

    Node(const int& key, const T& value) : key(key), value(value), next(nullptr) {}
};

template <typename T>
class Dictionary {
private:
    Node<T>** table; // Array of pointers to Node (buckets)
    int size;        // Size of the hash table
    int numElements;

    // Hash function to compute an index
    int hashFunction(const int& key) const;
    void resize();

public:
    Dictionary(int initialSize = 10);   // Constructor
    ~Dictionary();               // Destructor

    // Add a key-value pair to the dictionary
    void insert(const int& key, const T& value);

    // Search for a value by key
    T* search(const int& key) const;

    // New search functions

    // In Dictionary class declaration
    T** searchByTitle(const string& name, int& matchCount);
    T** searchByName(const string& name, int& matchCount);

    // Remove a key-value pair by key
    bool remove(const int& key);

    // Display all key-value pairs
    void display(void (*displayFunc)(const T&)) const;
    
    int getSize() const { return size; }
};

#endif