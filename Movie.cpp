#include "Movie.h"
#include "Actor.h"
#include "MovieAVLNode.h"
#include <iostream>
using namespace std;

// Constructor
Movie::Movie(const int& id, const string& title, const string& plot, int releaseYear)
    : id(id), title(title), plot(plot), releaseYear(releaseYear), actorHead(nullptr) {}

// Destructor
Movie::~Movie() {
    ActorNode* current = actorHead;
    while (current) {
        ActorNode* temp = current;
        current = current->next;
        delete temp;
    }
}

// Getter methods
int Movie::getId() const { return id; }
string Movie::getTitle() const { return title; }
string Movie::getPlot() const { return plot; }
int Movie::getReleaseYear() const { return releaseYear; }

// Setter methods
void Movie::setId(const int& id) { this->id = id; }
void Movie::setTitle(const string& title) { this->title = title; }
void Movie::setPlot(const string& plot) { this->plot = plot; }
void Movie::setReleaseYear(int releaseYear) { this->releaseYear = releaseYear; }

// Add an actor to the movie's list
void Movie::addActor(Actor* actor) {
    ActorNode* newNode = new ActorNode(actor);
    newNode->next = actorHead;
    actorHead = newNode;
}


void Movie::updateDetails(const string& newTitle, const string& newPlot, int newReleaseYear) {
    if (!newTitle.empty()) {
        title = newTitle;
    }
    if (!newPlot.empty()) {
        plot = newPlot;
    }
    if (newReleaseYear > 0) {
        releaseYear = newReleaseYear;
    }
    cout << "Movie details updated successfully." << endl;
}


// Display movie details and their actors
void Movie::display() const {
    cout << "Movie ID: " << id << ", \nTitle: " << title
         << ", \nPlot: " << plot << ", \nRelease Year: " << releaseYear << endl;
    cout << "\nActors in this movie:" << endl;

    ActorNode* current = actorHead;
    if (!current) {
        cout << "No actors in this movie." << endl;
        return;
    }

    while (current) {
        // Display both actor ID and name
        cout << " - ID: " << current->actor->getId()
             << ", Name: " << current->actor->getName() << endl;
        current = current->next;
    }
}

// void swap(Actor*& x, Actor*& y) {
//     Actor* temp = x;
//     x = y;
//     y = temp;
// }

// int indexOfLargest(Actor* array[], int n) {
//     int largestIndex = 0;
//     for (int i = 1; i < n; i++) {
//         if (array[i]->getName() > array[largestIndex]->getName()) {
//             largestIndex = i;
//         }
//     }
//     return largestIndex;
// }

// void selectionSort(Actor* array[], int n) {
//     for (int last = n - 1; last >= 1; last--) {
//         int largest = indexOfLargest(array, last + 1);
//         swap(array[largest], array[last]);
//     }
// }

// Actor** Movie::getSortedActors(int& count) const {
//     // Step 1: Count the number of actors
//     count = 0;
//     ActorNode* currentNode = actorHead;
//     while (currentNode != nullptr) {
//         count++;
//         currentNode = currentNode->next;
//     }

//     // Step 2: Allocate an array to store actors
//     Actor** actors = new Actor*[count];
//     currentNode = actorHead;
//     for (int i = 0; i < count; i++) {
//         actors[i] = currentNode->actor;
//         currentNode = currentNode->next;
//     }

//     // Step 3: Sort the actors using selection sort
//     selectionSort(actors, count);

//     // Step 4: Return the sorted array
//     return actors;
// }

