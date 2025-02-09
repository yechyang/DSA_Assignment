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

public:
    // Constructor
    // Pre-condition: None
    // Post-condition: Initializes an Actor with given ID, name, and birth year.
    Actor(const int& id = 0, const string& name = "", int birthYear = 0);

    // Destructor
    // Pre-condition: None
    // Post-condition: Clears movie list and deallocates memory.
    ~Actor();

    // Getter methods
    // Pre-condition: Actor object must be initialized.
    // Post-condition: Returns the actor's unique ID.
    int getId() const;

    // Pre-condition: Actor object must be initialized.
    // Post-condition: Returns the actor's name.
    string getName() const;

    // Pre-condition: Actor object must be initialized.
    // Post-condition: Returns the actor's birth year.
    int getBirthYear() const;

    // Pre-condition: Actor object must be initialized.
    // Post-condition: Returns the actor's rating.
    float getRating() const;

    // Setter methods
    // Pre-condition: None
    // Post-condition: Updates the actor's unique ID.
    void setId(const int& id);

    // Pre-condition: None
    // Post-condition: Updates the actor's name.
    void setName(const string& name);

    // Pre-condition: None
    // Post-condition: Updates the actor's birth year.
    void setBirthYear(int birthYear);

    // Pre-condition: Rating must be between 0.0 and 10.0
    // Post-condition: Updates the actor's rating if valid, otherwise prints error.
    void setRating(float newRating);

    // Add a movie to the actor's list
    // Pre-condition: movie must not be null, and must not already exist in the list.
    // Post-condition: Adds the movie to the actor's list of movies.
    void addMovie(Movie* movie);

    // Get linked movies
    // Pre-condition: Actor object must be initialized.
    // Post-condition: Returns a reference to the actor's linked list of movies.
    LinkedList<Movie>& getMovies();

    // Update actor details
    // Pre-condition: newName can be empty, and newBirthYear must be greater than 0.
    // Post-condition: Updates the actor's name and/or birth year.
    void updateDetails(const string& newName, int newBirthYear);

    // Sort and retrieve movies (sorted alphabetically by title)
    // Pre-condition: Actor object must have movies.
    // Post-condition: Returns a dynamically allocated array of movies sorted by title.
    // Return: Pointer to array of Movie pointers (caller must free memory).
    Movie** getSortedMovies(int& count) const;

    // Sort movies by rating in descending order
    // Pre-condition: Actor object must have movies.
    // Post-condition: Returns a dynamically allocated array of movies sorted by rating.
    // Return: Pointer to array of Movie pointers (caller must free memory).
    Movie** sortMoviesByRating(int& count) const;

    // Helper function for insertion sort (sorts movies by rating)
    // Pre-condition: movies array must be initialized.
    // Post-condition: Sorts the movies in descending order of rating.
    void insertionSortMoviesByRating(Movie** movies, int count) const;

    // Display actor details and their movies
    // Pre-condition: Actor object must be initialized.
    // Post-condition: Prints actor details along with movies they have acted in.
    void display() const;

    // Display a list of all actors that a particular actor knows (up to 2 levels)
    // Pre-condition: Actor must be connected to other actors through movies.
    // Post-condition: Prints all directly and indirectly known actors.
    void displayKnownActors() const;

    // Recommend actors based on rating
    // Pre-condition: Actors array must be initialized.
    // Post-condition: Prints all actors with a rating higher than minRating.
    void recommendActorsByRating(Actor** actors, int totalActors, float minRating) const;
};

#endif