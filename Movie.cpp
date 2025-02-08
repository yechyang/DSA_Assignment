#include "Movie.h"
#include "Actor.h"
#include "MovieAVLNode.h"
#include <iostream>
using namespace std;

// Constructor
Movie::Movie(const int& id, const string& title, const string& plot, int releaseYear)
    : id(id), title(title), plot(plot), releaseYear(releaseYear), actorHead(nullptr), rating(0.0f) {}

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
float Movie::getRating() const { return rating; }


// Setter methods
void Movie::setId(const int& id) { this->id = id; }
void Movie::setTitle(const string& title) { this->title = title; }
void Movie::setPlot(const string& plot) { this->plot = plot; }
void Movie::setReleaseYear(int releaseYear) { this->releaseYear = releaseYear; }
// Time Complexity: O(1)
void Movie::setRating(float newRating) {
    if (newRating >= 0.0f && newRating <= 10.0f) {
        rating = newRating;
    } else {
        cerr << "Invalid rating. Please enter a value between 0.0 and 10.0." << endl;
    }
}

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


// void mergeActors(Actor** actors, int left, int mid, int right) {
//     int n1 = mid - left + 1;
//     int n2 = right - mid;

//     // Temporary arrays
//     Actor** leftArray = new Actor*[n1];
//     Actor** rightArray = new Actor*[n2];

//     // Copy data to temporary arrays
//     for (int i = 0; i < n1; ++i)
//         leftArray[i] = actors[left + i];
//     for (int j = 0; j < n2; ++j)
//         rightArray[j] = actors[mid + 1 + j];

//     // Merge the arrays back into actors[left..right]
//     int i = 0, j = 0, k = left;
//     while (i < n1 && j < n2) {
//         if (leftArray[i]->getName() <= rightArray[j]->getName())
//             actors[k++] = leftArray[i++];
//         else
//             actors[k++] = rightArray[j++];
//     }

//     // Copy remaining elements
//     while (i < n1)
//         actors[k++] = leftArray[i++];
//     while (j < n2)
//         actors[k++] = rightArray[j++];

//     // Free temporary arrays
//     delete[] leftArray;
//     delete[] rightArray;
// }

// void mergeSortActors(Actor** actors, int left, int right) {
//     if (left < right) {
//         int mid = left + (right - left) / 2;

//         // Sort first and second halves
//         mergeSortActors(actors, left, mid);
//         mergeSortActors(actors, mid + 1, right);

//         // Merge the sorted halves
//         mergeActors(actors, left, mid, right);
//     }
// }

// // Time Complexity: O(n log n)
// // Space Complexity: O(n)
// Actor** Movie::getSortedActors(int& count) const {
//     // Count the number of actors
//     count = 0;
//     ActorNode* current = actorHead;
//     while (current != nullptr) {
//         count++;
//         current = current->next;
//     }

//     // Create an array to hold the actors
//     Actor** actors = new Actor*[count];
//     current = actorHead;
//     for (int i = 0; i < count; ++i) {
//         actors[i] = current->actor;
//         current = current->next;
//     }

//     // Apply merge sort
//     mergeSortActors(actors, 0, count - 1); // Time Complexity: O(n log n)

//     return actors;
// }

// Insertion Sort for Sorting Actors by Name
void insertionSortActors(Actor** actors, int count) {
    for (int i = 1; i < count; ++i) {
        Actor* key = actors[i];
        int j = i - 1;

        // Move elements that are greater than `key` forward
        while (j >= 0 && actors[j]->getName() > key->getName()) {
            actors[j + 1] = actors[j];
            j--;
        }
        actors[j + 1] = key;
    }
}

// **Updated Sorting Function Using Insertion Sort**
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

    // **Use Insertion Sort (Better for Small Data Sets)**
    insertionSortActors(actors, count); // O(n^2) worst case, O(n) best case

    return actors;
}

ActorNode* Movie::getActorHead() const {
    return actorHead;
}

//
// Change to Merge Sort
//
Movie** Movie::sortMoviesByRating(Movie** movies, int count) const {
    // Perform Bubble Sort (Descending Order by Rating)
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (movies[j]->getRating() < movies[j + 1]->getRating()) {
                // Swap movies
                Movie* temp = movies[j];
                movies[j] = movies[j + 1];
                movies[j + 1] = temp;
            }
        }
    }
    return movies; // Return the sorted array
}

// Insertion Sort for Movies by Rating
void Movie::insertionSortMoviesByRating(Movie** movies, int count) const {
    for (int i = 1; i < count; ++i) {
        Movie* key = movies[i];
        int j = i - 1;

        while (j >= 0 && movies[j]->getRating() < key->getRating()) {
            movies[j + 1] = movies[j];
            j = j - 1;
        }
        movies[j + 1] = key;
    }
}

void Movie::recommendMoviesByRating(Movie** movies, int totalMovies, float minRating) const {
    cout << "\nMovies with rating higher than " << minRating << ":\n";
    int count = 0;

    for (int i = 0; i < totalMovies; ++i) {
        if (movies[i]->getRating() >= minRating) {
            count++;
        }
    }

    if (count == 0) {
        cout << "No movies found with the specified rating." << endl;
        return;
    }

    Movie** filteredMovies = new Movie*[count];
    int index = 0;
    for (int i = 0; i < totalMovies; ++i) {
        if (movies[i]->getRating() >= minRating) {
            filteredMovies[index++] = movies[i];
        }
    }

    insertionSortMoviesByRating(filteredMovies, count);

    for (int i = 0; i < count; ++i) {
        cout << "- " << filteredMovies[i]->getTitle() << " Rating: " << filteredMovies[i]->getRating() <<"/10\n";
    }

    delete[] filteredMovies;
}

void Movie::recommendMoviesByYear(Movie** movies, int totalMovies, int year) const {
    cout << "\nMovies from the year " << year << ":\n";
    int yearCount = 0;

    // First, count movies from the specified year that also have a rating > 0
    for (int i = 0; i < totalMovies; ++i) {
        if (movies[i]->getReleaseYear() == year && movies[i]->getRating() > 0.0f) {
            yearCount++;
        }
    }

    if (yearCount == 0) {
        cout << "No rated movies found from the specified year." << endl;
        return;
    }

    // Store movies from the specified year that have a rating > 0
    Movie** yearMovies = new Movie*[yearCount];
    int index = 0;
    for (int i = 0; i < totalMovies; ++i) {
        if (movies[i]->getReleaseYear() == year && movies[i]->getRating() > 0.0f) {
            yearMovies[index++] = movies[i];
        }
    }

    // Sort using insertion sort
    insertionSortMoviesByRating(yearMovies, yearCount);

    // Display sorted movies
    for (int i = 0; i < yearCount; ++i) {
        cout << "- " << yearMovies[i]->getTitle() << " Rating: " << yearMovies[i]->getRating() <<"/10\n";
    }

    delete[] yearMovies;
}
