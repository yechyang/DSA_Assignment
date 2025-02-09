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

// Add an actor to the movie's list
void Movie::addActor(Actor* actor) {
    if (!actor || actors.contains(actor)) return;  // Prevent duplicates
    actors.append(actor);
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


// Updated display to use function pointer instead of lambda
void Movie::display() const {
    cout << "Movie ID: " << id << ", \nTitle: " << title
         << ", \nPlot: " << plot << ", \nRelease Year: " << releaseYear << endl;

    cout << "\nActors in this movie:" << endl;
    actors.display(Movie::displayActorInfo);  // Use function pointer
}

// Static function to display an actor
void Movie::displayActorInfo(const Actor& actor) {
    cout << " - ID: " << actor.getId() << ", Name: " << actor.getName() << endl;
}


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
    Actor** actorArray = actors.toArray(count);
    if (count == 0) return nullptr;

    // **Use Insertion Sort (Better for Small Data Sets)**
    insertionSortActors(actorArray, count); // O(n^2) worst case, O(n) best case

    return actorArray;
}

// Insertion Sort for Actors by Rating
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

Actor** Movie::sortActorsByRating(int& count) const {
    Actor** actorArray = actors.toArray(count);
    if (count == 0) return nullptr;

    // Sort by rating (descending order)
    insertionSortActorsByRating(actorArray, count);

    return actorArray;
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


// ✅ Get LinkedList of actors
LinkedList<Actor>& Movie::getActors() {
    return actors;
}