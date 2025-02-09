#include "Actor.h"
#include "Movie.h"
#include "Dictionary.h"
#include <iostream>
using namespace std;

// Constructor
Actor::Actor(const int& id, const string& name, int birthYear)
    : id(id), name(name), birthYear(birthYear), rating(0.0f) {}

// Destructor
Actor::~Actor() {
    movies.clear();  // Use LinkedList clear function
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
    if (!movie || movies.contains(movie)) return;  // Prevent duplicates
    movies.append(movie);
}


// Get movies list
LinkedList<Movie>& Actor::getMovies() {
    return movies;
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
void displayMovie(const Movie& movie) {
    movie.display();  // Call Movie's display function
}

void Actor::display() const {
    cout << "Actor ID: " << id << ", Name: " << name << ", Birth Year: " << birthYear << endl;
    cout << "\nMovies:" << endl;
    
    movies.display(displayMovie);
}

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

Movie** Actor::getSortedMovies(int& count) const {
    // Convert LinkedList to an array using the actual `movies` LinkedList instance
    Movie** movieArray = movies.toArray(count);  // Call `toArray()` correctly

    if (count == 0) return nullptr;

    // Use Insertion Sort for sorting
    insertionSortMovies(movieArray, count); // O(n^2) worst case, O(n) best case

    return movieArray;
}

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
    ListNode<Movie>* movieNode = movies.getHead(); // ✅ Use LinkedList<Movie> instead of movieHead
    while (movieNode) {
        Movie* movie = movieNode->data;
        ListNode<Actor>* actorNode = movie->getActors().getHead(); // ✅ Get actors from LinkedList<Actor>
        while (actorNode) {
            Actor* currentActor = actorNode->data;
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

        ListNode<Movie>* level1MovieNode = level1Actor->getMovies().getHead(); // ✅ Get movies from LinkedList<Movie>
        while (level1MovieNode) {
            Movie* movie = level1MovieNode->data;
            ListNode<Actor>* actorNode = movie->getActors().getHead();
            while (actorNode) {
                Actor* currentActor = actorNode->data;
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




// Insertion Sort for Actors by Rating
void Actor::insertionSortMoviesByRating(Movie** movies, int count) const {
    for (int i = 1; i < count; ++i) {
        Movie* key = movies[i];
        int j = i - 1;

        // Move elements that have a LOWER rating forward (higher ratings on top)
        while (j >= 0 && movies[j]->getRating() < key->getRating()) {
            movies[j + 1] = movies[j];
            j = j - 1;
        }
        movies[j + 1] = key;
    }
}

Movie** Actor::sortMoviesByRating(int& count) const {
    Movie** movieArray = movies.toArray(count);
    if (count == 0) return nullptr;

    // Sort by rating (descending order)
    insertionSortMoviesByRating(movieArray, count);

    return movieArray;
}


// Helper function to merge two sorted halves
void merge(Actor** actors, int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    Actor** leftArr = new Actor*[leftSize];
    Actor** rightArr = new Actor*[rightSize];

    for (int i = 0; i < leftSize; i++)
        leftArr[i] = actors[left + i];

    for (int i = 0; i < rightSize; i++)
        rightArr[i] = actors[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < leftSize && j < rightSize) {
        if (leftArr[i]->getRating() >= rightArr[j]->getRating()) {
            actors[k] = leftArr[i];
            i++;
        } else {
            actors[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < leftSize) {
        actors[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < rightSize) {
        actors[k] = rightArr[j];
        j++;
        k++;
    }

    delete[] leftArr;
    delete[] rightArr;
}

// Merge Sort function
void mergeSort(Actor** actors, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(actors, left, mid);
        mergeSort(actors, mid + 1, right);

        merge(actors, left, mid, right);
    }
}

// Updated recommendActorsByRating function using Merge Sort
void Actor::recommendActorsByRating(Actor** actors, int totalActors, float minRating) const {
    // Sort actors by rating in descending order using Merge Sort
    mergeSort(actors, 0, totalActors - 1);

    cout << "\nActors with rating higher than " << minRating << " (Sorted by Rating):\n";
    bool found = false;

    for (int i = 0; i < totalActors; ++i) {
        if (actors[i]->getRating() >= minRating) {
            cout << "- " << actors[i]->getName() << " (Rating: " << actors[i]->getRating() << "/10)\n";

            ListNode<Movie>* movieNode = actors[i]->getMovies().getHead();
            if (!movieNode) {
                cout << "  No movies found for this actor.\n" << endl;
            } else {
                cout << "  Movies:\n";
                while (movieNode) {
                    cout << "    * " << movieNode->data->getTitle()
                         << " (Year: " << movieNode->data->getReleaseYear()
                         << " Rating: " << movieNode->data->getRating() << "/10)\n";
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
