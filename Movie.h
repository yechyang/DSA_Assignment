#ifndef MOVIE_H
#define MOVIE_H

#include <string>
using namespace std;

class Actor; // Forward declaration

// Linked list node for storing relationships
struct ActorNode {
    Actor* actor;
    ActorNode* next;

    ActorNode(Actor* actor) : actor(actor), next(nullptr) {}
};

class Movie {
private:
    int id;            // Movie's unique ID
    string title;         // Movie title
    string plot;          // Movie plot
    int releaseYear;      // Release year of the movie
    ActorNode* actorHead; // Head of the linked list of actors

public:
    // Constructor
    Movie(const int& id = 0, const string& title = "", const string& plot = "", int releaseYear = 0);

    // Destructor
    ~Movie();

    // Getter methods
    int getId() const;
    string getTitle() const;
    string getPlot() const;
    int getReleaseYear() const;

    // Setter methods
    void setId(const int& id);
    void setTitle(const string& title);
    void setPlot(const string& plot);
    void setReleaseYear(int releaseYear);

    // Add an actor to the movie's list
    void addActor(Actor* actor);

    // Display movie details and their actors
    void display() const;
};

#endif