void mergeActors(Actor** actors, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Temporary arrays
    Actor** leftArray = new Actor*[n1];
    Actor** rightArray = new Actor*[n2];

    // Copy data to temporary arrays
    for (int i = 0; i < n1; ++i)
        leftArray[i] = actors[left + i];
    for (int j = 0; j < n2; ++j)
        rightArray[j] = actors[mid + 1 + j];

    // Merge the arrays back into actors[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i]->getName() <= rightArray[j]->getName())
            actors[k++] = leftArray[i++];
        else
            actors[k++] = rightArray[j++];
    }

    // Copy remaining elements
    while (i < n1)
        actors[k++] = leftArray[i++];
    while (j < n2)
        actors[k++] = rightArray[j++];

    // Free temporary arrays
    delete[] leftArray;
    delete[] rightArray;
}

void mergeSortActors(Actor** actors, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSortActors(actors, left, mid);
        mergeSortActors(actors, mid + 1, right);

        // Merge the sorted halves
        mergeActors(actors, left, mid, right);
    }
}

Actor** Movie::getSortedActors(int& count) const {
    // Count the number of actors
    count = 0;
    ActorNode* current = actorHead;
    while (current != nullptr) {
        count++;
        current = current->next;
    }

    // Create an array to hold the actors
    Actor** actors = new Actor*[count];
    current = actorHead;
    for (int i = 0; i < count; ++i) {
        actors[i] = current->actor;
        current = current->next;
    }

    // Apply merge sort
    mergeSortActors(actors, 0, count - 1);

    return actors;
}

// AVL Tree utility methods
int Movie::getHeight(MovieAVLNode* node) {
    return node ? node->height : 0;
}

int Movie::getBalance(MovieAVLNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

MovieAVLNode* Movie::rotateLeft(MovieAVLNode* x) {
    MovieAVLNode* y = x->right;
    MovieAVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

MovieAVLNode* Movie::rotateRight(MovieAVLNode* y) {
    MovieAVLNode* x = y->left;
    MovieAVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

MovieAVLNode* Movie::insertIntoAVL(MovieAVLNode* node, Movie* movie) {
    if (!node) {
        return new MovieAVLNode(movie); // Create a new node
    }

    if (movie->getReleaseYear() < node->releaseYear) {
        node->left = insertIntoAVL(node->left, movie);
    } else if (movie->getReleaseYear() > node->releaseYear) {
        node->right = insertIntoAVL(node->right, movie);
    } else {
        // Duplicate year: Add movie to the linked list
        MovieListNode* newNode = new MovieListNode(movie);
        newNode->next = node->movieList;
        node->movieList = newNode;
        return node; // No need to adjust height or balance
    }

    // Update height
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // Check balance and perform rotations if needed
    int balance = getBalance(node);

    if (balance > 1 && movie->getReleaseYear() < node->left->releaseYear) {
        return rotateRight(node);
    }
    if (balance < -1 && movie->getReleaseYear() > node->right->releaseYear) {
        return rotateLeft(node);
    }
    if (balance > 1 && movie->getReleaseYear() > node->left->releaseYear) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && movie->getReleaseYear() < node->right->releaseYear) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void Movie::inOrderTraversal(MovieAVLNode* node) {
    if (node) {
        inOrderTraversal(node->left);
        MovieListNode* current = node->movieList;
        while (current) {
            cout << "ID: " << current->movie->getId()
                 << ", Movie: " << current->movie->getTitle()
                 << ", Plot: " << current->movie->getPlot()
                 << ", Year: " << node->releaseYear << endl;
            current = current->next;
        }
        inOrderTraversal(node->right);
    }
}

void Movie::freeAVLTree(MovieAVLNode* node) {
    if (node) {
        freeAVLTree(node->left);
        freeAVLTree(node->right);
        delete node;
    }
}

// Sort movies using AVL tree
void Movie::sortMoviesByReleaseYear(Movie** movies, int count) {
    MovieAVLNode* root = nullptr;

    for (int i = 0; i < count; ++i) {
        root = insertIntoAVL(root, movies[i]);
    }

    cout << "Movies sorted by release year:" << endl;
    inOrderTraversal(root);

    freeAVLTree(root);
}

ActorNode* Movie::getActorHead() const {
    return actorHead;
}