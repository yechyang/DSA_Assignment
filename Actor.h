#ifndef ACTOR_H
#define ACTOR_H

#include <string>
using namespace std;

class Movie; // Forward declaration

// Linked list node for storing relationships
struct MovieNode {
    Movie* movie;
    MovieNode* next;

    MovieNode(Movie* movie) : movie(movie), next(nullptr) {}
};

class Actor {
private:
    int id;             // Actor's unique ID
    string name;           // Actor's name
    int birthYear;         // Actor's birth year
    MovieNode* movieHead;  // Head of the linked list of movies
    float rating; // Actor's rating

    static void mergeSort(Actor** actors, int left, int right);
    static void merge(Actor** actors, int left, int mid, int right);

    static void mergeByRating(Actor** actors, int left, int mid, int right);
    static void mergeSortByRating(Actor** actors, int left, int right);

public:
    // Constructor
    Actor(const int& id = 0, const string& name = "", int birthYear = 0);

    // Destructor
    ~Actor();
    MovieNode* getMovieHead() const {
        return movieHead;
    }
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

    // Update Actor details
    void updateDetails(const string& newName, int newBirthYear);

    const MovieNode* getMovies() const;
    Movie** getSortedMovies(int& count) const;

    Actor** sortActorsByRating(Actor** actors, int count) const;    
    // Display actor details and their movies
    void display() const;

    // void sortActorsByAge(Actor** allActors, int totalActors, int minAge, int maxAge, int& filteredCount);

    void displayKnownActors() const;

    void recommendActorsByRating(Actor** actors, int totalActors, float minRating) const;
};

#endif