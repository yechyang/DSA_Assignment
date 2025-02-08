#include <iostream>
#include "Dictionary.h"
#include "Actor.h"
#include "Movie.h"

// Generic AVL Tree Node
template <typename T>
struct AVLNode {
    T* data;
    int key;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(T* data, int key) : data(data), key(key), height(1), left(nullptr), right(nullptr) {}
};

// Generic AVL Tree Class
template <typename T>
class AVLTree {
private:
    AVLNode<T>* root;
    int (*keyFunc)(T*);  // Function pointer to extract the key from an object

    // Helper functions (private)
    int height(AVLNode<T>* node);
    int getBalance(AVLNode<T>* node);
    int getLarger(int a, int b);
    AVLNode<T>* rightRotate(AVLNode<T>* y);
    AVLNode<T>* leftRotate(AVLNode<T>* x);
    AVLNode<T>* insert(AVLNode<T>* node, T* data);
    AVLNode<T>* remove(AVLNode<T>* node, T* data);
    AVLNode<T>* findMin(AVLNode<T>* node);
    // void displayAll(AVLNode<T>* node);
    void displayActorsInAgeRange(AVLNode<T>* node,int minAge, int maxAge);
    void displayMoviesInRange(AVLNode<T>* node, int minYear, int maxYear);
    void displayAllMovies(AVLNode<Movie>* node);
public:
    // Constructor
    AVLTree(int (*keyFunction)(T*));

    // Insert
    void insert(T* data);
    void remove(T* data);
    void update(T* oldData, T* newData);

    // void displayAll();

    void displayActorsInAgeRange(int minAge, int maxAge);

    void displayMoviesInRange(int minYear, int maxYear);
    void displayAllMovies();
};
