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


// void swap(Movie*& x, Movie*& y) {
//     Movie* temp = x;
//     x = y;
//     y = temp;
// }

// int indexOfLargest(Movie* array[], int n) {
//     int largestIndex = 0;
//     for (int i = 1; i < n; i++) {
//         if (array[i]->getTitle() > array[largestIndex]->getTitle()) {
//             largestIndex = i;
//         }
//     }
//     return largestIndex;
// }

// void selectionSort(Movie* array[], int n) {
//     for (int last = n - 1; last >= 1; last--) {
//         int largest = indexOfLargest(array, last + 1);
//         swap(array[largest], array[last]);
//     }
// }

// Movie** Actor::getSortedMovies(int& count) const {
//     // Count the number of movies
//     count = 0;
//     MovieNode* currentNode = movieHead;
//     while (currentNode != nullptr) {
//         count++;
//         currentNode = currentNode->next;
//     }

//     // Allocate an array to store movies
//     Movie** movies = new Movie*[count];
//     currentNode = movieHead;
//     for (int i = 0; i < count; i++) {
//         movies[i] = currentNode->movie;
//         currentNode = currentNode->next;
//     }

//     // Sort the movies
//     selectionSort(movies, count);

//     return movies;
// }

void mergeMovies(Movie** movies, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Temporary arrays
    Movie** leftArray = new Movie*[n1];
    Movie** rightArray = new Movie*[n2];

    // Copy data to temporary arrays
    for (int i = 0; i < n1; ++i)
        leftArray[i] = movies[left + i];
    for (int j = 0; j < n2; ++j)
        rightArray[j] = movies[mid + 1 + j];

    // Merge the arrays back into movies[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i]->getTitle() <= rightArray[j]->getTitle())
            movies[k++] = leftArray[i++];
        else
            movies[k++] = rightArray[j++];
    }

    // Copy remaining elements
    while (i < n1)
        movies[k++] = leftArray[i++];
    while (j < n2)
        movies[k++] = rightArray[j++];

    // Free temporary arrays
    delete[] leftArray;
    delete[] rightArray;
}

void mergeSortMovies(Movie** movies, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSortMovies(movies, left, mid);
        mergeSortMovies(movies, mid + 1, right);

        // Merge the sorted halves
        mergeMovies(movies, left, mid, right);
    }
}

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

    // Apply merge sort
    mergeSortMovies(movies, 0, count - 1);

    return movies;
}

void Actor::merge(Actor** actors, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Temporary arrays
    Actor** leftArray = new Actor*[n1];
    Actor** rightArray = new Actor*[n2];

    // Copy data to temporary arrays
    for (int i = 0; i < n1; ++i) {
        leftArray[i] = actors[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        rightArray[j] = actors[mid + 1 + j];
    }

    // Merge the arrays back into actors[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        int ageLeft = 2025 - leftArray[i]->getBirthYear();
        int ageRight = 2025 - rightArray[j]->getBirthYear();

        if (ageLeft <= ageRight) {
            actors[k++] = leftArray[i++];
        } else {
            actors[k++] = rightArray[j++];
        }
    }

    // Copy any remaining elements
    while (i < n1) {
        actors[k++] = leftArray[i++];
    }
    while (j < n2) {
        actors[k++] = rightArray[j++];
    }

    // Free memory
    delete[] leftArray;
    delete[] rightArray;
}

// Merge sort function
void Actor::mergeSort(Actor** actors, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(actors, left, mid);
        mergeSort(actors, mid + 1, right);

        // Merge the sorted halves
        merge(actors, left, mid, right);
    }
}

Actor** Actor::filterAndSortByAge(Actor** allActors, int totalActors, int minAge, int maxAge, int& filteredCount) {
    filteredCount = 0;

    // Temporary array for filtered actors
    Actor** filteredActors = new Actor*[totalActors];

    // Filter actors by age range
    for (int i = 0; i < totalActors; ++i) {
        int age = 2025 - allActors[i]->getBirthYear();
        if (age >= minAge && age <= maxAge) {
            filteredActors[filteredCount++] = allActors[i];
        }
    }

    // Sort the filtered actors by age
    mergeSort(filteredActors, 0, filteredCount - 1);

    return filteredActors; // Return the filtered and sorted array
}

void Actor::displayKnownActors() const {
    const int maxActors = 1000; // Adjust as needed
    Actor* knownActors[maxActors];
    int knownCount = 0;

    Dictionary<bool> processedActors(100); // Use Dictionary to track processed actors

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
            }
            actorNode = actorNode->next;
        }
        movieNode = movieNode->next;
    }

    // Second-level connections
    for (int i = 0; i < knownCount; ++i) {
        Actor* level1Actor = knownActors[i];
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

Actor** Actor::sortActorsByRating(Actor** actors, int count) const {
    // Perform Bubble Sort (Descending Order by Rating)
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (actors[j]->getRating() < actors[j + 1]->getRating()) {
                // Swap
                Actor* temp = actors[j];
                actors[j] = actors[j + 1];
                actors[j + 1] = temp;
            }
        }
    }
    return actors; // Return the sorted array
}

