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

    // ----- Helper functions (private) -
    
    // **Gets the height of a node**
    // Purpose: Returns the height of a given node.
    // Pre-condition: The node must be valid or nullptr.
    // Post-condition: Returns the height value.----
    int height(AVLNode<T>* node);

    // **Calculates the balance factor of a node**
    // Purpose: Determines whether the tree is balanced.
    // Pre-condition: The node must be valid.
    // Post-condition: Returns the balance factor (left height - right height).
    int getBalance(AVLNode<T>* node);

    // **Finds the larger of two integers**
    // Purpose: Returns the maximum of two values.
    // Pre-condition: Two integer inputs must be provided.
    // Post-condition: The larger of the two integers is returned.
    int getLarger(int a, int b);

    // **Performs a right rotation**
    // Purpose: Balances the tree when it is left-heavy.
    // Pre-condition: The node must be imbalanced (LL case).
    // Post-condition: The tree is rotated to the right to restore balance.
    AVLNode<T>* rightRotate(AVLNode<T>* y);

    // **Performs a left rotation**
    // Purpose: Balances the tree when it is right-heavy.
    // Pre-condition: The node must be imbalanced (RR case).
    // Post-condition: The tree is rotated to the left to restore balance.
    AVLNode<T>* leftRotate(AVLNode<T>* x);

    // **Inserts a node into the AVL tree**
    // Purpose: Adds a new element while maintaining balance.
    // Pre-condition: Data must be valid, and keyFunc must be initialized.
    // Post-condition: The node is inserted, and the tree remains balanced.
    AVLNode<T>* insert(AVLNode<T>* node, T* data);

    // **Removes a node from the AVL tree**
    // Purpose: Deletes an element and maintains balance.
    // Pre-condition: The tree must contain the node to be removed.
    // Post-condition: The node is removed, and the tree is rebalanced.
    AVLNode<T>* remove(AVLNode<T>* node, T* data);

    // **Finds the minimum value node in a subtree**
    // Purpose: Retrieves the leftmost node in a given subtree.
    // Pre-condition: The node must not be nullptr.
    // Post-condition: Returns the node with the smallest key.
    AVLNode<T>* findMin(AVLNode<T>* node);

    // **Displays actors in a given age range**
    // Purpose: Retrieves and prints actors within the specified age range.
    // Pre-condition: The tree must contain actor data.
    // Post-condition: Only actors within the given age range are displayed.
    void displayActorsInAgeRange(AVLNode<T>* node,int minAge, int maxAge);

    // **Displays movies in a specified year range**
    // Purpose: Retrieves and prints movies released within the given year range.
    // Pre-condition: The tree must contain movie data.
    // Post-condition: Movies within the range are displayed in sorted order.
    void displayMoviesInRange(AVLNode<T>* node, int minYear, int maxYear);

    // **Displays all movies stored in the AVL tree**
    // Purpose: Prints a sorted list of all movies.
    // Pre-condition: The tree must not be empty.
    // Post-condition: All stored movies are displayed in order.
    void displayAllMovies(AVLNode<Movie>* node);
public:
    // **Constructor**
    // Purpose: Initializes an empty AVL tree.
    // Pre-condition: Key function must be provided.
    // Post-condition: An empty AVL tree is created.
    AVLTree(int (*keyFunction)(T*));

    // **Inserts a node into the AVL tree**
    // Purpose: Adds a new object while maintaining balance.
    // Pre-condition: Object must be valid.
    // Post-condition: Object is inserted into the AVL tree.
    void insert(T* data);

    // **Removes a node from the AVL tree**
    // Purpose: Deletes an element from the tree.
    // Pre-condition: Object must exist in the tree.
    // Post-condition: Object is removed, and the tree remains balanced.
    void remove(T* data);

    // **Updates an existing node**
    // Purpose: Replaces an old object with a new one.
    // Pre-condition: Old object must exist in the tree.
    // Post-condition: Old object is removed, and the new object is inserted.
    void update(T* oldData, T* newData);

    // **Displays all actors within a specified age range**
    // Purpose: Lists actors who fall within the given age criteria.
    // Pre-condition: Tree must store actor data.
    // Post-condition: Actors in the given range are displayed.
    void displayActorsInAgeRange(int minAge, int maxAge);

    // **Displays movies released within a specific year range**
    // Purpose: Lists movies that match the given criteria.
    // Pre-condition: Tree must store movie data.
    // Post-condition: Matching movies are displayed.
    void displayMoviesInRange(int minYear, int maxYear);

    // **Displays all stored movies**
    // Purpose: Prints a complete sorted list of all movies.
    // Pre-condition: Tree must not be empty.
    // Post-condition: All movies are displayed in chronological order.
    void displayAllMovies();
};
