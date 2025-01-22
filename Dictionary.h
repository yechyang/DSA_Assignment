// #ifndef DICTIONARY_H
// #define DICTIONARY_H

// #include <iostream>
// #include <string>
// using namespace std;

// // Node structure for the hash table
// struct Node {
//     string key;  // Unique key (e.g., Movie ID or Actor ID)
//     void* value; // Pointer to hold either Movie or Actor data
//     Node* next;  // Pointer for collision resolution (chaining)

//     Node(const string& key, void* value) : key(key), value(value), next(nullptr) {}
// };

// class Dictionary {
// private:
//     Node** table;  // Array of pointers to Node (buckets)
//     int size;      // Size of the hash table

//     // Hash function to compute an index
//     int hashFunction(const string& key) const;

// public:
//     Dictionary(int tableSize);   // Constructor
//     ~Dictionary();               // Destructor

//     // Add a key-value pair to the dictionary
//     void insert(const string& key, void* value);

//     // Search for a value by key
//     void* search(const string& key) const;

//     // Remove a key-value pair by key
//     bool remove(const string& key);

//     // Display all key-value pairs
//     void display(void (*displayFunc)(void*)) const;
// };

// #endif


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

    // Hash function to compute an index
    int hashFunction(const int& key) const;

public:
    Dictionary(int tableSize);   // Constructor
    ~Dictionary();               // Destructor

    // Add a key-value pair to the dictionary
    void insert(const int& key, const T& value);

    // Search for a value by key
    T* search(const int& key) const;

    // Remove a key-value pair by key
    bool remove(const int& key);

    // Display all key-value pairs
    void display(void (*displayFunc)(const T&)) const;
    
    int getSize() const { return size; }
};

#endif