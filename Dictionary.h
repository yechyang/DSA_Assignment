#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <string>
using namespace std;

// Node structure for the hash table
template <typename T>
struct Node {
    int key;      // Unique key (e.g., Movie ID or Actor ID)
    T value;      // Value stored in the dictionary
    Node* next;   // Pointer for collision resolution (chaining)

    // Constructor
    // Pre-condition: Key must be an integer, and value must be of type T.
    // Post-condition: Initializes a Node with key and value, sets next to nullptr.
    Node(const int& key, const T& value) : key(key), value(value), next(nullptr) {}
};

template <typename T>
class Dictionary {
private:
    Node<T>** table; // Array of pointers to Node (buckets)
    int size;        // Size of the hash table
    int numElements; // Number of elements in the dictionary

    // Computes the hash index for a given key
    // Pre-condition: key must be an integer.
    // Post-condition: Returns the index computed using hash function.
    int hashFunction(const int& key) const;

    // Resizes the dictionary when the load factor exceeds 70%
    // Pre-condition: Dictionary exists with some elements.
    // Post-condition: Expands the dictionary to double its current size and rehashes elements.
    void resize();

public:
    // Constructor
    // Pre-condition: initialSize must be a positive integer.
    // Post-condition: Initializes an empty hash table of given size.
    Dictionary(int initialSize = 10);

    // Destructor
    // Pre-condition: Dictionary must exist.
    // Post-condition: Frees memory allocated for hash table and all nodes.
    ~Dictionary();

    // Inserts a key-value pair into the dictionary
    // Pre-condition: key must be an integer, and value must be of type T.
    // Post-condition: Adds the key-value pair, resizes if load factor > 70%.
    void insert(const int& key, const T& value);

    // Searches for a value by key
    // Pre-condition: Dictionary must be initialized.
    // Post-condition: Returns a pointer to the value if found, otherwise returns nullptr.
    T* search(const int& key) const;

    // Searches for movies by title (specialized for Movie type)
    // Pre-condition: Dictionary must contain Movie objects.
    // Post-condition: Returns a pointer to an array of matching Movie objects.
    // Return: Dynamically allocated array (caller must free).
    T** searchByTitle(const string& name, int& matchCount);

    // Searches for actors by name (specialized for Actor type)
    // Pre-condition: Dictionary must contain Actor objects.
    // Post-condition: Returns a pointer to an array of matching Actor objects.
    // Return: Dynamically allocated array (caller must free).
    T** searchByName(const string& name, int& matchCount);

    // Removes a key-value pair from the dictionary
    // Pre-condition: Dictionary must contain elements.
    // Post-condition: Removes the element if found, returns true; otherwise returns false.
    bool remove(const int& key);

    // Displays all key-value pairs using a custom display function
    // Pre-condition: A valid function pointer must be provided.
    // Post-condition: Calls displayFunc for each element in the dictionary.
    void display(void (*displayFunc)(const T&)) const;

    // Returns the current size of the dictionary
    // Pre-condition: Dictionary must be initialized.
    // Post-condition: Returns the total number of buckets in the hash table.
    int getSize() const { return size; }
};

#endif