#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include "LinkedList.h"  // Include LinkedList for managing actors

using namespace std;

class Actor; // Forward declaration

class Movie {
private:
    int id;                 // Movie's unique ID
    string title;           // Movie title
    string plot;            // Movie plot
    int releaseYear;        // Release year of the movie
    LinkedList<Actor> actors; // Linked list for storing actors
    float rating;           // Movie's rating

    // Helper function for displaying actor info
    static void displayActorInfo(const Actor& actor);

public:
    // Constructor
    // Pre-condition: None
    // Post-condition: Initializes a movie with given ID, title, plot, and release year.
    Movie(const int& id = 0, const string& title = "", const string& plot = "", int releaseYear = 0);

    // Destructor
    // Pre-condition: None
    // Post-condition: Clears the linked list of actors.
    ~Movie();

    // Getter methods
    // Pre-condition: Movie object must be initialized.
    // Post-condition: Returns the movie's unique ID.
    int getId() const;

    // Pre-condition: Movie object must be initialized.
    // Post-condition: Returns the movie's title.
    string getTitle() const;

    // Pre-condition: Movie object must be initialized.
    // Post-condition: Returns the movie's plot.
    string getPlot() const;

    // Pre-condition: Movie object must be initialized.
    // Post-condition: Returns the movie's release year.
    int getReleaseYear() const;

    // Pre-condition: Movie object must be initialized.
    // Post-condition: Returns the movie's rating.
    float getRating() const;

    // Setter methods
    // Pre-condition: None
    // Post-condition: Updates the movie's unique ID.
    void setId(const int& id);

    // Pre-condition: None
    // Post-condition: Updates the movie's title.
    void setTitle(const string& title);

    // Pre-condition: None
    // Post-condition: Updates the movie's plot.
    void setPlot(const string& plot);

    // Pre-condition: None
    // Post-condition: Updates the movie's release year.
    void setReleaseYear(int releaseYear);

    // Pre-condition: Rating must be between 0.0 and 10.0.
    // Post-condition: Updates the movie's rating if valid, otherwise prints an error.
    void setRating(float newRating);

    // Add an actor to the movie's actor list
    // Pre-condition: actor must not be null, and must not already exist in the list.
    // Post-condition: Adds the actor to the movie's list of actors.
    void addActor(Actor* actor);

    // Update movie details
    // Pre-condition: newTitle and newPlot can be empty, and newReleaseYear must be greater than 0.
    // Post-condition: Updates the movie's title, plot, and/or release year.
    void updateDetails(const string& newTitle, const string& newPlot, int newReleaseYear);

    // Display movie details and their actors
    // Pre-condition: Movie object must be initialized.
    // Post-condition: Prints movie details along with actors in the movie.
    void display() const;

    // Get sorted actors by name
    // Pre-condition: Movie object must have actors.
    // Post-condition: Returns a dynamically allocated array of actors sorted by name.
    // Return: Pointer to an array of Actor pointers (caller must free memory).
    Actor** getSortedActors(int& count) const;

    // Sort actors by rating in descending order
    // Pre-condition: Movie object must have actors.
    // Post-condition: Returns a dynamically allocated array of actors sorted by rating.
    // Return: Pointer to an array of Actor pointers (caller must free memory).
    Actor** sortActorsByRating(int& count) const;

    // Helper function for sorting actors by rating
    // Pre-condition: actors array must be initialized.
    // Post-condition: Sorts the actors in descending order of rating.
    void insertionSortActorsByRating(Actor** actors, int count) const;

    // Recommend movies based on rating threshold
    // Pre-condition: movies array must be initialized.
    // Post-condition: Displays movies with ratings above minRating.
    void recommendMoviesByRating(Movie** movies, int totalMovies, float minRating) const;

    // Recommend movies based on release year
    // Pre-condition: movies array must be initialized.
    // Post-condition: Displays movies released in the given year.
    void recommendMoviesByYear(Movie** movies, int totalMovies, int year) const;

    // Helper function for sorting movies by rating
    // Pre-condition: movies array must be initialized.
    // Post-condition: Sorts the movies in descending order of rating.
    void insertionSortMoviesByRating(Movie** movies, int count) const;

    // Get the linked list of actors in the movie
    // Pre-condition: Movie object must be initialized.
    // Post-condition: Returns a reference to the movie's linked list of actors.
    LinkedList<Actor>& getActors();
};

#endif