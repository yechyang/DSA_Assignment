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

// Time Complexity: O(n) - checking for duplicates takes O(n) in the worst case
// Add a movie to the actor's linked list
void Actor::addMovie(Movie* movie) {
    if (!movie || movies.contains(movie)) return;  // Prevent duplicates
    movies.append(movie);
}


// Returns the linked list of movies associated with the actor
LinkedList<Movie>& Actor::getMovies() {
    return movies;
}

// Updates actor details if new values are provided
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

// Time Complexity: O(n) - Traverses the linked list of movies
void Actor::display() const {
    cout << "Actor ID: " << id << ", Name: " << name << ", Birth Year: " << birthYear << endl;
    cout << "\nMovies:" << endl;
    
    movies.display(displayMovie); // Call linked list display function
}

// Insertion Sort: Sorts movies alphabetically by title
// Time Complexity: O(n^2) - Worst case when the array is in reverse order
// Best case is O(n) if already sorted
// Space Complexity: O(1) - In-place sorting
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

// Converts linked list of movies to an array and sorts them alphabetically
// Time Complexity: O(n log n) - Using Merge Sort
// Space Complexity: O(n) - Allocates array for movies
Movie** Actor::getSortedMovies(int& count) const {
    // Convert LinkedList to an array using the actual `movies` LinkedList instance
    Movie** movieArray = movies.toArray(count);  // Convert LinkedList to array

    if (count == 0) return nullptr;

    // Use Insertion Sort for sorting
    insertionSortMovies(movieArray, count); // O(n^2) worst case, O(n) best case

    return movieArray;
}


// Insertion Sort: Sorts movies in descending order by rating
// Time Complexity: O(n^2) - Worst case when movies are in ascending order
// Best case is O(n) if movies are already sorted in descending order
// Space Complexity: O(1) - In-place sorting (no extra memory used)
void Actor::insertionSortMoviesByRating(Movie** movies, int count) const {
    for (int i = 1; i < count; ++i) {
        Movie* key = movies[i]; // Current movie being inserted into sorted portion
        int j = i - 1;

        // Move elements that have a LOWER rating forward (higher ratings on top)
        while (j >= 0 && movies[j]->getRating() < key->getRating()) {
            movies[j + 1] = movies[j]; // Shift elements forward
            j = j - 1;
        }
        movies[j + 1] = key; // Insert movie at correct position
    }
}

// Converts the actor's linked list of movies to an array and sorts them by rating (descending)
// Time Complexity: O(n^2) using Insertion Sort (Worse Case)
// Space Complexity: O(n) - Creates an array to store movies
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

// Merge Sort for sorting actors by rating (descending order)
// Time Complexity: O(n log n) - Efficient sorting
// Space Complexity: O(n) - Uses extra arrays for merging
void mergeSort(Actor** actors, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(actors, left, mid);
        mergeSort(actors, mid + 1, right);

        merge(actors, left, mid, right);
    }
}

// Recommend actors based on rating, sorted using Merge Sort
// Time Complexity: O(n log n) - Due to Merge Sort
// Space Complexity: O(n) - Uses additional space for sorting
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
