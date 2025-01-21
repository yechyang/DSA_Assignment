#include "Actor.h"
#include "Movie.h"
#include <iostream>
using namespace std;

// Constructor
Actor::Actor(const int& id, const string& name, int birthYear)
    : id(id), name(name), birthYear(birthYear), movieHead(nullptr) {}

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

// Setter methods
void Actor::setId(const int& id) { this->id = id; }
void Actor::setName(const string& name) { this->name = name; }
void Actor::setBirthYear(int birthYear) { this->birthYear = birthYear; }

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

// Movie** Actor::getSortedMovies(int& count) const {
//     // Step 1: Count the number of movies
//     count = 0;
//     MovieNode* currentNode = movieHead;
//     while (currentNode != nullptr) {
//         count++;
//         currentNode = currentNode->next;
//     }

//     // Step 2: Allocate an array to store movies
//     Movie** movies = new Movie*[count];
//     currentNode = movieHead;
//     for (int i = 0; i < count; i++) {
//         movies[i] = currentNode->movie;
//         currentNode = currentNode->next;
//     }

//     // Step 3: Sort the movies using selection sort
//     for (int i = 0; i < count - 1; i++) {
//         int minIndex = i;
//         for (int j = i + 1; j < count; j++) {
//             if (movies[j]->getTitle() < movies[minIndex]->getTitle()) {
//                 minIndex = j;
//             }
//         }
//         // Swap the smallest movie with the current position
//         if (minIndex != i) {
//             Movie* temp = movies[i];
//             movies[i] = movies[minIndex];
//             movies[minIndex] = temp;
//         }
//     }

//     // Step 4: Return the sorted array
//     return movies;
// }


void swap(Movie*& x, Movie*& y) {
    Movie* temp = x;
    x = y;
    y = temp;
}

int indexOfLargest(Movie* array[], int n) {
    int largestIndex = 0;
    for (int i = 1; i < n; i++) {
        if (array[i]->getTitle() > array[largestIndex]->getTitle()) {
            largestIndex = i;
        }
    }
    return largestIndex;
}

void selectionSort(Movie* array[], int n) {
    for (int last = n - 1; last >= 1; last--) {
        int largest = indexOfLargest(array, last + 1);
        swap(array[largest], array[last]);
    }
}

Movie** Actor::getSortedMovies(int& count) const {
    // Count the number of movies
    count = 0;
    MovieNode* currentNode = movieHead;
    while (currentNode != nullptr) {
        count++;
        currentNode = currentNode->next;
    }

    // Allocate an array to store movies
    Movie** movies = new Movie*[count];
    currentNode = movieHead;
    for (int i = 0; i < count; i++) {
        movies[i] = currentNode->movie;
        currentNode = currentNode->next;
    }

    // Sort the movies
    selectionSort(movies, count);

    return movies;
}