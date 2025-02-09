#ifndef AVLTREE_CPP
#define AVLTREE_CPP
#include "Dictionary.h"
#include "AVLTree.h"
#include "Actor.h"
#include "Movie.h"

// Constructor
template <typename T>
AVLTree<T>::AVLTree(int (*keyFunction)(T*)) : root(nullptr), keyFunc(keyFunction) {}

// Get height of a node
template <typename T>
int AVLTree<T>::height(AVLNode<T>* node) {
    if (!node) return 0;
    return node->height;
}

// Get balance factor
template <typename T>
int AVLTree<T>::getBalance(AVLNode<T>* node) {
    if (!node) return 0;
    return height(node->left) - height(node->right);
}

// Function to return the larger of two integers
template <typename T>
int AVLTree<T>::getLarger(int a, int b) {
    return (a > b) ? a : b;
}

// Right Rotate (for balancing)
// Used to fix left-heavy trees;
template <typename T>
AVLNode<T>* AVLTree<T>::rightRotate(AVLNode<T>* nodeN) {
    AVLNode<T>* nodeC = nodeN->left;
    nodeN->left = nodeC->right;
    nodeC->right = nodeN;

    // Update heights manually
    nodeN->height = getLarger(height(nodeN->left), height(nodeN->right)) + 1;
    nodeC->height = getLarger(height(nodeC->left), height(nodeC->right)) + 1;

    return nodeC;
}

// Left Rotate
// Used to fix right-heavy imbalance
template <typename T>
AVLNode<T>* AVLTree<T>::leftRotate(AVLNode<T>* nodeN) {
    AVLNode<T>* nodeC = nodeN->right;
    nodeN->right = nodeC->left;
    nodeC->left = nodeN;

    // Update heights manually
    nodeN->height = getLarger(height(nodeN->left), height(nodeN->right)) + 1;
    nodeC->height = getLarger(height(nodeC->left), height(nodeC->right)) + 1;

    return nodeC;
}

// Insert a node into the AVL Tree
// Balances the tree if necessary
// Time Complexity: O(log N) - Height balancing ensures logarithmic insertion
// Space Complexity: O(log N) - Due to recursive function call stack
template <typename T>
AVLNode<T>* AVLTree<T>::insert(AVLNode<T>* node, T* data) {
    if (!node) return new AVLNode<T>(data, keyFunc(data)); // Insert new node

    int key = keyFunc(data);

    if (key < node->key) {
        node->left = insert(node->left, data);
    } else if (key > node->key) {
        node->right = insert(node->right, data);
    } else {
        // Allow updating existing nodes (if needed)
        node->data = data;  
        return node;
    }

    // Update height after insertion
    node->height = getLarger(height(node->left), height(node->right)) + 1;

    // Balance the node
    int balance = getBalance(node);

    // Left Heavy (Right Rotation)
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Heavy (Left Rotation)
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left-Right (Left Rotation then Right Rotation)
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right-Left (Right Rotation then Left Rotation)
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Public insert function for Actor
template <>
void AVLTree<Actor>::insert(Actor* data) {
    int key = keyFunc(data);
    root = insert(root, data);
}

// Public insert function for Movie
template <>
void AVLTree<Movie>::insert(Movie* data) {
    int key = keyFunc(data);
    root = insert(root, data);
}

// Find the node with the minimum key in a subtree
// Time Complexity: O(log N)
// Space Complexity: O(1)
template <typename T>
AVLNode<T>* AVLTree<T>::findMin(AVLNode<T>* node) {
    while (node->left) node = node->left;
    return node;
}

// Remove a node from the AVL Tree
// Time Complexity: O(log N)
// Space Complexity: O(log N)
template <typename T>
AVLNode<T>* AVLTree<T>::remove(AVLNode<T>* node, T* data) {
    if (!node) return nullptr;

    int key = keyFunc(data);
    
    if (key < node->key) {
        node->left = remove(node->left, data);
    } else if (key > node->key) {
        node->right = remove(node->right, data);
    } else {
        // Node with only one child or no child
        if (!node->left || !node->right) {
            AVLNode<T>* temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        }
        // Node with two children: Get the inorder successor
        AVLNode<T>* temp = findMin(node->right);
        node->data = temp->data;
        node->key = temp->key;
        node->right = remove(node->right, temp->data);
    }

    if (!node) return nullptr;

    // Update height
    node->height = getLarger(height(node->left), height(node->right)) + 1;

    // Rebalance the tree
    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);

    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);

    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Public remove function
