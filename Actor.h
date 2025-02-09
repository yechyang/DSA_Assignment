#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include "LinkedList.h"  // Include the linked list implementation
using namespace std;

class Movie; // Forward declaration

class Actor {
private:
    int id;                 // Actor's unique ID
    string name;            // Actor's name
    int birthYear;          // Actor's birth year
    LinkedList<Movie> movies;  // Linked list for storing related movies
    float rating;           // Actor's rating

    // Merge sort utilities
    static void mergeSort(Actor** actors, int left, int right);
    static void merge(Actor** actors, int left, int mid, int right);
    
public:
    // Constructor
    Actor(const int& id = 0, const string& name = "", int birthYear = 0);

    // Destructor
    ~Actor();

    // Getter methods
    int getId() const;
    string getName() const;
    int getBirthYear() const;
    float getRating() const;

    // Setter methods
    void setId(const int& id);
    void setName(const string& name);
    void setBirthYear(int birthYear);
    void setRating(float newRating);

    // Add a movie to the actor's list
    void addMovie(Movie* movie);

    // Get linked movies
    LinkedList<Movie>& getMovies();

    // Update actor details
    void updateDetails(const string& newName, int newBirthYear);

    // Sort and retrieve movies
    Movie** getSortedMovies(int& count) const;

    // Sorting actors


    Movie** sortMoviesByRating(int& count) const;
    void insertionSortMoviesByRating(Movie** movies, int count) const;

    // Display functions
    void display() const;
    void displayKnownActors() const;

    // Recommendations
    void recommendActorsByRating(Actor** actors, int totalActors, float minRating) const;
};

#endif