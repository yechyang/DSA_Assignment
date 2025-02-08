#include "Actor.h"
#include "Movie.h"
#include "Dictionary.h"
#include <iostream>
using namespace std;

// Constructor
Actor::Actor(const int& id, const string& name, int birthYear)
    : id(id), name(name), birthYear(birthYear), movieHead(nullptr), rating(0.0f) {}

// Destructor
Actor::~Actor() {
    MovieNode* current = movieHead;
    while (current) {
        MovieNode* temp = current;
        current = current->next;
        delete temp;
    }
}

// Getter methods
int Actor::getId() const { return id; }
string Actor::getName() const { return name; }
int Actor::getBirthYear() const { return birthYear; }
float Actor::getRating() const { return rating; }

// Setter methods
void Actor::setId(const int& id) { this->id = id; }
void Actor::setName(const string& name) { this->name = name; }
void Actor::setBirthYear(int birthYear) { this->birthYear = birthYear; }
// Time Complexity: O(1)
void Actor::setRating(float newRating) {
    if (newRating >= 0.0f && newRating <= 10.0f) {
        rating = newRating;
    } else {
        cerr << "Invalid rating. Please enter a value between 0.0 and 10.0." << endl;
    }
}

// Add a movie to the actor's list
void Actor::addMovie(Movie* movie) {
    MovieNode* newNode = new MovieNode(movie);
    newNode->next = movieHead;
    movieHead = newNode;
}

// New method to return the head of the movie list
const MovieNode* Actor::getMovies() const {
    return movieHead;
}

void Actor::updateDetails(const string& newName, int newBirthYear) {
    if (!newName.empty()) {
        name = newName;
    }
    if (newBirthYear > 0) {
        birthYear = newBirthYear;
    }
    cout << "Actor details updated successfully." << endl;
}

// Display actor details and their movies
void Actor::display() const {
    cout << "Actor ID: " << id << ", \nName: " << name << ", \nBirth Year: " << birthYear << endl;
    cout << "\nMovies:" << endl;

    MovieNode* current = movieHead;
    while (current) {
        current->movie->display();
        current = current->next;
    }
}

// // Time Complexity: O(n log n)
// // Space Complexity: O(n)
// void mergeMovies(Movie** movies, int left, int mid, int right) {
//     int n1 = mid - left + 1;
//     int n2 = right - mid;

//     // Temporary arrays
//     Movie** leftArray = new Movie*[n1];
//     Movie** rightArray = new Movie*[n2];

//     // Copy data to temporary arrays
//     for (int i = 0; i < n1; ++i)
//         leftArray[i] = movies[left + i];
//     for (int j = 0; j < n2; ++j)
//         rightArray[j] = movies[mid + 1 + j];

//     // Merge the arrays back into movies[left..right]
//     int i = 0, j = 0, k = left;
//     while (i < n1 && j < n2) {
//         if (leftArray[i]->getTitle() <= rightArray[j]->getTitle())
//             movies[k++] = leftArray[i++];
//         else
//             movies[k++] = rightArray[j++];
//     }

//     // Copy remaining elements
//     while (i < n1)
//         movies[k++] = leftArray[i++];
//     while (j < n2)
//         movies[k++] = rightArray[j++];

//     // Free temporary arrays
//     delete[] leftArray;
//     delete[] rightArray;
// }

// void mergeSortMovies(Movie** movies, int left, int right) {
//     if (left < right) {
//         int mid = left + (right - left) / 2;

//         // Sort first and second halves
//         mergeSortMovies(movies, left, mid);
//         mergeSortMovies(movies, mid + 1, right);

//         // Merge the sorted halves
//         mergeMovies(movies, left, mid, right);
//     }
// }

// // Time Complexity: O(n log n)
// // Space Complexity: O(n)
// Movie** Actor::getSortedMovies(int& count) const {
//     // Count the number of movies
//     count = 0;
//     MovieNode* current = movieHead;
//     while (current != nullptr) {
//         count++;
//         current = current->next;
//     }

//     // Create an array to hold the movies
//     Movie** movies = new Movie*[count];
//     current = movieHead;
//     for (int i = 0; i < count; ++i) {
//         movies[i] = current->movie;
//         current = current->next;
//     }

//     // Apply merge sort
//     mergeSortMovies(movies, 0, count - 1); // Time Complexity: O(n log n)

//     return movies;
// }


// Insertion Sort for Sorting Movies by Title
void insertionSortMovies(Movie** movies, int count) {
    for (int i = 1; i < count; ++i) {
        Movie* key = movies[i];
        int j = i - 1;

        // Move elements that are greater than `key` forward
        while (j >= 0 && movies[j]->getTitle() > key->getTitle()) {
            movies[j + 1] = movies[j];
            j--;
        }
        movies[j + 1] = key;
    }
}

