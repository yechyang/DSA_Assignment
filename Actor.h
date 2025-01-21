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

public:
    // Constructor
    Actor(const int& id = 0, const string& name = "", int birthYear = 0);

    // Destructor
    ~Actor();

    // Getter methods
    int getId() const;
    string getName() const;
    int getBirthYear() const;

    // Setter methods
    void setId(const int& id);
    void setName(const string& name);
    void setBirthYear(int birthYear);

    // Add a movie to the actor's list
    void addMovie(Movie* movie);

    // Update Actor details
    void updateDetails(const string& newName, int newBirthYear);

    // Display actor details and their movies
    void display() const;
};

#endif