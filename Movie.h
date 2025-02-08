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
    LinkedList<Actor> actors; // Linked list for storing actors LinkedList<Actor>
    float rating;           // Movie's rating
    static void displayActorInfo(const Actor& actor);
    static void mergeByRating(Movie** movies, int left, int mid, int right);
    static void mergeSortByRating(Movie** movies, int left, int right);

public:
    // Constructor & Destructor
    Movie(const int& id = 0, const string& title = "", const string& plot = "", int releaseYear = 0);
    ~Movie();

    // Getter methods
    int getId() const;
    string getTitle() const;
    string getPlot() const;
    int getReleaseYear() const;
    float getRating() const;

    // Setter methods
    void setId(const int& id);
    void setTitle(const string& title);
    void setPlot(const string& plot);
    void setReleaseYear(int releaseYear);
    void setRating(float newRating);

    // Add an actor to the movie's actor list
    void addActor(Actor* actor);

    // Update movie details
    void updateDetails(const string& newTitle, const string& newPlot, int newReleaseYear);

    // Display movie details and their actors
    void display() const;

    // Get sorted actors by name
    Actor** getSortedActors(int& count) const;

    Movie** sortMoviesByRating(Movie** movies, int count) const;

    void recommendMoviesByRating(Movie** movies, int totalMovies, float minRating) const;
    void recommendMoviesByYear(Movie** movies, int totalMovies, int year) const;

    void insertionSortMoviesByRating(Movie** movies, int count) const;

    LinkedList<Actor>& getActors();
};

#endif