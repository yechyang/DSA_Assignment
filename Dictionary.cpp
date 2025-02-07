#include "Dictionary.h"
#include <iostream>
#include "Actor.h"
#include "Movie.h"
using namespace std;

// Constructor
template <typename T>
Dictionary<T>::Dictionary(int tableSize) : size(tableSize) {
    table = new Node<T>*[size];
    for (int i = 0; i < size; ++i) {
        table[i] = nullptr;
    }
}

// Destructor
template <typename T>
Dictionary<T>::~Dictionary() {
    for (int i = 0; i < size; ++i) {
        Node<T>* current = table[i];
        while (current) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] table;
}

// Hash function
template <typename T>
int Dictionary<T>::hashFunction(const int& key) const {
    return key % size;
}

// Insert a key-value pair
template <typename T>
void Dictionary<T>::insert(const int& key, const T& value) {
    int index = hashFunction(key);
    Node<T>* newNode = new Node<T>(key, value);

    if (!table[index]) {
        table[index] = newNode;
    } else {
        Node<T>* current = table[index];
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Search for a value by key
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

// Search for actors by name, allowing multiple matches
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