// **Updated Sorting Function Using Insertion Sort**
Movie** Actor::getSortedMovies(int& count) const {
    // Count the number of movies
    count = 0;
    MovieNode* current = movieHead;
    while (current != nullptr) {
        count++;
        current = current->next;
    }

    // Create an array to hold the movies
    Movie** movies = new Movie*[count];
    current = movieHead;
    for (int i = 0; i < count; ++i) {
        movies[i] = current->movie;
        current = current->next;
    }

    // **Use Insertion Sort (Better for Small Data Sets)**
    insertionSortMovies(movies, count); // O(n^2) worst case, O(n) best case

    return movies;
}

// void Actor::merge(Actor** actors, int left, int mid, int right) {
//     int n1 = mid - left + 1;
//     int n2 = right - mid;

//     // Temporary arrays
//     Actor** leftArray = new Actor*[n1];
//     Actor** rightArray = new Actor*[n2];

//     // Copy data to temporary arrays
//     for (int i = 0; i < n1; ++i) {
//         leftArray[i] = actors[left + i];
//     }
//     for (int j = 0; j < n2; ++j) {
//         rightArray[j] = actors[mid + 1 + j];
//     }

//     // Merge the arrays back into actors[left..right]
//     int i = 0, j = 0, k = left;
//     while (i < n1 && j < n2) {
//         int ageLeft = 2025 - leftArray[i]->getBirthYear();
//         int ageRight = 2025 - rightArray[j]->getBirthYear();

//         if (ageLeft <= ageRight) {
//             actors[k++] = leftArray[i++];
//         } else {
//             actors[k++] = rightArray[j++];
//         }
//     }

//     // Copy any remaining elements
//     while (i < n1) {
//         actors[k++] = leftArray[i++];
//     }
//     while (j < n2) {
//         actors[k++] = rightArray[j++];
//     }

//     // Free memory
//     delete[] leftArray;
//     delete[] rightArray;
// }

// // Merge sort function
// void Actor::mergeSort(Actor** actors, int left, int right) {
//     if (left < right) {
//         int mid = left + (right - left) / 2;

//         // Sort first and second halves
//         mergeSort(actors, left, mid);
//         mergeSort(actors, mid + 1, right);

//         // Merge the sorted halves
//         merge(actors, left, mid, right);
//     }
// }

// // Time Complexity: O(n log n)
// // Storage Complexity: O(n)
// Actor** Actor::filterAndSortByAge(Actor** allActors, int totalActors, int minAge, int maxAge, int& filteredCount) {
//     filteredCount = 0;

//     // Temporary array for filtered actors
//     Actor** filteredActors = new Actor*[totalActors]; // Space Complexity: O(n)

//     // Filter actors by age range
//     for (int i = 0; i < totalActors; ++i) {
//         int age = 2025 - allActors[i]->getBirthYear();
//         if (age >= minAge && age <= maxAge) {
//             filteredActors[filteredCount++] = allActors[i];
//         }
//     }

//     // Sort the filtered actors by age
//     mergeSort(filteredActors, 0, filteredCount - 1); // Time Complexity: O(n log n)

//     return filteredActors; // Return the filtered and sorted array
// }
// #include "AVLTree.h"

// // Helper function to get actor age as the sorting key
// int getActorAge(Actor* actor) {
//     return (2025 - actor->getBirthYear()) * 1000000 + actor->getId();  // Unique key
// }

// // Function to filter and sort actors using AVL Tree
// void Actor::sortActorsByAge(Actor** allActors, int totalActors, int minAge, int maxAge, int& filteredCount) {
//     filteredCount = 0;

//     int currentYear = 2025;
//     int minYear = currentYear - maxAge;
//     int maxYear = currentYear - minAge;

//     // Create an AVL Tree for sorting
//     AVLTree<Actor> actorTree(getActorAge);

//     // Insert only actors that match the age range into the AVL Tree
//     for (int i = 0; i < totalActors; ++i) {
//         int age = currentYear - allActors[i]->getBirthYear();
//         if (age >= minAge && age <= maxAge) {
//             actorTree.insert(allActors[i]);
//             filteredCount++;
//         }
//     }

//     // If no actors match the age range, exit early
//     if (filteredCount == 0) {
//         cout << "No actors found in the specified age range." << endl;
//         return;
//     }

//     // Allocate memory for the sorted actors
//     Actor** sortedActors = new Actor*[filteredCount];

//     // Retrieve sorted actors from the AVL Tree
//     int index = 0;
//     actorTree.inOrderFill(sortedActors, index);

//     // Display the sorted actors
//     cout << "\nActors with age between " << minAge << " and " << maxAge << " (sorted by age):" << endl;
//     for (int i = 0; i < filteredCount; ++i) {
//         int age = currentYear - sortedActors[i]->getBirthYear();
//         cout << "Actor ID: " << sortedActors[i]->getId()
//              << ", Name: " << sortedActors[i]->getName()
//              << ", Age: " << age << endl;
//     }

