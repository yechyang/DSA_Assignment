#include "Movie.h"
#include "Actor.h"
#include <iostream>
using namespace std;

// Constructor
Movie::Movie(const int& id, const string& title, const string& plot, int releaseYear)
    : id(id), title(title), plot(plot), releaseYear(releaseYear), rating(0.0f) {}

// Destructor
Movie::~Movie() {
    actors.clear();  // clears all linked actors
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

// **Adds an actor to the movie's list**  
// Ensures no duplicate actors are added.  
// Time Complexity: O(N) (Since `contains()` checks if the actor already exists)  
// Space Complexity: O(1)  
void Movie::addActor(Actor* actor) {
    if (!actor || actors.contains(actor)) return;  // Prevent duplicates
    actors.append(actor);
}

// **Updates movie details (title, plot, release year)**  
// Only updates non-empty values and valid years.  
// Time Complexity: O(1)  
// Space Complexity: O(1)  
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


// Calls a function pointer to print actors.  
// Time Complexity: O(N) (where N is the number of actors in the movie)  
// Space Complexity: O(1)  
void Movie::display() const {
    cout << "Movie ID: " << id << ", \nTitle: " << title
         << ", \nPlot: " << plot << ", \nRelease Year: " << releaseYear << endl;

    cout << "\nActors in this movie:" << endl;
    actors.display(Movie::displayActorInfo);  // Use function pointer
}

// **Static function to display actor information**  
// Used for displaying linked actors.  
// Time Complexity: O(1)  
// Space Complexity: O(1)  
void Movie::displayActorInfo(const Actor& actor) {
    cout << " - ID: " << actor.getId() << ", Name: " << actor.getName() << endl;
}


// **Insertion Sort for Sorting Actors by Name**
// Sorts actors alphabetically using insertion sort.
// Time Complexity: O(N^2) (Worst case), O(N) (Best case if already sorted)
// Space Complexity: O(1)
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

// **Returns actors sorted alphabetically**
// Uses insertion sort (good for small datasets).
// Time Complexity: O(N^2) worst case, O(N) best case
// Space Complexity: O(N) (stores sorted array)
Actor** Movie::getSortedActors(int& count) const {
    Actor** actorArray = actors.toArray(count);
    if (count == 0) return nullptr;

    // **Use Insertion Sort (Better for Small Data Sets)**
    insertionSortActors(actorArray, count); // O(n^2) worst case, O(n) best case

    return actorArray;
}

// **Insertion Sort for Sorting Actors by Rating**
// Time Complexity: O(N^2) (Worst case), O(N) (Best case)
// Space Complexity: O(1)
void Movie::insertionSortActorsByRating(Actor** actors, int count) const {
    for (int i = 1; i < count; ++i) {
        Actor* key = actors[i];
        int j = i - 1;

        // Move elements that have a LOWER rating forward (higher ratings on top)
        while (j >= 0 && actors[j]->getRating() < key->getRating()) {
            actors[j + 1] = actors[j];
            j = j - 1;
        }
        actors[j + 1] = key;
    }
}


// **Returns actors sorted by rating (Descending Order)**
// Time Complexity: O(N^2) worst case, O(N) best case
// Space Complexity: O(N)
Actor** Movie::sortActorsByRating(int& count) const {
    Actor** actorArray = actors.toArray(count);
    if (count == 0) return nullptr;

    // Sort by rating (descending order)
    insertionSortActorsByRating(actorArray, count);

    return actorArray;
}


// **Merge Sort for Sorting Movies by Rating (Descending)**
// Time Complexity: O(N log N)
// Space Complexity: O(N)
void mergeMoviesByRating(Movie** movies, int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    // Temporary arrays
    Movie** leftArr = new Movie*[leftSize];
    Movie** rightArr = new Movie*[rightSize];

    // Copy data to temp arrays
    for (int i = 0; i < leftSize; i++) 
        leftArr[i] = movies[left + i];

    for (int i = 0; i < rightSize; i++) 
        rightArr[i] = movies[mid + 1 + i];

    // Merge the temp arrays back into movies[]
    int i = 0, j = 0, k = left;
    while (i < leftSize && j < rightSize) {
        if (leftArr[i]->getRating() >= rightArr[j]->getRating()) {
            movies[k] = leftArr[i];
            i++;
        } else {
            movies[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of leftArr[]
    while (i < leftSize) {
        movies[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy remaining elements of rightArr[]
    while (j < rightSize) {
        movies[k] = rightArr[j];
        j++;
        k++;
    }

    // Free temporary arrays
    delete[] leftArr;
    delete[] rightArr;
}

// **Merge Sort Function**
// Time Complexity: O(N log N)
// Space Complexity: O(N)
void mergeSortMoviesByRating(Movie** movies, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Recursively sort the left and right halves
        mergeSortMoviesByRating(movies, left, mid);
        mergeSortMoviesByRating(movies, mid + 1, right);

        // Merge the sorted halves
        mergeMoviesByRating(movies, left, mid, right);
    }
}

void Movie::recommendMoviesByRating(Movie** movies, int totalMovies, float minRating) const {
    cout << "\nMovies with rating higher than " << minRating << ":\n";
    int count = 0;

    // Step 1: Count how many movies qualify
    // Iterates through the movie list and counts how many meet the rating threshold.
    // Time Complexity: O(N) (where N = totalMovies)
    for (int i = 0; i < totalMovies; ++i) {
        if (movies[i]->getRating() >= minRating) {
            count++;
        }
    }

    if (count == 0) {
        cout << "No movies found with the specified rating." << endl;
        return;
    }

    // Step 2: Store qualifying movies
    // Allocates memory for a new array to store movies that meet the rating condition.
    // Time Complexity: O(N)
    // Space Complexity: O(N) (creates new array for filtered movies)
    Movie** filteredMovies = new Movie*[count];
    int index = 0;
    for (int i = 0; i < totalMovies; ++i) {
        if (movies[i]->getRating() >= minRating) {
            filteredMovies[index++] = movies[i];
        }
    }

    // Step 3: Sort by movie rating using Merge Sort
    mergeSortMoviesByRating(filteredMovies, 0, count - 1); // Time Complexity: O(N log N)

    // Step 4: Display movies along with their actors and ratings
    for (int i = 0; i < count; ++i) {
        Movie* movie = filteredMovies[i];

        cout << "\n-- " << movie->getTitle() << " -- (Rating: " << movie->getRating() << "/10)\n";

        // Fetch the list of actors in the movie
        int actorCount;
        Actor** actors = movie->getSortedActors(actorCount);

        if (actorCount == 0) {
            cout << "   No actors found for this movie.\n";
        } else {
            cout << "   Actors: \n";
            for (int j = 0; j < actorCount; ++j) {
                cout << "   - " << actors[j]->getName();

                // Include actor rating if available
                if (actors[j]->getRating() > 0) {
                    cout << " (Rating: " << actors[j]->getRating() << "/10)";
                }
                cout << "\n";
            }
        }

        delete[] actors; // Free allocated memory
    }

    delete[] filteredMovies; // Free allocated memory
}


// ✅ Get LinkedList of actors
LinkedList<Actor>& Movie::getActors() {
    return actors;
}