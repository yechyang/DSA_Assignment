#include "Dictionary.h"
#include <iostream>
#include "Actor.h"
#include "Movie.h"
using namespace std;

// Constructor
// Initializes a hash table with a given initial size
// Time Complexity: O(N) - Initializes an array of size N
// Space Complexity: O(N) - Stores an array of pointers to linked list nodes
template <typename T>
Dictionary<T>::Dictionary(int initialSize) : size(initialSize), numElements(0) {
    table = new Node<T>*[size];
    for (int i = 0; i < size; ++i) {
        table[i] = nullptr;
    }
}

// Destructor
// Deallocates all dynamically allocated memory in the hash table
// Time Complexity: O(N) - Iterates through all buckets and deletes linked list nodes
// Space Complexity: O(1) - No extra space used, only deallocating memory
template <typename T>
Dictionary<T>::~Dictionary() {
    for (int i = 0; i < size; ++i) {
        Node<T>* current = table[i];
        while (current) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;  // Delete each node
        }
    }
    delete[] table;
}

// Hash function
template <typename T>
int Dictionary<T>::hashFunction(const int& key) const {
    return key % size;
}

// Insert with dynamic resizing
// Inserts a key-value pair into the hash table and resizes if load factor > 70%
// Time Complexity: O(1) (Average case), O(N) (Worst case when resizing)
// Space Complexity: O(1) (No extra space except new node, unless resizing occurs)
template <typename T>
void Dictionary<T>::insert(const int& key, const T& value) {
    if ((numElements / (float)size) > 0.7) { // Load factor > 70%
        resize();
    }

    int index = hashFunction(key);  // Compute index
    Node<T>* newNode = new Node<T>(key, value);

    if (!table[index]) {
        table[index] = newNode;  // Insert if bucket is empty
    } else {
        Node<T>* current = table[index];
        while (current->next) { // Traverse to the last node
            current = current->next;
        }
        current->next = newNode; // Append new node at end of linked list
    }
    numElements++;  // Increase element count
}

// Resize the dictionary when load factor is too high
// Time Complexity: O(N) - Rehashing requires iterating over all elements
// Space Complexity: O(N) - New array of double the size
template <typename T>
void Dictionary<T>::resize() {
    int newCapacity = size * 2; // Double the size
    Node<T>** newTable = new Node<T>*[newCapacity];  // Allocate new table

    for (int i = 0; i < newCapacity; ++i) {
        newTable[i] = nullptr;
    }

    // Rehash all elements
    for (int i = 0; i < size; ++i) {
        Node<T>* current = table[i];
        while (current) {
            Node<T>* temp = current;
            current = current->next;

            // Compute new index
            int newIndex = temp->key % newCapacity;
            temp->next = newTable[newIndex];
            newTable[newIndex] = temp;
        }
    }

    // Replace old table with new table
    delete[] table;
    table = newTable;
    size = newCapacity;

    cout << "Resized dictionary to " << size << " buckets.\n";
}

// Search for a value by key
// Returns a pointer to the value if found, else nullptr
// Time Complexity: O(1) (Average case), O(N) (Worst case if many collisions)
// Space Complexity: O(1)
template <typename T>
T* Dictionary<T>::search(const int& key) const {
    int index = hashFunction(key);
    Node<T>* current = table[index];

    while (current) {
        if (current->key == key) {
            return &(current->value);
        }
        current = current->next;
    }
    return nullptr;
}

// Manual trimming function (no STL)
// Removes leading and trailing spaces from a string
// Time Complexity: O(N)
// Space Complexity: O(1)
string trim(const string& str) {
    int start = 0;
    int end = str.length() - 1;

    // Trim leading spaces
    while (start <= end && (str[start] == ' ' || str[start] == '\t' || str[start] == '\n' || str[start] == '\r')) 
        start++;
    
    // Trim trailing spaces
    while (end >= start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n' || str[end] == '\r')) 
        end--;

    return str.substr(start, end - start + 1);
}

// Manual lowercase conversion (no STL)
string toLower(const string& str) {
    string lowerStr = "";
    for (int i = 0; i < str.length(); ++i) {
        char lowerChar = (str[i] >= 'A' && str[i] <= 'Z') ? (str[i] + 32) : str[i];
        lowerStr += lowerChar;
    }
    return lowerStr;
}

// Search for movies by title
// Returns an array of movie pointers if found, else nullptr
// Time Complexity: O(N) (Iterates through all buckets and linked list nodes)
// Space Complexity: O(K) (Stores matched movie pointers, where K is match count)
template <>
Movie** Dictionary<Movie>::searchByTitle(const string& name, int& matchCount) {
    matchCount = 0;
    Movie** matches = new Movie*[size];

    string searchName = toLower(trim(name));  // Clean user input for comparison

    for (int i = 0; i < size; ++i) {
        Node<Movie>* current = table[i];
        while (current != nullptr) {
            // Compare lowercase, trimmed names but keep original for display
            if (toLower(trim(current->value.getTitle())) == searchName) {
                matches[matchCount++] = &(current->value);
            }
            current = current->next;
        }
    }

    if (matchCount == 0) {
        delete[] matches;
        return nullptr;
    }

    return matches;
}

// Search for actors by name
// Returns an array of actor pointers if found, else nullptr
// Time Complexity: O(N) (Iterates through all buckets and linked list nodes)
// Space Complexity: O(K) (Stores matched actor pointers, where K is match count)
template <>
Actor** Dictionary<Actor>::searchByName(const string& name, int& matchCount) {
    matchCount = 0;
    Actor** matches = new Actor*[size];

    string searchName = toLower(trim(name));  // Clean user input for comparison

    for (int i = 0; i < size; ++i) {
        Node<Actor>* current = table[i];
        while (current != nullptr) {
            // Compare lowercase, trimmed names but keep original for display
            if (toLower(current->value.getName()) == searchName) {
                matches[matchCount++] = &(current->value);
            }
            current = current->next;
        }
    }

    if (matchCount == 0) {
        delete[] matches;
        return nullptr;
    }

    return matches;
}


// Remove a key-value pair
// Returns true if removed, false if key not found
// Time Complexity: O(1) (Average case), O(N) (Worst case with many collisions)
// Space Complexity: O(1)
template <typename T>
bool Dictionary<T>::remove(const int& key) {
    int index = hashFunction(key);
    Node<T>* current = table[index];
    Node<T>* previous = nullptr;

    while (current) {
        if (current->key == key) {
            if (previous) {
                previous->next = current->next;
            } else {
                table[index] = current->next;
            }
            delete current;
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false;
}

// Display all key-value pairs
template <typename T>
void Dictionary<T>::display(void (*displayFunc)(const T&)) const {
    for (int i = 0; i < size; ++i) {
        Node<T>* current = table[i];
        while (current) {
            displayFunc(current->value); // Call the user-provided function
            current = current->next;
        }
    }
}

// Explicit instantiation for specific types
template class Dictionary<Actor>;
template class Dictionary<Movie>;
template class Dictionary<bool>;