//     delete[] sortedActors;  // Free memory
// }

//
// Change to ADT Queue
//
void Actor::displayKnownActors() const {
    const int maxActors = 1000; // Adjust as needed
    Actor* knownActors[maxActors];
    int knownCount = 0;

    Dictionary<bool> processedActors; // Track processed actors
    Dictionary<bool> level1Actors; // Track level-1 actors separately

    // First-level connections
    const MovieNode* movieNode = movieHead;
    while (movieNode) {
        Movie* movie = movieNode->movie;
        const ActorNode* actorNode = movie->getActorHead();
        while (actorNode) {
            Actor* currentActor = actorNode->actor;
            if (currentActor != this && !processedActors.search(currentActor->getId())) {
                knownActors[knownCount++] = currentActor;
                processedActors.insert(currentActor->getId(), true);
                level1Actors.insert(currentActor->getId(), true); // Mark as level-1
            }
            actorNode = actorNode->next;
        }
        movieNode = movieNode->next;
    }

    // Second-level connections (only for level-1 actors)
    for (int i = 0; i < knownCount; ++i) {
        Actor* level1Actor = knownActors[i];
        if (!level1Actors.search(level1Actor->getId())) continue; // Ensure only level-1 actors expand

        const MovieNode* level1MovieNode = level1Actor->getMovies();
        while (level1MovieNode) {
            Movie* movie = level1MovieNode->movie;
            const ActorNode* actorNode = movie->getActorHead();
            while (actorNode) {
                Actor* currentActor = actorNode->actor;
                if (currentActor != this && !processedActors.search(currentActor->getId())) {
                    knownActors[knownCount++] = currentActor;
                    processedActors.insert(currentActor->getId(), true);
                }
            actorNode = actorNode->next;
            }
            level1MovieNode = level1MovieNode->next;
        }
    }

    // Display known actors
    cout << "Actors known by " << name << ":" << endl;
    for (int i = 0; i < knownCount; ++i) {
        cout << "- ID: " << knownActors[i]->getId()
             << ", Name: " << knownActors[i]->getName() << endl;
    }
}

//
// Change to Merge Sort
//
// Merge function for sorting actors by rating
void Actor::mergeByRating(Actor** actors, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Temporary arrays
    Actor** leftArray = new Actor*[n1];
    Actor** rightArray = new Actor*[n2];

    // Copy data to temp arrays
    for (int i = 0; i < n1; ++i) leftArray[i] = actors[left + i];
    for (int j = 0; j < n2; ++j) rightArray[j] = actors[mid + 1 + j];

    int i = 0, j = 0, k = left;

    // Merge the arrays by rating in **descending** order
    while (i < n1 && j < n2) {
        if (leftArray[i]->getRating() >= rightArray[j]->getRating()) {
            actors[k++] = leftArray[i++];
        } else {
            actors[k++] = rightArray[j++];
        }
    }

    // Copy remaining elements
    while (i < n1) actors[k++] = leftArray[i++];
    while (j < n2) actors[k++] = rightArray[j++];

    // Free memory
    delete[] leftArray;
    delete[] rightArray;
}

// Merge Sort function for sorting actors by rating
void Actor::mergeSortByRating(Actor** actors, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort both halves
        mergeSortByRating(actors, left, mid);
        mergeSortByRating(actors, mid + 1, right);

        // Merge the sorted halves
        mergeByRating(actors, left, mid, right);
    }
}

// **Updated Sorting Function (Using Merge Sort)**
Actor** Actor::sortActorsByRating(Actor** actors, int count) const {
    if (count > 1) {
        mergeSortByRating(actors, 0, count - 1);
    }
    return actors; // Return sorted array
}

void Actor::recommendActorsByRating(Actor** actors, int totalActors, float minRating) const {
    cout << "\nActors with rating higher than " << minRating << ":\n";
    bool found = false;

    for (int i = 0; i < totalActors; ++i) {
        if (actors[i]->getRating() >= minRating) {
            cout << "- " << actors[i]->getName() << " (Rating: " << actors[i]->getRating() << "/10)\n";
            
            // Display movies the actor is in
            const MovieNode* movieNode = actors[i]->getMovies();
            if (!movieNode) {
                cout << "  No movies found for this actor.\n";
            } else {
                cout << "  Movies:\n";
                while (movieNode) {
                    cout << "    * " << movieNode->movie->getTitle() << " (Year: " << movieNode->movie->getReleaseYear() << " Rating: " << movieNode->movie->getRating() <<"/10)\n";
                    movieNode = movieNode->next;
                }
                cout << endl;
            }
            found = true;
        }
    }

    if (!found) {
        cout << "No actors found with the specified rating.\n";
    }
}