template <typename T>
void AVLTree<T>::remove(T* data) {
    root = remove(root, data);
}

// Update a node by removing and reinserting
// Time Complexity: O(log N)
// Space Complexity: O(log N)
template <typename T>
void AVLTree<T>::update(T* oldData, T* newData) {
    remove(oldData);  // Remove old node
    insert(newData);  // Insert updated node
}

// // Helper function for in-order traversal
// template <typename T>
// void AVLTree<T>::displayAll(AVLNode<T>* node) {
//     if (!node) return;

//     // Visit left subtree (younger actors)
//     displayAll(node->left);

//     // Display current actor
//     if constexpr (std::is_same<T, Actor>::value) {
//         std::cout << "Actor ID: " << node->data->getId()
//                   << ", Name: " << node->data->getName()
//                   << ", Age: " << (2025 - node->data->getBirthYear()) << std::endl;
//     }

//     // Visit right subtree (older actors)
//     displayAll(node->right);
// }

// // Public function to display all nodes
// template <typename T>
// void AVLTree<T>::displayAll() {
//     displayAll(root);
// }

// Display all actors within a specific age range
// Time Complexity: O(N) (In-order traversal)
// Space Complexity: O(N) (Recursive stack)
template <>
void AVLTree<Actor>::displayActorsInAgeRange(AVLNode<Actor>* node, int minAge, int maxAge) {
    if (!node) return;

    int currentYear = 2025;
    int actorAge = currentYear - node->data->getBirthYear();

    if (actorAge >= minAge) {
        displayActorsInAgeRange(node->left, minAge, maxAge);
    }

    if (actorAge >= minAge && actorAge <= maxAge) {
        cout << "Actor ID: " << node->data->getId()
             << ", Name: " << node->data->getName()
             << ", Age: " << actorAge << endl;
    }

    if (actorAge <= maxAge) {
        displayActorsInAgeRange(node->right, minAge, maxAge);
    }
}

// Public function to display actors in age range (Specialization for Actor)
template <>
void AVLTree<Actor>::displayActorsInAgeRange(int minAge, int maxAge) {
    std::cout << "\nActors with age between " << minAge << " and " << maxAge << " (sorted by age):\n";
    displayActorsInAgeRange(root, minAge, maxAge);
}

// Function to display movies released within a given year range
// Uses in-order traversal to visit nodes in sorted order
// Time Complexity: O(N) - Visits each node once in the worst case
// Space Complexity: O(log N) - Due to recursive call stack (worst case O(N) if unbalanced)
template <>
void AVLTree<Movie>::displayMoviesInRange(AVLNode<Movie>* node, int minYear, int maxYear) {
    if (!node) return;

    int movieYear = node->data->getReleaseYear();

    // Ensure correct traversal for all cases
    if (movieYear >= minYear)  // Move left to check for earlier years (including minYear)
        displayMoviesInRange(node->left, minYear, maxYear);

    if (movieYear >= minYear && movieYear <= maxYear) {  // Print movies inside the range
        std::cout << "Movie ID: " << node->data->getId()
                  << ", Title: " << node->data->getTitle()
                  << ", Release Year: " << movieYear << std::endl;
    }

    if (movieYear <= maxYear)  // Move right to check for later years (including maxYear)
        displayMoviesInRange(node->right, minYear, maxYear);
}

// Public function for calling from menu
template <>
void AVLTree<Movie>::displayMoviesInRange(int minYear, int maxYear) {
    // std::cout << "\nMovies released between " << minYear << " and " << maxYear << " (sorted by year):\n";
    displayMoviesInRange(root, minYear, maxYear);
}

// Helper function for in-order traversal (prints movies in sorted order)
template <>
void AVLTree<Movie>::displayAllMovies(AVLNode<Movie>* node) {
    if (!node) return;

    // Traverse left subtree (older movies)
    displayAllMovies(node->left);

    // Print current movie details
    std::cout << "Movie ID: " << node->data->getId()
              << ", Title: " << node->data->getTitle()
              << ", Release Year: " << node->data->getReleaseYear() << std::endl;

    // Traverse right subtree (newer movies)
    displayAllMovies(node->right);
}

// Public function to display all movies sorted by year
template <>
void AVLTree<Movie>::displayAllMovies() {
    std::cout << "\nAll Movies in AVL Tree (Sorted by Year):\n";
    displayAllMovies(root);
}

// Explicit instantiation for Actor and Movie
template class AVLTree<Actor>;
template class AVLTree<Movie>;

#endif
