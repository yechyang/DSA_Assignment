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

// Left Rotate (for balancing)
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

// Insert a node
template <typename T>
AVLNode<T>* AVLTree<T>::insert(AVLNode<T>* node, T* data) {
    if (!node) return new AVLNode<T>(data, keyFunc(data));

    int key = keyFunc(data);
    if (key < node->key)
        node->left = insert(node->left, data);
    else if (key > node->key)
        node->right = insert(node->right, data);
    else {
        return node; // Prevent duplicate keys
    }

    // Update height manually
    node->height = getLarger(height(node->left), height(node->right)) + 1;

    // Balance the node
    int balance = getBalance(node);

    // 🛠 **Fix: Assign the rotated subtree to `node`**
    if (balance > 1 && key < node->left->key)
        return rightRotate(node); 

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}


// Public insert function
template <>
void AVLTree<Actor>::insert(Actor* data) {
    int key = keyFunc(data);
    std::cout << "Inserting into AVLTree: " << data->getName() 
              << " with Key: " << key << std::endl;
    root = insert(root, data);
}

// Public insert function for Movie
template <>
void AVLTree<Movie>::insert(Movie* data) {
    int key = keyFunc(data);
    std::cout << "Inserting into AVLTree: " << data->getTitle() 
              << " with Key: " << key << std::endl;
    root = insert(root, data);
}

// Find minimum node in subtree
template <typename T>
AVLNode<T>* AVLTree<T>::findMin(AVLNode<T>* node) {
    while (node->left) node = node->left;
    return node;
}

// Remove a node
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

    node->height = getLarger(height(node->left), height(node->right)) + 1;

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

// Function to display actors in a specific age range
template <>
void AVLTree<Actor>::displayActorsInAgeRange(AVLNode<Actor>* node, int minAge, int maxAge) {
    if (!node) return;

    int currentYear = 2025;
    int actorAge = currentYear - node->data->getBirthYear();

    // 🔄 Move left to check for younger actors
    if (actorAge >= minAge)
        displayActorsInAgeRange(node->left, minAge, maxAge);

    // ✅ Print actors inside the range
    if (actorAge >= minAge && actorAge <= maxAge) {
        std::cout << "Actor ID: " << node->data->getId()
                  << ", Name: " << node->data->getName()
                  << ", Age: " << actorAge << std::endl;
    }

    // 🔄 Move right to check for older actors
    if (actorAge <= maxAge)
        displayActorsInAgeRange(node->right, minAge, maxAge);
}

// Public function to display actors in age range (Specialization for Actor)
template <>
void AVLTree<Actor>::displayActorsInAgeRange(int minAge, int maxAge) {
    std::cout << "\nActors with age between " << minAge << " and " << maxAge << " (sorted by age):\n";
    displayActorsInAgeRange(root, minAge, maxAge);
}

// Function to display movies in a specific release year range
template <>
void AVLTree<Movie>::displayMoviesInRange(AVLNode<Movie>* node, int minYear, int maxYear) {
    if (!node) return;

    int movieYear = node->data->getReleaseYear();

    // 🔥 Ensure correct traversal for all cases
    if (movieYear >= minYear)  // 🔄 Move left to check for earlier years (including minYear)
        displayMoviesInRange(node->left, minYear, maxYear);

    if (movieYear >= minYear && movieYear <= maxYear) {  // ✅ Print movies inside the range
        std::cout << "Movie ID: " << node->data->getId()
                  << ", Title: " << node->data->getTitle()
                  << ", Release Year: " << movieYear << std::endl;
    }

    if (movieYear <= maxYear)  // 🔄 Move right to check for later years (including maxYear)
        displayMoviesInRange(node->right, minYear, maxYear);
}

// Public function for calling from menu
template <>
void AVLTree<Movie>::displayMoviesInRange(int minYear, int maxYear) {
    std::cout << "\nMovies released between " << minYear << " and " << maxYear << " (sorted by year):\n";
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
